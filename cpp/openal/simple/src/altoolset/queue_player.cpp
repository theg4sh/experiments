
#include <AL/al.h>

#include "altoolset/generator.hpp"
#include "altoolset/queue_player.hpp"

namespace altoolset {

QueuePlayer::~QueuePlayer()
{
    alSourcei(this->source, AL_BUFFER, 0);
    alDeleteSources(1, &this->source);
    alDeleteBuffers(QueuePlayer::BUFFERS_COUNT, this->buffers);
}

bool QueuePlayer::init()
{
    alGenSources(1, &this->source);
    alGenBuffers(QueuePlayer::BUFFERS_COUNT, this->buffers);
    return true;
}

void QueuePlayer::worker()
{
    for (int i = 0; i<BUFFERS_COUNT; i++) {
       this->buffersStack.push(this->buffers[i]);
    }
    alSourcei(this->source, AL_BUFFER, 0);
    alSourcef(this->source, AL_GAIN, 1.0f);

    ALint buffersAvailable;
    ALuint buffersHolder[QueuePlayer::BUFFERS_COUNT];
    buffersAvailable = QueuePlayer::BUFFERS_COUNT;
    for (uint8_t it = 0; it < QueuePlayer::BUFFERS_COUNT; it++) {
        buffersHolder[it] = this->buffers[it];
    }

    for (;this->workerRunning;) {
        if (buffersAvailable>0) {
            for (uint8_t it=0; it<buffersAvailable; it++) {
                this->generator.generate();

                const auto data = this->generator.getData();
                ALsizei    size = this->generator.getDataSize();

                alBufferData(buffersHolder[it], AL_FORMAT_MONO16, data, size, this->generator.getDeviceRate());
            }
            alSourceQueueBuffers(this->source, buffersAvailable, buffersHolder);
            buffersAvailable = 0;

            ALint sourceState = 0;
            alGetSourcei(this->source, AL_SOURCE_STATE, &sourceState);
            if (sourceState!=AL_PLAYING) {
                alSourcePlay(this->source);
            }
        } else {
            alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &buffersAvailable);
            if (buffersAvailable > 0) {
                alSourceUnqueueBuffers(this->source, buffersAvailable, buffersHolder);
                continue;
            }
            std::this_thread::sleep_for( std::chrono::milliseconds(10) );
        }
    }
}


void QueuePlayer::play()
{
    this->workerRunning = true;
    this->workerThread = std::thread([this] {
        this->worker();
    });//std::bind(&QueuePlayer::worker, this));
}

void QueuePlayer::stop() {
    this->workerRunning = false;
    alSourceStop(this->source);
    this->workerThread.join();
}

/**
 * @brief Wait unless finished
 */
void QueuePlayer::join()
{
    this->workerThread.join();
}

}
