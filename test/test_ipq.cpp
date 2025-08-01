#include <catch2/catch_all.hpp>
#include "IndexedProrityQueue.hpp"

TEST_CASE("IndexedPriorityQueue", "[IndexedPriorityQueue]") {
    
    SECTION("Correctly insert and retrieve elements") {
        IndexedPriorityQueue queue(false);
        Order order1(1, 1, OrderType::Limit, OrderSide::Buy, 100.0, 50.0);
        Order order2(2, 2, OrderType::Limit, OrderSide::Buy, 80.0, 40.0);
        
        queue.insert(order1);
        queue.insert(order2);

        REQUIRE(queue.top() == 1);
    }

    SECTION("Correctly remove elements") {
        IndexedPriorityQueue queue(true);
        Order order1(1, 1, OrderType::Limit, OrderSide::Sell, 100.0, 50.0);
        queue.insert(order1);
        queue.remove(1);

        REQUIRE(queue.empty() == true);
    }

    SECTION("Check if heap contains an element") {
        IndexedPriorityQueue queue(false);
        Order order1(1, 1, OrderType::Limit, OrderSide::Buy, 100.0, 50.0);
        queue.insert(order1);

        REQUIRE(queue.contains(1) == true);
        REQUIRE(queue.contains(2) == false);
    }

    SECTION("Check the top after removing element from min-heap") {
        IndexedPriorityQueue queue(true);
        Order order1(1, 1, OrderType::Limit, OrderSide::Sell, 100.0, 37.5);
        Order order2(2, 2, OrderType::Limit, OrderSide::Sell, 80.0, 40.0);
        Order order3(3, 2, OrderType::Limit, OrderSide::Sell, 70.0, 35.0);
        
        queue.insert(order1);
        queue.insert(order2);
        queue.insert(order3);

        REQUIRE(queue.top() == 3);
        queue.remove(3);

        REQUIRE(queue.top() == 1);
    }

    SECTION("Check the top after removing element from max-heap") {
        IndexedPriorityQueue queue(false);
        Order order1(1, 1, OrderType::Limit, OrderSide::Buy, 100.0, 50.0);
        Order order2(2, 2, OrderType::Limit, OrderSide::Buy, 80.0, 40.0);
        Order order3(3, 2, OrderType::Limit, OrderSide::Buy, 70.0, 35.0);
        
        queue.insert(order1);
        queue.insert(order2);
        queue.insert(order3);

        REQUIRE(queue.top() == 1);
        queue.remove(1);

        REQUIRE(queue.top() == 2);
    }
}