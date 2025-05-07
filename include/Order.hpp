#ifndef ORDER_H
#define ORDER_H
#include "./Enums.hpp"
#include <ctime>

class Order {
    private:
        static int nextOrderId;
        int orderId;
        Side orderType;
        double price;
        int initialVolume;
        int remainingVolume;
        time_t timeStamp;
    public:
        Order(Side orderType, double price, int initialVolume):
            orderId(nextOrderId++), orderType(orderType), price(price), initialVolume(initialVolume),
            remainingVolume(initialVolume), timeStamp(time(nullptr)) {}
        
        int getOrderId() const;        
        Side getOrderType() const;
        double getPrice() const;
        int getInitialVolume() const;
        int getRemainingVolume() const;
        time_t getTimeStamp() const;
        
        void setOrderId(int);        
        void setOrderType(Side);
        void setPrice(double);
        void setInitialVolume(int);
        void setRemainingVolume(int);
        void setTimeStamp(time_t);

        void displayOrder() const;

        bool operator<(const Order& other) const {
            return price < other.price; 
        }
};

#endif