#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "VolumeAtPrice.hpp"
#include "enum.hpp"
#include "IndexedProrityQueue.hpp"
#include <vector>

using namespace std;

class OrderBook {
    private:
        vector<VolumeAtPrice> volumesAtPrice;
        IndexedPriorityQueue buyOrders;
        IndexedPriorityQueue sellOrders;
    public:
        OrderBook();
        void placeOrder(int userId, OrderType orderType, OrderSide orderSide, double price, double initialAmount);
        void cancelOrder(int userId, int orderId);

};

#endif