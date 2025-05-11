#include "../include/OrderBook.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook(){}

void OrderBook::placeOrder(Order& o) {
    executeOrder(o);

    if(o.getRemainingVolume() > 0) {
        // Insert the order only if it wasn't fullfilled 
        orders.emplace(o.getOrderId(), o);
        cout << "Order with Id: " << o.getOrderId() << " was added" << endl;
        if (o.getOrderType() == ASK) bestAsk.push(o);
        else bestBid.push(o);
    
        volumesAtPrice[{o.getPrice(), o.getOrderType()}] += o.getRemainingVolume();
    } else {
        // Erase the order from orders if it was fully filled 
        orders.erase(o.getOrderId());
    }
}


void OrderBook::executeOrder(Order& o) {
    if(o.getOrderType() == ASK) {
        while(!(bestBid.empty()) && (o.getRemainingVolume() > 0) && (o.getPrice() <= bestBid.top().getPrice())) {
            Order topBid = bestBid.top();
            bestBid.pop();
            
            int matchVolume = min(o.getRemainingVolume(), topBid.getRemainingVolume());
            o.setRemainingVolume(o.getRemainingVolume() - matchVolume);
            topBid.setRemainingVolume(topBid.getRemainingVolume() - matchVolume);
            cout << "Amount of " << matchVolume << " was fullfilled at price: " << topBid.getPrice() << endl;
            if(topBid.getRemainingVolume() > 0) {
                bestBid.push(topBid);
                auto it = orders.find(topBid.getOrderId());
                if(it != orders.end()){
                    it->second.setRemainingVolume(topBid.getRemainingVolume());
                }
            } else if(topBid.getRemainingVolume() == 0) cancelOrder(topBid);
            
            volumesAtPrice[{topBid.getPrice(), topBid.getOrderType()}] -= matchVolume;     
        }
    } else {
        while(!(bestAsk.empty()) && (o.getRemainingVolume() > 0) && (o.getPrice() >= bestAsk.top().getPrice())) {
            Order topAsk = bestAsk.top();
            bestAsk.pop();

            int matchVolume = min(o.getRemainingVolume(), topAsk.getRemainingVolume());
            o.setRemainingVolume(o.getRemainingVolume() - matchVolume);
            topAsk.setRemainingVolume(topAsk.getRemainingVolume() - matchVolume);
            cout << "Amount of " << matchVolume << " was fullfilled at price: " << topAsk.getPrice() << endl;

            // Pushes the bestAsk back to the heap if it's not fullfilled 
            if(topAsk.getRemainingVolume() > 0) {
                bestAsk.push(topAsk);
                auto it = orders.find(topAsk.getOrderId());
                if(it != orders.end()){
                    it->second.setRemainingVolume(topAsk.getRemainingVolume());
                }
            } else if(topAsk.getRemainingVolume() == 0) cancelOrder(topAsk);
         
            volumesAtPrice[{topAsk.getPrice(), topAsk.getOrderType()}] -= matchVolume; 
        }
    }

    if(o.getRemainingVolume() == 0) {
        cancelOrder(o);
    }
}

void OrderBook::cancelOrder(Order &o) {
    auto it = orders.find(o.getOrderId());
    if(it != orders.end()){
        orders.erase(it->first);
    }
}

int OrderBook::getVolumeAtPrice(pair<double, Side> k) {
    return volumesAtPrice[k];
}

void OrderBook::displayOrders() {

    cout << string(6, '*') << "Displaying all Orders" << string(6, '*') << endl;
    for (auto i : orders){
        i.second.displayOrder();
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << string(6, '*') << "Displaying BIDs orders" << string(6, '*') << endl;
    priority_queue<Order, vector<Order>> temp= bestBid; 
    while (!temp.empty()) {
        temp.top().displayOrder();
        temp.pop();
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << string(6, '*') << "Displaying ASKs orders" << string(6, '*') << endl;
    priority_queue<Order, vector<Order>, comparePrice> temp_2= bestAsk; 
    while (!temp_2.empty()) {
        temp_2.top().displayOrder();
        temp_2.pop();
        cout << endl;
    }
}
