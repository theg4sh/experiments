#ifndef ALTOOLSET_SIN_GENERATOR_HPP
#define ALTOOLSET_SIN_GENERATOR_HPP

#include <iostream>
#include <cmath>
#include <cstring>

#include "altoolset/generator.hpp"

namespace altoolset {

    class SinGenerator : public Generator
    {
        ALsizei size, freq;
        ALenum format;
        ALvoid *data;

        ALfloat lastOffset = 0;

    public:
        SinGenerator(std::size_t bufferSize, ALCint frequency, ALCint deviceRate):
            Generator(bufferSize, frequency, deviceRate) {}

        virtual void init() override;
        virtual void generate() override;
    };

}

#endif
