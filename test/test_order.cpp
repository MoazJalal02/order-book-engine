#include "Order.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("Order", "[Order]") {
    SECTION("Initializing order correctly") {
        Order order(1, 2, OrderType::Limit, OrderSide::Buy, 5.00, 10.0);
        
        REQUIRE(order.getOrderId() == 1);
        REQUIRE(order.getUserId() == 2);
        REQUIRE(order.getOrderType() == OrderType::Limit);
        REQUIRE(order.getOrderSide() == OrderSide::Buy);
        REQUIRE(order.getInitialAmount() == 5.0);
        REQUIRE(order.getRemainingAmount() == 5.0);
        REQUIRE(order.getPrice() == 10.0);
    }
    
    SECTION("Updating order remaining amount correctly") {
        Order order(1, 1, OrderType::Limit, OrderSide::Buy, 5.00, 10.0);
        
        order.setRemainingAmount(2.0);
        REQUIRE(order.getRemainingAmount() == 2.0);
    }
}
