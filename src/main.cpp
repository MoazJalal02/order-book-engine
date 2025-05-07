#include <iostream>
#include "../include/OrderBook.hpp"

using namespace std;

int main(){
    OrderBook orderBookTest1 = OrderBook();

    cout << "Main Function" << endl;
    
    orderBookTest1.placeOrder();
    orderBookTest1.placeOrder();
    
    return 0;
}