#include <iostream>
#include <stack>
#include <vector>
#include <thread>
#include <AL/al.h>
#include <AL/alc.h>

#include "altoolset/altoolset.hpp"

int main(int, char**)
{
    auto devicesList = altoolset::Device::listAudioDevices();
    if (devicesList.empty()) {
        std::cout << "Cannot found any audio device" << std::endl;
        return 99;
    }
    std::cout << "Devices list:" << std::endl;
    for (auto device : devicesList) {
        std::cout << "  " << device << std::endl;
    }

    altoolset::Device device(devicesList[0].c_str());
    if (!device.open()) {
        std::cerr << "main/open: " << device.getError() << std::endl;
        return 1;
    }

    {
        auto ctx = device.createContext();
        if (!ctx) {
            std::cerr << "main/context: " << device.getError() << std::endl;
            return 2;
        }
        ctx->setCurrent();
        std::stack<std::weak_ptr<altoolset::WavPlayer>> keeper;
        for (int i = 0; i < 1; i++) {
            // http://www.music.helsinki.fi/tmt/opetus/uusmedia/esim/a2002011001-e02.wav
            auto wpweak = ctx->createWavPlayer("a2002011001-e02.wav");
            if (auto wp = wpweak.lock()) {
                wp->play();
            }
            keeper.push(std::move(wpweak));
            std::this_thread::sleep_for( std::chrono::milliseconds(900) );
        }
        for (;!keeper.empty();) {
            auto wpweak = std::move(keeper.top());
            keeper.pop();
            if (auto wp = wpweak.lock()) {
                wp->join();
            }
            std::cerr << "Done" << std::endl;
        }
    }
    return 0;
}
