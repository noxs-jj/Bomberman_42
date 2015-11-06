#include "soundrender.class.hpp"

SoundRender::SoundRender() {
	if (!init()) {
        return ;
    };
}

SoundRender::~SoundRender() {
    deinit();
}

bool SoundRender::init() {
    w_full("soundrender -> constructing");
    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		w_error(Mix_GetError());
        return false;
    }
    // allocate 16 mixing channels
	w_full("soundrender -> allocating channels");
    Mix_AllocateChannels(mMaxAllocatedChannels);
    return true;
}

bool SoundRender::deinit() {
    w_full("destructing soundrender");
    // free sounds
    for (auto & kv : mChunks) {
        // kv.first --> key (std::string)
        // kv.second --> value (Mix_Chunk*)
        w_full("freeing " + kv.first);
        Mix_FreeChunk(kv.second);
        kv.second = NULL;
    }
    // free music
    for (auto & kv : mMusics) {
        Mix_FreeMusic(kv.second);
        kv.second = NULL;
    }
    w_full("soundrender -> deiniting (Mix_Init(0))");
    while (Mix_Init(0)) {
        Mix_Quit();
    }
    w_full("soundrender -> close audio");
    Mix_CloseAudio();
    return true;
}

bool SoundRender::loadSound(std::string soundName, std::string fileName) {
    w_full("loading sound -> " + soundName + " at " + fileName);
    if (mChunks.count(soundName) > 0) {
        w_full("sound with given name already exists!");
        return false;
    }
    Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());
    if (chunk == NULL) {
        w_full("sound loading [fail]");
        w_full(Mix_GetError());
        return false;
    }
    mChunks[soundName] = chunk;
    return true;
}

bool SoundRender::playSound(std::string soundName) const {
    (void)soundName;
    if (Mix_PlayChannel(-1, mChunks.at(soundName), 0) == -1) {
        std::printf("SoundRender::playSound: %s\n",Mix_GetError());
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
        return false;
    }
    return true;
}

bool SoundRender::loadMusic(std::string musicName, std::string fileName) {
    w_full("loading music -> " + musicName + " at " + fileName);
    if (mMusics.count(musicName) > 0) {
        w_full("music with given name already exists!");
        return false;
    }
    // load the WAV file "fileName" to play as music
    Mix_Music * music;
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        w_full(Mix_GetError());
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
