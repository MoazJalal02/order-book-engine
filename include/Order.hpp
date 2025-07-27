#ifndef ORDER_HPP
#define ORDER_HPP

#include "enum.hpp"

class Order {
    private:
        static int orderId;
        int userId;
        OrderType orderType;
        OrderSide orderSide;
        double price;
        double initialAmount;
        double remainingAmount;
    public:
        Order(int userId, OrderType orderType, OrderSide orderSide, double price, double initialAmount)
            : userId(userId), orderType(orderType), orderSide(orderSide), initialAmount(initialAmount), remainingAmount(initialAmount) {
            orderId++;
        }

        double getRemainingAmount() const;

        void setRemainingAmount(double amount);
        int getOrderId() const;
        int getUserId() const;
        double getPrice() const;
        OrderSide getOrderSide() const;
};

#endif