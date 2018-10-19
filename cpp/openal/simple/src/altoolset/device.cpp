#include <memory>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "altoolset/device.hpp"

namespace altoolset {

Device::Device(const char* deviceName):
    isOpened(false)
{
    if (deviceName != NULL) {
        this->deviceName = deviceName;
    }
}

Device::~Device()
{
    if (this->device) {
        alcMakeContextCurrent(NULL);
        alcCloseDevice(this->device);
    }
}

bool Device::open() {
    this->device = alcOpenDevice(NULL);
    this->error = alGetError();
    if (this->device != nullptr) {
        this->isOpened = true;
    }
    return this->isOpened;
}

std::shared_ptr<Context> Device::createContext()
{
    if (this->device == NULL) {
        return nullptr;
    }
    auto alctx = alcCreateContext(this->device, NULL);
    std::cerr << "Context: " << alctx << std::endl;
    auto ctx = std::make_shared<altoolset::Context>(alctx);
    return std::move(ctx);
}

} // namespace altoolset
