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

SoundRender::SoundRender(SoundRender const & rhs)
    : mChunks(rhs.mChunks)
    , mMusics(rhs.mMusics) {
    (void)rhs;
}

SoundRender & SoundRender::operator=(SoundRender const & rhs) {
    if (this != &rhs) {
        mChunks = rhs.mChunks;
        mMusics = rhs.mMusics;
    }
    return (*this);
}

SoundRender::~SoundRender() {
    // free sounds
    for (auto & kv : mChunks) {
        // kv.first --> key (std::string)
        // kv.second --> value (Mix_Chunk*)
        Mix_FreeChunk(kv.second);
        kv.second = NULL;
    }
    // free music
    for (auto & kv : mMusics) {
        Mix_FreeMusic(kv.second);
        kv.second = NULL;
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

bool SoundRender::playSound(std::string soundName) const {
    (void)soundName;
    if (Mix_PlayChannel(-1, mChunks.at(soundName), 0) == -1) {
        printf("SoundRender::playSound: %s\n",Mix_GetError());
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
        return false;
    }
    return true;
}

bool SoundRender::loadMusic(std::string musicName, std::string fileName) {
    // load the WAV file "fileName" to play as music
    Mix_Music * music;
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        std::printf("Mix_LoadMUS(\"%s\"): %s\n", fileName.c_str(), Mix_GetError());
        // this might be a critical error...
        return false;
    }
    mMusics[musicName] = music;
    return true;
}

bool SoundRender::playMusic(std::string musicName) const {
    // play music forever
    if (Mix_PlayMusic(mMusics.at(musicName), -1) == -1) {
        std::printf("Mix_PlayMusic: %s\n", Mix_GetError());
        // well, there's no music, but most games don't break without music...
        return false;
    }
    return true;
}
