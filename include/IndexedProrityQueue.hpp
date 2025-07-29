#ifndef INDEXED_PRIORITY_QUEUE_HPP
#define INDEXED_PRIORITY_QUEUE_HPP

#include <vector>
#include <unordered_map>
#include "Order.hpp"

using namespace std;

class IndexedPriorityQueue {
private:
    bool isMinHeap;
    vector<int> heap;
    unordered_map<int, int> position;
    unordered_map<int, double> priority;

    void swap(int i, int j);
    void upHeap(int k);
    void downHeap(int k);
    bool greater(int i, int j);

public:
    void insert(Order order);
    void remove(int orderID);
    int top() const;
    void pop();
    bool empty() const;
    bool contains(int orderID) const;
};

#endif
