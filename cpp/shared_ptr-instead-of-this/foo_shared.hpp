#pragma once

#include "bar_shared.hpp"

class FooShared {
private:
    boost::asio::io_service& ios;
    std::shared_ptr<BarShared> bar;
public:
    FooShared(boost::asio::io_service& ios): ios(ios) {}

    void makeTheBar() {
        if (this->bar != nullptr) {
            this->bar->deactivate();
        }
        this->bar = std::make_shared<BarShared>(this->ios);
        this->bar->init();
        this->bar->tripCall();

        std::stringstream msg;
        msg << "New Bar have " << this->bar.use_count() << " reference(s)" << std::endl;
        std::cout << msg.str();
    }
};

