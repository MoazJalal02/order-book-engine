#include "OrderBook.hpp"
#include "enum.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

OrderBook::OrderBook(){
    
};

void OrderBook::placeOrder(int userId, OrderType orderType, OrderSide orderSide, double initialAmount, double price) {
    // Create a new order
    int orderId = nextOrderID++;
    Order newOrder(orderId, userId, orderType, orderSide, price, initialAmount);

    double remainingAmount = initialAmount;

    if(orderType == OrderType::Market) {
        fulfillOrder(newOrder);

        remainingAmount = newOrder.getRemainingAmount();
        cout << "Order PLaced:\n";
        cout << "  → Order ID: " << orderId << "\n";
        cout << "  → Status: Fully matched\n";
        
        if(remainingAmount > 0) {
            cout << "Order PLaced:\n";
            cout << "  → Order ID: " << orderId << "\n";
            cout << "  → order could not be fully fulfilled. Remaining amount: " 
            << remainingAmount << ". Consider placing a limit order instead." << endl;
            return;
        } 
    }
    
    fulfillOrder(newOrder);
    
    // Check if the order has a remaining amount
    remainingAmount = newOrder.getRemainingAmount();

    if(remainingAmount <= 0) {
        cout << "Order Placed:\n";
        cout << "  → Order ID: " << orderId << "\n";
        cout << "  → Status: Fulfilled\n";
        cout << "  → Fulfilled Quantity: " << initialAmount << "/" << initialAmount << "\n";
        return; 
    }
    
    
    // Add the order to the orders map
    orders.emplace(newOrder.getOrderId(), std::move(newOrder));

    // Insert the order into the appropriate priority queue based on order side
    if(orderSide == OrderSide::Buy) {
            buyOrders.insert(newOrder);
    } else {
            sellOrders.insert(newOrder);
    }

    cout << "Order Placed:\n";
    cout << "  → Order ID: " << orderId << "\n";
    cout << "  → Status: " 
            << (remainingAmount < initialAmount ? "Partially filled" : "Pending") << "\n";
    cout << "  → Fulfilled Quantity: " << initialAmount - remainingAmount << "/" << initialAmount << "\n";

    //  Update the volume at price map
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
    // Check if the order exists
    auto it = orders.find(orderId);
    if(it == orders.end() || it->second.getUserId() != userId) {

        return false;
    }
    
    OrderSide orderSide = it->second.getOrderSide();
    // Remove the order from the appropriate priority queue
    if(orderSide == OrderSide::Buy && buyOrders.contains(orderId)) {
        buyOrders.remove(orderId);
    } else if (orderSide == OrderSide::Sell && sellOrders.contains(orderId)) {
        sellOrders.remove(orderId);
    }

    // Update the volume at price map
    auto& volumeMap = volumeAtPriceMap[orderSide];
    auto price = it->second.getPrice();

    if (volumeMap.count(price)) {
        volumeMap[price] -= it->second.getRemainingAmount();
        if (volumeMap[price] <= 0.0) {
            volumeMap.erase(price);
        }
    }

    // Remove the order from the orders map
    orders.erase(orderId);

    return true;

}

void OrderBook::fulfillOrder(Order& order) {
    // Match the order with the best available opposite order
    while(order.getRemainingAmount() > 0) {
        int matchedOrderId = -1;
        Order* matchedOrder = nullptr;


        // Select the best match based on order side
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

void OrderBook::printOrderSide(OrderSide side) const {
    // ANSI Color codes
    const char* color = (side == OrderSide::Buy) ? "\033[32m" : "\033[31m";
    const char* reset = "\033[0m";

    auto& priceVolumeMap = volumeAtPriceMap.at(side);

    vector<pair<double, double>> sortedPriceVolume(priceVolumeMap.begin(), priceVolumeMap.end());

    if (side == OrderSide::Buy) {
        sort(sortedPriceVolume.begin(), sortedPriceVolume.end(),
            [](const auto& a, const auto& b) { return a.first > b.first; });
    } else {
        sort(sortedPriceVolume.begin(), sortedPriceVolume.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });
    }

    cout << (side == OrderSide::Buy ? "BUY ORDERS:\n" : "SELL ORDERS:\n");
    cout << setw(10) << "Price" << " "
         << setw(10) << "Volume\n";

    for (const auto& [price, volume] : sortedPriceVolume) {
        cout << color
             << fixed << setprecision(2)
             << setw(10) << price << "  "
             << setw(10) << volume << "\n"
             << reset << endl;
    }
}


void OrderBook::displayOrderBook() const {
    // Display buy orders
    cout << "ORDER BOOK:\n";
    
    cout << "-------------------\n";
    cout << "BUY ORDERS:\n";
    printOrderSide(OrderSide::Buy);
    
    cout << "-------------------\n";
    cout << "SELL ORDERS:\n";
    printOrderSide(OrderSide::Sell);
    
    cout << "-------------------\n";
    cout << "Total Orders: " << orders.size() << "\n";
    cout << "-------------------\n";
}