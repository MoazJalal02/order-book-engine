#include "../include/OrderBook.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook(){}

void OrderBook::placeOrder() {
    Side orderType = ASK; 
    double price = 10; 
    int initialVolume = 3;

    Order newOrder(orderType, price, initialVolume);

    pair<double, Side> key = make_pair(newOrder.getPrice(), newOrder.getOrderType());

    if(orderType == ASK) {
        bistAsk.push(newOrder);
    } else {
        bistBid.push(newOrder);
    }

    orders.insert({newOrder.getOrderId(), newOrder});
    if(volumesAtPrice.find(key) != volumesAtPrice.end()){
        volumesAtPrice[key] += newOrder.getInitialVolume();
    } else {
        volumesAtPrice.insert({key, newOrder.getInitialVolume()});
    }

    cout << "Order with the following information added: " << endl;
    newOrder.displayOrder();


    cout << endl;
    cout << "Volume at price => " << getVolumeAtPrice(key) << endl;
}

void OrderBook::executeOrder(Order& o) {
    if(o.getOrderType() == ASK) {
        priority_queue<Order> temp = bistBid;
        while(!bistBid.empty() && o.getRemainingVolume() > 0 && o.getPrice() <= bistBid.top().getPrice()) {
            Order topBid = bistBid.top();
            bistBid.pop();
            int matchVolume = min(o.getRemainingVolume(), topBid.getRemainingVolume());
            o.setRemainingVolume(o.getRemainingVolume() - matchVolume);
            
            orders[topBid.getOrderId()].setRemainingVolume(topBid.getRemainingVolume() - matchVolume);

            if (orders[topBid.getOrderId()].getRemainingVolume() > 0) {
                bistBid.push(orders[topBid.getOrderId()]);
            }
        }
    } else {

    }
}

// void OrderBook::cancelOrder(Order) {

// }

int OrderBook::getVolumeAtPrice(pair<double, Side> k) {
    return volumesAtPrice[k];
}