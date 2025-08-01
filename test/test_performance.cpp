#include "OrderBook.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    OrderBook ob;

    const int NUM_ORDERS = 100000;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_ORDERS; ++i) {
        ob.placeOrder(i, OrderType::Limit, OrderSide::Buy, 10.0, 100.0 + i);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Placed " << NUM_ORDERS << " orders in " << duration << " ms\n";
}
