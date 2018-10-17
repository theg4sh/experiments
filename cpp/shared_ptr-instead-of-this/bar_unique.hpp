#pragma once

#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>

// Warning: that class with usage of unique_ptr is not finished yet

class BarUnique
{
private:
    boost::asio::io_service& ios;
private:
    // Helping variables
    static uint32_t globalId;
    uint32_t oid;
    uint32_t counts = 0; // Just to break infinite loop

    std::string objInfo;
public:
    BarUnique(boost::asio::io_service& ios):
        ios(ios),
        oid(globalId++)
    {
        std::stringstream msg;
        msg << "Bar[" << this << ":" << this->oid << "]";
        this->objInfo = msg.str();
        msg << " constructed" << std::endl;
        std::cout << msg.str();
    }

    void tripCall() {
        std::stringstream msg;
        msg << this->objInfo << "] Trip called times: " << ++this->counts << std::endl;
        std::cout << msg.str();
        if (this->counts < 20) {
            this->ios.post(std::bind(&BarUnique::tripCall, this));
        }
#if false
        if (0) {
            std::stringstream msg;
            msg << this->objInfo << "] I'm dying with trip calls " << this->counts \
                << " and reference(s) to me: " << this->selfPtr.use_count() << std::endl;
            std::cout << msg.str();
        }
#endif
    }
};

// Note: that could be safe only with `#pragma once`
uint32_t BarUnique::globalId = 0;
