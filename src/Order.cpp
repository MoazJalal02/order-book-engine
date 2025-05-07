#include <Order.hpp>
#include <iostream>

using namespace std;

int Order::nextOrderId = 0;

int Order::getOrderId() const {
    return orderId;
}   

Side Order::getOrderType() const {
    return orderType;
}

double Order::getPrice() const {
    return price;
}
int Order::getInitialVolume() const {
    return initialVolume;
}

int Order::getRemainingVolume() const {
    return remainingVolume;
}

time_t Order::getTimeStamp() const {
    return timeStamp;
}

void Order::setOrderId(int oId) {
    orderId = oId;
}   

void Order::setOrderType(Side t) {
    orderType = t;
}

void Order::setPrice(double p) {
    price = p;
}

void Order::setInitialVolume(int iVolume) {
    initialVolume = iVolume;
}

void Order::setRemainingVolume(int rVolume) {
    remainingVolume = rVolume;
}

void Order::setTimeStamp(time_t t) {
    timeStamp = t;
}

void Order::displayOrder() const {
    cout << "Order Id: " << orderId << endl;
    cout << "Order Type: " << orderType << endl;
    cout << "Price: " << price << endl;
    cout << "Initital Volume: " << initialVolume << endl;
    cout << "Remaining Volume: " << remainingVolume << endl;
    cout << "Date Created: " << timeStamp << endl;
}

