#ifndef ALTOOLSET_DEVICE_HPP
#define ALTOOLSET_DEVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/alut.h>

#include "altoolset/context.hpp"

namespace altoolset {

    class Device
    {
    private:
        ALCenum error = AL_NO_ERROR;
        ALCdevice *device = NULL;
        std::string deviceName;

        bool isOpened = false;
    public:
        Device(const char* deviceName);

        ~Device();

        ALuint getError() const { return this->error; }
        std::string getErrorStr() const { return alutGetErrorString(this->error); }

        bool open();

        std::shared_ptr<Context> createContext();

        ALCint getDeviceRate();

        static std::vector<std::string> listAudioDevices()
        {
            std::vector<std::string> list{};
            if (alcIsExtensionPresent(NULL, "ALC_enumeration_EXT") == AL_FALSE)
            {
                std::cerr << "Listing error: Enumeration is disabled" << std::endl;
                return list;
            }
            const ALCchar *devices;
            if (alcIsExtensionPresent(NULL, "ALC_enumerate_all_EXT") == AL_TRUE)
                devices = (char *)alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
            else
                devices = (char *)alcGetString(NULL, ALC_DEVICE_SPECIFIER);

            size_t len = 0;
            const ALCchar *device = devices, *next = devices + 1;
            for (; device && *device != '\0' && next && *next != '\0';) {
                std::string sdev = device;
                len = sdev.size();
                list.push_back(std::move(sdev));
                device += (len + 1);
                next += (len + 2);
            }
            return list;
        }
    };
}

#endif
