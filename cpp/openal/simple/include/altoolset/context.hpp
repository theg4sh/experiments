#ifndef ALTOOLSET_CONTEXT_HPP
#define ALTOOLSET_CONTEXT_HPP

#include <memory>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "altoolset/wav_player.hpp"

namespace altoolset {

    class Context
    {
        ALCcontext* context;
        ALCenum error = AL_NO_ERROR;

        std::vector<std::shared_ptr<WavPlayer>> wavPlayers;
    public:
        Context(ALCcontext* context);

        ~Context();

        ALuint getError() const { return this->error; }
        std::string getErrorStr() const { return alutGetErrorString(this->error); }

        ALCcontext* get() const { return this->context; }

        void setCurrent();

        std::weak_ptr<WavPlayer> createWavPlayer(std::string waveFile);
    };

}

#endif
