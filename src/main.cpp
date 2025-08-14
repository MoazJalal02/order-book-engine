#include "OrderBook.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void printMenu();

void printOrderBook(const OrderBook& orderBook);

int main() {
    vector<Order> initialOrders = {
        Order(1, 1, OrderType::Limit, OrderSide::Buy, 300.0, 150.00),
        Order(2, 2, OrderType::Limit, OrderSide::Buy, 250.0, 149.50),
        Order(3, 3, OrderType::Limit, OrderSide::Buy, 270.0, 149.00),
        Order(4, 4, OrderType::Limit, OrderSide::Buy, 350.0, 148.50),
        Order(5, 5, OrderType::Limit, OrderSide::Buy, 400.0, 148.00),

        Order(6, 6, OrderType::Limit, OrderSide::Sell, 200.0, 150.50),
        Order(7, 7, OrderType::Limit, OrderSide::Sell, 180.0, 151.00),
        Order(8, 8, OrderType::Limit, OrderSide::Sell, 220.0, 151.50),
        Order(9, 9, OrderType::Limit, OrderSide::Sell, 150.0, 152.00),
        Order(10, 10, OrderType::Limit, OrderSide::Sell, 100.0, 152.50)
    };
    
    OrderBook orderBook(initialOrders);

    int choice;
    int userId = 1;

    while (true) {
        orderBook.printOrderBook();
        printMenu();
        cin >> choice;

        switch (choice) {
            case 0: {
                cout << "Exiting the program..." << endl;
                return 0;
            }
            case 1: {
                double price, volume;
                bool cancelled = false;
                
                while(true) {
                    cout << "Enter price: $";
                    string input;
                    cin >> input;
                    
                    if(input == "c" || input == "C") {
                        cout << "Cancelling...\n";
                        cancelled = true;
                        break;
                    }
                    
                    try {
                        price = stod(input);
                        break;
                    } catch (const invalid_argument&) {
                        cout << "Invalid input! Please enter a valid number or 'c' to cancel.\n";
                    }
                }

                if(cancelled) break;

                while(true) {
                    cout << "Enter volume: ";
                    string input;
                    cin >> input;
                        
                    if(input == "c" || input == "C") {
                        cout << "Cancelling...\n";
                        cancelled = true;
                        break;
                    }
                        
                    try {
                        volume = stod(input);
                        break;
                    } catch (const invalid_argument&) {
                        cout << "Invalid input! Please enter a valid number or 'c' to cancel.\n";
                        }
                    }
                
                    if(cancelled) break;
                    
                    try {
                        orderBook.placeOrder(100, OrderType::Limit, OrderSide::Buy, volume, price);
                    } catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    
                    break;
                }
                
            case 2: {
                double price, volume;
                bool cancelled = false;

                while(true) {
                    cout << "Enter price: $";
                    string input;
                    cin >> input;
                    
                    if(input == "c" || input == "C") {
                        cout << "Cancelling...\n";
                        cancelled = true;
                        break;
                    }
                    
                    try {
                        price = stod(input);
                        break;
                    } catch (const invalid_argument&) {
                        cout << "Invalid input! Please enter a valid number or 'c' to cancel.\n";
                    }
                }

                if(cancelled) break;
                
                while(true) {
                    cout << "Enter volume: ";
                    string input;
                    cin >> input;
                        
                    if(input == "c" || input == "C") {
                        cout << "Cancelling...\n";
                        cancelled = true;
                        break;
                    }
                        
                    try {
                        volume = stod(input);
                        break;
                    } catch (const invalid_argument&) {
                        cout << "Invalid input! Please enter a valid number or 'c' to cancel.\n";
                    }
                }

                if(cancelled) break;

                try {
                    orderBook.placeOrder(101, OrderType::Limit, OrderSide::Sell, volume, price);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                
                break;
            }
            
            case 3: {
                char side;
                double volume;
                bool cancelled = false;
                cout << "Buy or Sell? (B/S): ";
                cin >> side;
                if (toupper(side) != 'B' && toupper(side) != 'S') {
                    cout << "Invalid choice! Please enter 'B' for Buy or 'S' for Sell.\n";
                    break;
                }
                
                cout << "Enter volume: ";
                cin >> volume;
                while(true) {
                    if(cin.fail() || volume <= 0) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a positive number for volume.\n";
                        cout << "Enter volume: ";
                        cin >> volume;
                    } else {
                        break;
                    }
                }
                
                try {
                    OrderSide orderSide = (toupper(side) == 'B') ? OrderSide::Buy : OrderSide::Sell;
                    orderBook.placeOrder(102, OrderType::Market, orderSide, volume);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                
                break;
            }
            
            default:
                cout << "Invalid choice!" << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}

void printMenu() {
    cout << "=== TRADING MENU ===" << endl;
    cout << "1. Place Buy Limit Order" << endl;
    cout << "2. Place Sell Limit Order" << endl;
    cout << "3. Place Market Order" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}
