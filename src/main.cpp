#include <iostream>
#include "../include/OrderBook.hpp"

using namespace std;

int main(){
    OrderBook orderBookTest;

    Order order1(ASK, 3.0, 4);
    Order order2(ASK, 3.1, 2);
    Order order3(BID, 3.2, 7);
    
    
    cout << "Basic Match" << endl;
    
    orderBookTest.placeOrder(order1);
    orderBookTest.placeOrder(order2);
    orderBookTest.placeOrder(order3);

    cout << endl << endl;
    cout << "Unmatched " << endl;
    Order order4(ASK, 3.5, 2);
    orderBookTest.placeOrder(order4);

    cout << endl << endl;
    cout << "Partial Match" << endl;
    Order order5(BID, 3.5, 1);
    orderBookTest.placeOrder(order5);

    cout << endl << endl;
    cout << "Final Orders Satus" << endl;
    orderBookTest.displayOrders();
    return 0;
}