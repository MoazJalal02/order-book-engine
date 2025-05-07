#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "./Order.hpp"
#include <queue>
#include <unordered_map>

using namespace std;

struct comparePrice {
    // Compare the priceses of Orders
    bool operator()(const Order& a, const Order& b) const {
        return (a.getPrice() > b.getPrice());
    }
};

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        size_t hash1 = hash<T1>{}(p.first);
        size_t hash2 = hash<T2>{}(p.second);
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

class OrderBook {
    private:
        priority_queue<Order, vector<Order>, comparePrice> bistAsk; //min-heap
        priority_queue<Order, vector<Order>> bistBid; //max-heap
        unordered_map<int, Order> orders;
        unordered_map<pair<double, Side>, int, hash_pair> volumesAtPrice;
    public:
        OrderBook();
        void placeOrder();
        void executeOrder(Order &);
        // void cancelOrder(Order);
        int getVolumeAtPrice(pair<double, Side>);
};


#endif