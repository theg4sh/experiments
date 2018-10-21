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
    this->queuePlayers.clear();
    if (this->context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(this->context);
    }
}

void Context::setCurrent() {
    alcMakeContextCurrent(this->context);
}

std::shared_ptr<Player> Context::createWavPlayer(std::string waveFile) {
    auto wp = std::make_shared<WavPlayer>(waveFile);
    wp->init();
    auto p = std::shared_ptr<Player>(wp);
    this->wavPlayers.push_back(std::move(wp));
    return p;
}

std::shared_ptr<Player> Context::createQueuePlayer(Generator& generator) {
    auto wp = std::make_shared<QueuePlayer>(generator.getFrequency(), generator);
    wp->init();
    this->queuePlayers.push_back(wp);
    return wp;
}

}
