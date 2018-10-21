#ifndef ALTOOLSET_GENERATOR_HPP
#define ALTOOLSET_GENERATOR_HPP

#include <queue>
#include <vector>
#include <limits>
#include <AL/al.h>
#include <AL/alc.h>

namespace altoolset {

    class Generator
    {
    private:
        using BufferType = std::vector<short>;
        BufferType buffer;
    protected:

        ALsizei size;
        ALCint frequency;
        ALCint deviceRate;

        BufferType& getBuffer() { return this->buffer; }

        ALCint getBufferMaxValue() { return std::numeric_limits<short>::max(); }

    public:
        Generator(ALsizei bufferSize, ALCint frequency, ALCint deviceRate):
            buffer(bufferSize), size(bufferSize), frequency(frequency), deviceRate(deviceRate)
        {}

        ~Generator() = default;

        ALCint getFrequency() const { return this->frequency; }
        ALCint getDeviceRate() const { return this->deviceRate; }
        const short* getData() const { return this->buffer.data(); }
        ALsizei getDataSize() const { return this->size; }

        virtual void init() {};
        virtual void generate() = 0;
    };

}

#endif
