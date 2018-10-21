#include <altoolset/sin_generator.hpp>

#include <limits>

namespace altoolset {

void SinGenerator::init()
{
    auto& buff = this->getBuffer();
    auto size = this->getDataSize();

    buff.clear();
    buff.reserve(size);
}

void SinGenerator::generate()
{
    ALdouble g = 1.0f * (this->getBufferMaxValue()-1);
    ALdouble circle = 2.0*M_PI;
    ALdouble smps_per_cycle = (ALdouble)this->getFrequency()/this->getDeviceRate() * circle;
    auto& buff = this->getBuffer();
    auto size = this->getDataSize();
    ALfloat angle=this->lastOffset;
    for (ALCint i=0; i<size; i++) {
        angle = ((ALfloat)this->lastOffset+i)*smps_per_cycle;
        buff[i] = (ALfloat)(std::sin(angle) * g);
    }
    this->lastOffset=size-1;
}

}

