#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "enum.hpp"
#include "IndexedProrityQueue.hpp"
#include <vector>

using namespace std;

class OrderBook {
    private:
        unordered_map<OrderSide, unordered_map<double, double>> volumeAtPriceMap;
        unordered_map<int, Order> orders;
        IndexedPriorityQueue buyOrders;
        IndexedPriorityQueue sellOrders;
    public:
        OrderBook();
        void placeOrder(int userId, OrderType orderType, OrderSide orderSide, double price, double initialAmount);
        void cancelOrder(int userId, int orderId);
        void fullfillOrder(Order& order);
        int matchOrder(int orderId);
        void displayOrderBook();
};
#endif