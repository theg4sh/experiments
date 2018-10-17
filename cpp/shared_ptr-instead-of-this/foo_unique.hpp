#pragma once

#include "bar_unique.hpp"

/**
 * FooUnique shows the example how you could shoot in your leg
 * If you try to use that implementation you'll get SIGSEGV
 * because `this` will reference on destructed object in Bar::tripCall.
 */
class FooUnique {
private:
    boost::asio::io_service& ios;
    std::unique_ptr<BarUnique> bar = nullptr;
public:
    FooUnique(boost::asio::io_service& ios): ios(ios) {}

    void makeTheBar() {
        this->bar = std::make_unique<BarUnique>(this->ios);
        this->bar->tripCall();
    }
};

