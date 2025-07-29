#include "OrderBook.hpp"
#include <iostream>

using namespace std;

void showMenu();

int main() {
OrderBook orderBook;
    int choice;
    int userId = 1;

    while (true) {
        showMenu();
        std::cin >> choice;
        cout << endl;

        if (choice == 1) {
            int userId, side;
            double price, amount;
            cout << "Enter Side (1= Buy, 2 = Sell): ";
            cin >> side;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Amount: ";
            cin >> amount;

            orderBook.placeOrder(userId, OrderType::Limit, static_cast<OrderSide>(--side), amount, price);

        } else if (choice == 2) {
            int userId, side;
            double amount;
            cout << "Enter Side (1 = Buy, 2 = Sell): ";
            cin >> side;
            cout << "Enter Amount: ";
            cin >> amount;

            cout << endl << endl;
            orderBook.placeOrder(userId, OrderType::Market, static_cast<OrderSide>(--side), amount);

        } else if (choice == 3) {
            int userId, orderId;
            orderBook.listUserOrders(userId);

            cout << "Enter Order ID you want cancel: ";
            cin >> orderId;

            orderBook.cancelOrder(userId, orderId);

        } else if (choice == 4) {
            orderBook.displayOrderBook();

        } else if (choice == 5) {
            break;

        } else {
            cout << "Invalid option, try again.\n";
        }
    }

    return 0;
}

void showMenu() {
    cout << "\n=== Order Book Menu ===\n";
    cout << "1. Place Limit Order\n";
    cout << "2. Place Market Order\n";
    cout << "3. Cancel Order\n";
    cout << "4. View Order Book\n";
    cout << "5. Exit\n" << endl;
    cout << "Choose an option: ";
}
