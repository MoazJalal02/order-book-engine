#include "IndexedProrityQueue.hpp"

using namespace std;

void IndexedPriorityQueue::swap(int i, int j) {
    std::swap(heap[i], heap[j]);
    position[heap[i]] = i;
    position[heap[j]] = j;
}

void IndexedPriorityQueue::upHeap(int k) {
    while (k > 0 && greater(heap[k], heap[(k - 1) / 2])) {
        swap(k, (k - 1) / 2);
        k = (k - 1) / 2;
    }
}

void IndexedPriorityQueue::downHeap(int k) {
    int n = heap.size();
    while (2 * k + 1 < n) {
        int j = 2 * k + 1;
        if (j + 1 < n && greater(heap[j + 1], heap[j])) {
            j++;
        }
        if (!greater(heap[k], heap[j])) {
            break;
        }
        swap(k, j);
        k = j;
    }
}

bool IndexedPriorityQueue::greater(int i, int j) {
    if (isMinHeap) {
        return priority[heap[i]] < priority[heap[j]];
    } else {
        return priority[heap[i]] > priority[heap[j]];
    }
}


void IndexedPriorityQueue::insert(Order order) {
    int orderID = order.getOrderId();
    heap.push_back(orderID);
    position[orderID] = heap.size() - 1;
    priority[orderID] = order.getPrice();
    upHeap(heap.size() - 1);
}

void IndexedPriorityQueue::remove(int orderID) {
    auto it = position.find(orderID);
    int idx = it->second;
    swap(idx, heap.size() - 1);
    heap.pop_back();
    position.erase(it);
    priority.erase(orderID);
    if (idx < heap.size()) {
        downHeap(idx);
        upHeap(idx);
    }
}

int IndexedPriorityQueue::top() const {
    return heap[0];
}

void IndexedPriorityQueue::pop() {
    remove(heap[0]);
}

bool IndexedPriorityQueue::contains(int orderID) const {
    return position.find(orderID) != position.end();
}

bool IndexedPriorityQueue::empty() const {
    return heap.empty();
}