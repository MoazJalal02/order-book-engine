#include "OrderBook.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("OrderBook Initialization", "[Orderbook Functionality]") {
    
    SECTION("Initial order book is empty") {
        OrderBook orderBook;
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 0);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 0);
    }

    SECTION("Initializing order book with orders") {
        vector<Order> initialOrders = {
            Order(1, 2, OrderType::Limit, OrderSide::Buy, 100.0, 50.0),
            Order(2, 2, OrderType::Limit, OrderSide::Sell, 80.0, 40.0),
            Order(3, 3, OrderType::Limit, OrderSide::Buy, 150.0, 60.0),
            Order(4, 3, OrderType::Market, OrderSide::Sell, 120.0)
        };

        OrderBook orderBookWithInitialOrders(initialOrders);

        REQUIRE(orderBookWithInitialOrders.getOrdersCount(OrderSide::Buy) == 2);
        REQUIRE(orderBookWithInitialOrders.getVolumeAtPrice(OrderSide::Buy, 50.0) == 100.0);
        REQUIRE(orderBookWithInitialOrders.getVolumeAtPrice(OrderSide::Buy, 60.0) == 150.0);
        REQUIRE(orderBookWithInitialOrders.getOrdersCount(OrderSide::Sell) == 2);
        REQUIRE(orderBookWithInitialOrders.getVolumeAtPrice(OrderSide::Sell, 40.0) == 80.0);
        REQUIRE(orderBookWithInitialOrders.getVolumeAtPrice(OrderSide::Sell, 0.00) == 120.0);
    }
}

TEST_CASE("Placing limit orders", "[Orderbook Functionality]") {
    OrderBook orderBook;

    SECTION("Placing a buy limit order updates the order book correctly") {
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 0);

        orderBook.placeOrder(1, OrderType::Limit, OrderSide::Buy, 100.0, 50.0);

        REQUIRE(orderBook.hasOrder(1) == true);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 1);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 50.0) == 100.0);
    }
    
    SECTION("Placing a sell limit order updates the order book correctly") {
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 0);
    
        orderBook.placeOrder(1, OrderType::Limit, OrderSide::Sell, 80.0, 40.0);
    
        REQUIRE(orderBook.hasOrder(1) == true);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 1);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 40.0) == 80.0);
    }

    SECTION("Placing a limit order with invalid amount throws an exception") {
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Limit, OrderSide::Buy, 0.0, 50.0), invalid_argument);
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Limit, OrderSide::Buy, -10.0, 50.0), invalid_argument);
    }

    SECTION("Placing a limit order with invalid price throws an exception") {
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Limit, OrderSide::Buy, 100.0, 0.0), invalid_argument);
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Limit, OrderSide::Sell, 100.0, -5.0), invalid_argument);
    }
}

TEST_CASE("Placing market orders", "[Orderbook Functionality]") {
    OrderBook orderBook;

    SECTION("Placing a market order with no mathcing orders gets destoried") {
        orderBook.placeOrder(1,OrderType::Market, OrderSide::Buy, 50.0);
   
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 0);
        REQUIRE(orderBook.hasOrder(1) == false);
    }

    SECTION("Placing a market order with invalid amount throws an exception") {
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Market, OrderSide::Buy, 0.0), invalid_argument);
        REQUIRE_THROWS_AS(orderBook.placeOrder(1, OrderType::Market, OrderSide::Buy, -5.0), invalid_argument);
    }
}

