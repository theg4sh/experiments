#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "altoolset/context.hpp"
#include "altoolset/wav_player.hpp"

namespace altoolset {

WavPlayer::WavPlayer(std::string waveFile):
    waveFile(waveFile)
{}

WavPlayer::~WavPlayer() {
    alDeleteSources(1, &this->source);
    alDeleteBuffers(1, &this->buffer);
}

bool WavPlayer::init() {
    alutLoadWAVFile((ALbyte*)this->waveFile.c_str(), &this->format,
            &this->data, &this->size, &this->freq, AL_FALSE);
    //std::cerr << "Loaded wav file: " << this->waveFile << " Size:" << this->size << std::endl;

    alGenBuffers((ALuint)1, &this->buffer);
    alGenSources((ALuint)1, &this->source);

    alSourcef (this->source, AL_PITCH, 1);
    alSourcef (this->source, AL_GAIN,  1);
    alSource3f(this->source, AL_POSITION, 0, 0, 0);
    alSource3f(this->source, AL_VELOCITY, 0, 0, 0);
    alSourcei (this->source, AL_LOOPING, this->loop);

    alBufferData(this->buffer, this->format, this->data, this->size, this->freq);

    alSourcei(this->source, AL_BUFFER, this->buffer);
    this->initialised = true;
    return true;
}

void WavPlayer::play() {
    if (!this->initialised) {
        this->init();
    }
    alSourcePlay(this->source);
}

void WavPlayer::stop() {
    if (!this->initialised) {
        return;
    }
    alSourceStop(this->source);
}

void WavPlayer::join() {
    ALint source_state;
    do {
        std::this_thread::sleep_for( std::chrono::milliseconds(10) );
        alGetSourcei(this->source, AL_SOURCE_STATE, &source_state);
    } while(source_state == AL_PLAYING);
}

}