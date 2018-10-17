#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <deque>

#include "foo_shared.hpp"
#include "foo_unique.hpp"

void testShared()
{
    boost::asio::io_service ios;

    FooShared foo(ios);
    std::thread iosThread([&ios, &foo] {
            foo.makeTheBar();
            ios.run();
    });
    for (int i = 0; i<10; i++) {
        ios.post([&foo] {
            foo.makeTheBar();
        });
    }
    iosThread.join();
}

void testUnique()
{
    boost::asio::io_service ios;

    FooUnique foo(ios);
    std::thread iosThread([&ios, &foo] {
            foo.makeTheBar();
            ios.run();
    });
    for (int i = 0; i<10; i++) {
        ios.post([&foo] {
            foo.makeTheBar();
        });
    }
    iosThread.join();
}

int main(int, char**)
{
    testShared();
    testUnique();

    return 0;
}
