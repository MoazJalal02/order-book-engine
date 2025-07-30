#include "catch.hpp"
#include "Order.hpp"

TEST_CASE("Order constructor initializes values correctly", "[Order]") {
    Order order(1, 2, OrderType::Limit, OrderSide::Buy, 5.00, 10.0);

    REQUIRE(order.getOrderId() == 1);
    REQUIRE(order.getUserId() == 2);
    REQUIRE(order.getOrderType() == OrderType::Limit);
    REQUIRE(order.getOrderSide() == OrderSide::Buy);
    REQUIRE(order.getInitialAmount() == 5.0);
    REQUIRE(order.getRemainingAmount() == order.getInitialAmount());
    REQUIRE(order.getPrice() == 10.0);
}

TEST_CASE("Order remaining amount can be updated correctly", "[Order]") {
    Order order(1, 2, OrderType::Market, OrderSide::Sell, 5.00, 10.0);
    
    order.setRemainingAmount(3.0);
    REQUIRE(order.getRemainingAmount() == 3.0);

    order.setRemainingAmount(0.0);
    REQUIRE(order.getRemainingAmount() == 0.0);
}