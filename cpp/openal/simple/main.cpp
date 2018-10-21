#include <iostream>
#include <stack>
#include <vector>
#include <thread>
#include <AL/al.h>
#include <AL/alc.h>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include "altoolset/altoolset.hpp"
#include "altoolset/sin_generator.hpp"

namespace po=boost::program_options;

void WavPlay(std::shared_ptr<altoolset::Context> ctx, size_t count, const char* filename)
{
    std::stack<std::weak_ptr<altoolset::Player>> keeper;
    for (size_t i = 0; i < count; i++) {
        auto wp = ctx->createWavPlayer(filename);
        wp->play();
        keeper.push(wp);
        std::this_thread::sleep_for( std::chrono::milliseconds(900) );
    }
    for (;!keeper.empty();) {
        auto wpweak = keeper.top();
        keeper.pop();
        if (auto wp = wpweak.lock()) {
            wp->join();
        }
        std::cerr << "Done" << std::endl;
    }
}

void QueuePlay(altoolset::Device& dev, ALCint frequency, std::chrono::milliseconds time, std::shared_ptr<altoolset::Context> ctx)
{
    altoolset::SinGenerator generator(dev.getDeviceRate(), frequency, dev.getDeviceRate());
    auto player = ctx->createQueuePlayer(generator);
    player->play();
    std::this_thread::sleep_for(time);
    player->stop();
}

int main(int argc, char** argv)
{
    po::options_description desc("General options");
    std::string runType;
    desc.add_options()
        ("help,h", "Print this text")
        ("type,t", po::value(&runType), "Command type: wav|file, freq");

    std::string filePath;
    po::options_description wavDesc("Play wav file");
    wavDesc.add_options()
        ("file,f", po::value<std::string>(&filePath), "Path to wav file");

    int genFrequency;
    po::options_description sinDesc("Generate sinusoidal");
    sinDesc.add_options()
        ("freq,f", po::value(&genFrequency), "Sound frequency");

    po::variables_map vm;


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

    auto ctx = device.createContext();
    if (!ctx) {
        std::cerr << "main/context: " << device.getError() << std::endl;
        return 2;
    }
    ctx->setCurrent();

    try {
        po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        po::store(parsed, vm);
        po::notify(vm);
        if (runType == "wav" || runType == "file") {
            desc.add(wavDesc);
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (!vm.count("file")) {
                std::cerr << "File not found: '" << filePath << "'" << std::endl;
                std::cerr << desc << std::endl;
                return 1;
            }
            //filePath = vm["file"].as<std::string>();
            auto fp = boost::filesystem::absolute(boost::filesystem::path(filePath));
            std::cout << fp << std::endl;
            WavPlay(ctx, 1, fp.c_str());
        }
        else if (runType == "freq") {
            desc.add(sinDesc);
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (!vm.count("freq")) {
                std::cerr << desc << std::endl;
                return 1;
            }
            QueuePlay(device, genFrequency, std::chrono::seconds(1), ctx);
        }
        else
        {
            desc.add(wavDesc).add(sinDesc);
            std::cout << desc << std::endl;
        }
    } catch(std::exception &e) {
        desc.add(wavDesc).add(sinDesc);
        std::cout << desc << std::endl;
    }
    return 0;
}
