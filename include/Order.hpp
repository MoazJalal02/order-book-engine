#ifndef ORDER_HPP
#define ORDER_HPP

#include "enum.hpp"

class Order {
    private:
        int orderId;
        int userId;
        OrderType orderType;
        OrderSide orderSide;
        double price;
        double initialAmount;
        double remainingAmount;
    public:
        Order(int orderId, int userId, OrderType orderType, OrderSide orderSide, double price, double initialAmount)
            : orderId(orderId), userId(userId), orderType(orderType), orderSide(orderSide), price(price), initialAmount(initialAmount), remainingAmount(initialAmount) {
            ;
        }

        double getRemainingAmount() const;

        void setRemainingAmount(double amount);
        int getOrderId() const;
        int getUserId() const;
        double getPrice() const;
        double getInitialAmount() const;
        OrderType getOrderType() const;
        OrderSide getOrderSide() const;
};

#endif