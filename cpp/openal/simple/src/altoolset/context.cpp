#include <memory>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "altoolset/context.hpp"
#include "altoolset/wav_player.hpp"

namespace altoolset {

Context::Context(ALCcontext* context): context(context) {}

Context::~Context() {
    this->wavPlayers.clear();
    if (this->context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(this->context);
    }
}

void Context::setCurrent() {
    alcMakeContextCurrent(this->context);
}

std::weak_ptr<WavPlayer> Context::createWavPlayer(std::string waveFile) {
    auto wp = std::make_shared<WavPlayer>(waveFile);
    wp->init();
    auto p = std::weak_ptr<WavPlayer>(wp);
    this->wavPlayers.push_back(std::move(wp));
    return p;
}

}
