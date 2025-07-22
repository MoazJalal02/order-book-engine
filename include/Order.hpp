#ifndef ORDER_HPP
#define ORDER_HPP

#include "enum.hpp"

class Order {
    private:
        static int orderId;
        int userId;
        OrderType orderType;
        OrderSide orderSide;
        double initialAmount;
        double remainingAmount;
    public:
        Order(int userId, OrderType orderType, OrderSide orderSide, double initialAmount)
            : userId(userId), orderType(orderType), orderSide(orderSide), initialAmount(initialAmount), remainingAmount(initialAmount) {
            orderId++;
        }
        void setRemainingAmount(double amount);
};

#endif