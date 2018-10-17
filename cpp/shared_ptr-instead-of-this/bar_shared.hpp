#pragma once 

#include <iostream>
#include <sstream>
#include <memory>
#include <thread>
#include <chrono>
#include <deque>

#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>

class BarShared: public std::enable_shared_from_this<BarShared>
{
private:
    boost::asio::io_service& ios;

    std::weak_ptr<BarShared> selfPtr;
private:
    // Helping variables

    static uint32_t globalId;
    uint32_t oid;
    uint32_t counts = 0; // Just to break infinite loop

    std::string objInfo;
public:

    using std::enable_shared_from_this<BarShared>::shared_from_this;

    BarShared(boost::asio::io_service& ios):
        enable_shared_from_this(),
        ios(ios),
        oid(globalId++)
    {
        std::stringstream msg;
        msg << "Bar[" << this << ":" << this->oid << "]";
        this->objInfo = msg.str();
        msg << " constructed" << std::endl;
        std::cout << msg.str();
    }

    void init() {
        // In constructor we don't have initialized object yet,
        // so, required to continue initialization here
        this->selfPtr = shared_from_this();
    }

    ~BarShared() {
        std::stringstream msg;
        msg << this->objInfo << " destructed" << std::endl;
        std::cout << msg.str();
    }

    void deactivate() {
        this->selfPtr.reset();

        std::stringstream msg;
        msg << this->objInfo << " deactivated" << std::endl;
        std::cout << msg.str();
    }

    void tripCall() {
        if (auto self = this->selfPtr.lock()) {
            std::stringstream msg;
            msg << this->objInfo << "] Trip called times: " << ++this->counts << std::endl;
            std::cout << msg.str();
            if (this->counts < 20) {
                this->ios.post(std::bind(&BarShared::tripCall, self));
            }
        } else {
            std::stringstream msg;
            msg << this->objInfo << "] I'm dying with trip calls " << this->counts \
                << " and reference(s) to me: " << this->selfPtr.use_count() << std::endl;
            std::cout << msg.str();
        }
    }
};

// Note: that could be safe only with `#pragma once`
uint32_t BarShared::globalId = 0;
