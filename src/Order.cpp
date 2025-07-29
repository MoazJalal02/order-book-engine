#include "Order.hpp"

int Order::getOrderId() const {
    return orderId;
}

int Order::getUserId() const {
    return userId;
}

double Order::getPrice() const {
    return price;
}

double Order::getInitialAmount() const {
    return initialAmount;
}

double Order::getRemainingAmount() const {
    return remainingAmount;
}

OrderType Order::getOrderType() const {
    return orderType;
}

OrderSide Order::getOrderSide() const {
    return orderSide;
}

void Order::setRemainingAmount(double amount) {
    remainingAmount = amount;
}