TEST_CASE("Order mathcing and fulfillment", "[Orderbook Functionality]") {    
    SECTION("Complete order fulfillment removes both orders") {
        vector<Order> initialOrders = {
            Order(1, 2, OrderType::Limit, OrderSide::Buy, 50.0, 50.0),
        };

        OrderBook orderBook(initialOrders);
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 1);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 50.0) == 50.0);

        orderBook.placeOrder(2, OrderType::Limit, OrderSide::Sell, 50.0, 40.0);
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 0);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 50.0) == 0.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 40.0) == 00.0);
    }
    
    SECTION("Partial order fulflilment updates the order book correctly") {
        vector<Order> initialOrders = {
            Order(1, 1, OrderType::Limit, OrderSide::Sell, 100.0, 40.0),
        };

        OrderBook orderBook(initialOrders);

        orderBook.placeOrder(2, OrderType::Limit, OrderSide::Buy, 80.0, 42.5);
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 1);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 40.0) == 20.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 42.5) == 0.0);
    }
    
    SECTION("Partially fulfilling multiple limit orders with higher price priority") {
        vector<Order> initialOrders = {
            Order(2, 2, OrderType::Limit, OrderSide::Buy, 80.0, 40.5),
            Order(1, 2, OrderType::Limit, OrderSide::Buy, 40.0, 42.5),
            Order(3, 3, OrderType::Limit, OrderSide::Sell, 70.0, 44.0),
        };

        OrderBook orderBook(initialOrders);
        
        orderBook.placeOrder(1, OrderType::Limit, OrderSide::Sell, 10.0, 40.0);
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 1);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 2);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 40.0) == 0.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 40.5) == 80.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 42.5) == 30.0);
    }

    SECTION("FIFO priority, matching orders with same price") {
        vector<Order> initialOrders = {
            Order(1, 1, OrderType::Limit, OrderSide::Buy, 50.0, 42.5),
            Order(2, 2, OrderType::Limit, OrderSide::Buy, 30.0, 42.5),
        };
        
        OrderBook orderBook(initialOrders);
        
        orderBook.placeOrder(3, OrderType::Limit, OrderSide::Sell, 30.0, 40.0);
        
        REQUIRE(orderBook.hasOrder(2) == true);
        REQUIRE(orderBook.getOrdersCount(OrderSide::Buy) == 2);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Buy, 42.5) == 50.0);
    }
    
    SECTION("Market order complete fulfillment") {
        vector<Order> initialOrders = {
            Order(1, 2, OrderType::Limit, OrderSide::Sell, 50.0, 80.0),
        };
    
        OrderBook orderBook(initialOrders);
        
        orderBook.placeOrder(1, Market, Buy, 30.0);

        REQUIRE(orderBook.hasOrder(2) == false);
        REQUIRE(orderBook.getOrdersCount(Buy) == 0);
        REQUIRE(orderBook.getOrdersCount(Sell) == 1);
        REQUIRE(orderBook.getVolumeAtPrice(Sell, 80.0) == 20);
    }
    
    SECTION("Market order partial fulfillment, order destroyed after partial fulfillment") {
        vector<Order> initialOrders = {
            Order(1, 2, OrderType::Limit, OrderSide::Buy, 20.0, 80.0),
        };

    
        OrderBook orderBook(initialOrders);

        orderBook.placeOrder(1, Market, Sell, 30.0);

        REQUIRE(orderBook.hasOrder(1) == false);
        REQUIRE(orderBook.getOrdersCount(Buy) == 0);
        REQUIRE(orderBook.getOrdersCount(Sell) == 0);
        REQUIRE(orderBook.getVolumeAtPrice(Sell, 80.0) == 0.0);
    }

    SECTION("Large market order matches multiple price levels, mathcing the best price first") {
        vector<Order> initialOrders = {
            Order(1, 1, OrderType::Limit, OrderSide::Sell, 40.0, 102.0),
            Order(2, 2, OrderType::Limit, OrderSide::Sell, 30.0, 101.0), 
            Order(3, 3, OrderType::Limit, OrderSide::Sell, 50.0, 100.0),
        };
        
        OrderBook orderBook(initialOrders);
        
        orderBook.placeOrder(4, OrderType::Market, OrderSide::Buy, 90.0);
        
        REQUIRE(orderBook.getOrdersCount(OrderSide::Sell) == 1);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 100.0) == 0.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 101.0) == 0.0);
        REQUIRE(orderBook.getVolumeAtPrice(OrderSide::Sell, 102.0) == 30.0);
    }
}

TEST_CASE("Order cancellation", "[Orderbook Functionality]") {
    vector<Order> initialOrders = {
            Order(1, 2, OrderType::Limit, OrderSide::Buy, 20.0, 80.0),
    };    
    
    OrderBook orderBook(initialOrders);

    SECTION("Successfully canceling existing order by owner") {
        REQUIRE(orderBook.hasOrder(1) == true);
        
        bool canceled = orderBook.cancelOrder(2, 1);

        REQUIRE(canceled == true);
        REQUIRE(orderBook.hasOrder(1) == false);
    }

    SECTION("Cannot canceling non-existing order") {
        REQUIRE_THROWS_AS(orderBook.cancelOrder(1, 999), invalid_argument);
    }

    SECTION("Cannot canceling order owned by different user") {
        REQUIRE_THROWS_AS(orderBook.cancelOrder(3, 1), invalid_argument);
    }
}


TEST_CASE("Performance Benchmarks", "[benchmark]") {
    
    BENCHMARK("Placing 10,000 orders") {
        OrderBook ob;
        
        for (int i = 0; i < 10000; ++i)
        ob.placeOrder(i, OrderType::Limit, OrderSide::Buy, 10.0, 100.0 + i);
    };
    
    BENCHMARK("Canceling 5,000 orders") {
        OrderBook ob;
        
        for (int i = 0; i < 5000; ++i) {
            ob.placeOrder(i, OrderType::Limit, OrderSide::Buy, 10.0, 100.0 + i * 0.01);
        }

        return [&ob]() {
            for (int i = 0; i < 5000; ++i) {
                ob.cancelOrder(i, i);
            }
        };
    };

    BENCHMARK("Market order matching against deep book") {
        OrderBook ob;

        for (int i = 0; i < 1000; ++i) {
            ob.placeOrder(i, OrderType::Limit, OrderSide::Sell, 10.0, 100.0 + i * 0.01);
        }

        return [&ob]() {
            ob.placeOrder(10000, OrderType::Market, OrderSide::Buy, 5000.0);
        };
    };

    BENCHMARK("Mixed trading scenario") {
        OrderBook ob;

        int orderId = 0;
        
        return [&ob, &orderId]() {

            for (int i = 0; i < 100; ++i) {
                ob.placeOrder(orderId++, OrderType::Limit, OrderSide::Buy, 10.0, 100.0 + i * 0.01);
                ob.placeOrder(orderId++, OrderType::Limit, OrderSide::Sell, 12.0, 101.0 + i * 0.01);
                if (i % 10 == 0 && orderId > 10) {
                    ob.cancelOrder(orderId-10, orderId-10);
                }
            }
        };
    };
    
}

