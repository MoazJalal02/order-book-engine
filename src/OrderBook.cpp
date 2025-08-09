#include "OrderBook.hpp"
#include "enum.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

OrderBook::OrderBook(): buyOrders(false), sellOrders(true) {

}

OrderBook::OrderBook(vector<Order> initialOrders): buyOrders(false), sellOrders(true) {
    for (const auto& order : initialOrders) {
        insertSingleOrder(order);
    }
}

void OrderBook::insertSingleOrder(const Order& order) {
    orders.emplace(order.getOrderId(), order);

    if(order.getOrderSide() == OrderSide::Buy) {
        buyOrders.insert(order);
    } else {
        sellOrders.insert(order);
    }

    volumeAtPriceMap[order.getOrderSide()][order.getPrice()] += order.getRemainingAmount();
}

void OrderBook::placeOrder(int userId, OrderType orderType, OrderSide orderSide, double initialAmount, double price) {
    // Validate order parameters
    if(initialAmount <= 0) {
        throw invalid_argument("Invalid order inputs: initial amount must be greater than zero.");
    }

    if(orderType== OrderType::Limit && price <= 0.00) {
        throw invalid_argument("Invalid order inputs: price must be greater than zero for limit orders."); 
    } 

    // Create a new order
    int orderId = nextOrderID++;
    Order newOrder(orderId, userId, orderType, orderSide, initialAmount, price);

    double remainingAmount = initialAmount;

    if(orderType == OrderType::Market) {
        fulfillOrder(newOrder);

        remainingAmount = newOrder.getRemainingAmount();
        
        if(remainingAmount > 0) {
            return;
        } 
    }
    
    fulfillOrder(newOrder);
    
    // Check if the order has a remaining amount
    remainingAmount = newOrder.getRemainingAmount();

    if(remainingAmount <= 0) {
        return; 
    }
    
    
    orders.emplace(newOrder.getOrderId(), std::move(newOrder));

    if(orderSide == OrderSide::Buy) {
            buyOrders.insert(newOrder);
    } else {
            sellOrders.insert(newOrder);
    }

    volumeAtPriceMap[orderSide][price] += remainingAmount;
}


bool OrderBook::hasOrder(int orderId) const {
    return orders.find(orderId) != orders.end();
}

double OrderBook::getVolumeAtPrice(OrderSide side, double price) const {
    auto it = volumeAtPriceMap.find(side);
    if(it != volumeAtPriceMap.end()) {
        auto priceIt = it->second.find(price);
        if(priceIt != it->second.end()) {
            return priceIt->second;
        }
    }

    return 0.0;
}

int OrderBook::getOrdersCount(OrderSide side) const {
    int count = 0;
    for (const auto& [id, order] : orders) {
        if (order.getOrderSide() == side) {
            count++;
        }
    }

    return count;
}

bool OrderBook::cancelOrder(int userId, int orderId) {
    auto it = orders.find(orderId);
    if(it == orders.end()) {
        throw invalid_argument("Order does not exist");
        return false;    
    }
    
    if(it->second.getUserId() != userId) {
        throw invalid_argument("User does not own the order");
        return false;
    }
    
    OrderSide orderSide = it->second.getOrderSide();

    if(orderSide == OrderSide::Buy && buyOrders.contains(orderId)) {
        buyOrders.remove(orderId);
    } else if (orderSide == OrderSide::Sell && sellOrders.contains(orderId)) {
        sellOrders.remove(orderId);
    }

    auto& volumeMap = volumeAtPriceMap[orderSide];
    auto price = it->second.getPrice();

    if (volumeMap.count(price)) {
        volumeMap[price] -= it->second.getRemainingAmount();
        if (volumeMap[price] <= 0.0) {
            volumeMap.erase(price);
        }
    }

    orders.erase(orderId);

    return true;
}

