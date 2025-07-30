#include "catch.hpp"
#include "OrderBook.hpp"

TEST_CASE("PLace limit orders", "[Orderbook]") {
    OrderBook orderBook;

    SECTION("Place buy limit order") {
        WHEN("A buy limit order is placed") {
            orderBook.placeOrder(1, OrderType::Limit, OrderSide::Buy, 100.0, 50.0);
            THEN("The order should be added to the buy orders queue") {
                REQUIRE(orderBook.getBuyOrders().size() == 1);
            }
        }
        
        // Check if orders are placed correctly
        REQUIRE(orderBook.getBuyOrders().size() == 3);
    }

    SECTION("Place sell order") {
        orderBook.placeOrder(1, OrderType::LIMIT, OrderSide::SELL, 100.0, 60.0);
        orderBook.placeOrder(2, OrderType::LIMIT, OrderSide::SELL, 200.0, 65.0);
        orderBook.placeOrder(3, OrderType::LIMIT, OrderSide::SELL, 150.0, 62.5);
        
        // Check if orders are placed correctly
        REQUIRE(orderBook.getSellOrders().size() == 3);
    }
}