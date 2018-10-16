#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>

class Bar {
private:
    boost::asio::io_service& ios;
    std::atomic_bool readyToDie;
    static uint32_t globalId;
    uint32_t oid;
    uint32_t counts = 0; // Just to break infinite loop
public:
    Bar(boost::asio::io_service& ios):
        ios(ios),
        readyToDie(false),
        oid(globalId++) {}

    void tripCall() {
        if (!readyToDie && this->counts < 20) {
            std::cout << "Trip called " << this->counts++ << " from " << this->oid << std::endl;
            this->ios.post(std::bind(&Bar::tripCall, this));
        }
    }

    void letDie() {
        this->readyToDie = true;
    }
};

uint32_t Bar::globalId = 0;


/**
 * FooUnique shows the example how you could shoot in your leg
 */
class FooUnique {
private:
    boost::asio::io_service& ios;
    std::unique_ptr<Bar> bar = nullptr;
public:
    FooUnique(boost::asio::io_service& ios): ios(ios) {}

    void takeTheBar() {
        this->bar = std::make_unique<Bar>(this->ios);
        this->bar->tripCall();
    }
};

class FooShared {
private:
    boost::asio::io_service& ios;
    std::shared_ptr<Bar> bar = nullptr;
public:
    FooShared(boost::asio::io_service& ios): ios(ios) {}

    void makeTheBar() {
        auto bar = std::make_shared<Bar>(this->ios);
        bar->tripCall();
        if (this->bar != nullptr) {
            // Why we should use that?
            // We expect that bar, which was created first, will stop process when
            // we replaces shared_ptr<Bar>, but we already have a pointers to first copy
            // inside of std::bind, so, we should say to old Bar to let he stop copying himself.
            this->bar->letDie();
        }
        this->bar = std::move(bar);
    }
};

int main(int, char**)
{
    boost::asio::io_service ios;
    FooShared foo(ios);
    foo.makeTheBar();
    foo.makeTheBar();
    ios.run();
    return 0;
}