void OrderBook::fulfillOrder(Order& order) {
    const string yellow = "\033[33m";
    const string reset = "\033[0m";
    double averagePrice = 0.0;
    while(order.getRemainingAmount() > 0) {
        int matchedOrderId = -1;
        Order* matchedOrder = nullptr;

        // Select the best match
        if(order.getOrderSide() == OrderSide::Buy && !sellOrders.empty()) {
            matchedOrderId = sellOrders.top();
            matchedOrder = &orders.at(matchedOrderId);

            if(order.getPrice() < matchedOrder->getPrice() && order.getOrderType() == OrderType::Limit) break;
        } else if (order.getOrderSide() == OrderSide::Sell && !buyOrders.empty()) {
            matchedOrderId = buyOrders.top();
            matchedOrder = &orders.at(matchedOrderId);

            if(order.getPrice() > matchedOrder->getPrice() && order.getOrderType() == OrderType::Limit) break;
        } else {
            break;
        }

        // Fulfill the order
        double matchedAmount = min(order.getRemainingAmount(), matchedOrder->getRemainingAmount());
        order.setRemainingAmount(order.getRemainingAmount() - matchedAmount);
        matchedOrder->setRemainingAmount(matchedOrder->getRemainingAmount() - matchedAmount);
        averagePrice += matchedAmount * matchedOrder->getPrice();
        
        cout << yellow <<"Filled " << matchedAmount
             << "/" << order.getInitialAmount() << " units at price: $" << matchedOrder->getPrice() << reset << endl;
             
        // Update volume at price
        OrderSide matchedSide = matchedOrder->getOrderSide();
        volumeAtPriceMap[matchedSide][matchedOrder->getPrice()] -= matchedAmount;
        if(volumeAtPriceMap[matchedSide][matchedOrder->getPrice()] <= 0)
        volumeAtPriceMap[matchedSide].erase(matchedOrder->getPrice());
             
        
        // Remove fully matched orders
        if(matchedOrder->getRemainingAmount() <= 0) {
            if(matchedSide == OrderSide::Sell)
            sellOrders.remove(matchedOrderId);
            else
            buyOrders.remove(matchedOrderId);
            
            orders.erase(matchedOrderId);
        }        
    }
    averagePrice /= order.getInitialAmount() - order.getRemainingAmount();
    cout << yellow <<"Filled " << order.getInitialAmount() - order.getRemainingAmount()
         << "/" << order.getInitialAmount() << " units at average price: $" << averagePrice << reset << endl;
}

void OrderBook::listUserOrders(int userId) const {
    cout << "Open Orders for User " << userId << ":\n";
    
    for (const auto& pair : orders) {
        const Order& order = pair.second;
        if (order.getUserId() == userId) {
            cout << "Order ID: " << order.getOrderId() 
                 << ", Side: " << (order.getOrderSide() == OrderSide::Buy ? "Buy" : "Sell") 
                 << ", Price: " << order.getPrice() 
                 << ", Remaining Amount: " << order.getRemainingAmount() 
                 << endl;
        }
    }
}

void OrderBook::printOrderBook(int count) const {
    const string green = "\033[32m";
    const string red = "\033[31m";
    const string reset = "\033[0m";

    vector<double> buyPrices, sellPrices;

    for(const auto& [price, volume] : volumeAtPriceMap.at(OrderSide::Buy)) {
        buyPrices.push_back(price);
    }

    for(const auto& [price, volume] : volumeAtPriceMap.at(OrderSide::Sell)) {
        sellPrices.push_back(price);
    }

    sort(buyPrices.begin(), buyPrices.end(), greater<double>());
    sort(sellPrices.begin(), sellPrices.end());
    
    int maxCount = max((int)sellPrices.size(), (int)buyPrices.size());

    const int cellWidth = 12;
    const int colGap = 8;
    const int totalWidth = 4 * cellWidth + colGap;

    cout << "\n";
    cout << string((totalWidth - 17)/2, ' ') << "=== ORDER BOOK: AAPL ===" << endl;
    cout << endl;

    cout 
        << left
        << setw(cellWidth) << "SELL Price" << setw(cellWidth) << "Volume"
        << string(colGap, ' ')
        << setw(cellWidth) << "BUY Price" << setw(cellWidth) << "Volume"
        << endl
    ;

    cout << string(totalWidth, '-') << endl;

    for(int i = 0; i < maxCount; ++i) {
        string sellPriceStr = "", sellVolStr = "";
        string buyPriceStr  = "", buyVolStr  = "";

        if(i < (int)sellPrices.size()) {
            double price = sellPrices[i];
            double vol   = volumeAtPriceMap.at(OrderSide::Sell).at(price);
            
            ostringstream ss;
            ss << fixed << setprecision(3) << price;
            sellPriceStr = ss.str();

            ss.str("");
            ss << fixed << setprecision(3) << vol;
            sellVolStr   = ss.str();
        }

        if(i < (int)buyPrices.size()) {
            double price = buyPrices[i];
            double vol   = volumeAtPriceMap.at(OrderSide::Buy).at(price);
            
            ostringstream ss;
            ss << fixed << setprecision(3) << price;
            buyPriceStr = ss.str();
            
            ss.str("");
            ss << fixed << setprecision(3) << vol;
            buyVolStr   = ss.str();
        }

        cout
            << red << left << setw(cellWidth) << sellPriceStr << reset
            << red << setw(cellWidth) << sellVolStr << reset
            << setw(colGap) << " "
            << green << setw(cellWidth) << buyPriceStr  << reset
            << green << setw(cellWidth) << buyVolStr << reset
            << endl
        ;
    }
    cout << string(totalWidth, '-') << endl;
}