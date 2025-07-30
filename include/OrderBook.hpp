#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "enum.hpp"
#include "IndexedProrityQueue.hpp"
#include <vector>

using namespace std;

class OrderBook {
    private:
        int nextOrderID = 1;
        unordered_map<OrderSide, unordered_map<double, double>> volumeAtPriceMap;
        unordered_map<int, Order> orders;
        IndexedPriorityQueue buyOrders;
        IndexedPriorityQueue sellOrders;

        void printOrderSide(OrderSide side) const;
    public:
        OrderBook();
        void placeOrder(int userId, OrderType orderType, OrderSide orderSide, double initialAmount, double price = 0.0);
        bool hasOrder(int orderId) const;
        double getVolumeAtPrice(OrderSide side, double price) const;
        int getOrdersCount(OrderSide side) const;
        bool cancelOrder(int userId, int orderId);
        void fulfillOrder(Order& order);
        void listUserOrders(int userId) const;
        void displayOrderBook() const;
};
#endif