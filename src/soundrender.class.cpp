#include "soundrender.class.hpp"

SoundRender::SoundRender() {
    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::printf("SoundRender::SoundRender(): %s\n", Mix_GetError());
        return ;
    }
    // allocate 16 mixing channels
    Mix_AllocateChannels(mMaxAllocatedChannels);
}

SoundRender::SoundRender(SoundRender const & rhs) {
    (void)rhs;
}

SoundRender & SoundRender::operator=(SoundRender const & rhs) {
    if (this != &rhs) {
        (void)rhs;
    }
    return (*this);
}

SoundRender::~SoundRender() {
    for (auto & kv : mChunks) {
        // kv.first --> key (std::string)
        // kv.second --> value (Mix_Chunk*)
        Mix_FreeChunk(kv.second);
    }
    while (Mix_Init(0)) {
        Mix_Quit();
    }
    Mix_CloseAudio();
}


bool SoundRender::loadSound(std::string soundName, std::string fileName) {
    (void)soundName;
    (void)fileName;
    Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());
    if (chunk == NULL) {
        printf("SoundRender::loadSound: %s\n", Mix_GetError());
        return false;
    }
    mChunks[soundName] = chunk;
    return true;
}

void SoundRender::playSound(std::string soundName) {
    (void)soundName;
    if (Mix_PlayChannel(-1, mChunks[soundName], 0) == -1) {
        printf("SoundRender::playSound: %s\n",Mix_GetError());
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
    }
}
