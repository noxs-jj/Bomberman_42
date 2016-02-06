// ************************************************************************** //
//   24 Bomb                                                                  //
//   By: rcargou <rcargou@student.42.fr>                  :::      ::::::::   //
//   By: nmohamed <nmohamed@student.42.fr>              :+:      :+:    :+:   //
//   By: adjivas <adjivas@student.42.fr>              +:+ +:+         +:+     //
//   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        //
//   By: jmoiroux <jmoiroux@student.42.fr>        +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/27 14:00:02 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
    this->w_full("soundrender -> constructing");
    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, STEREO, 1024) == -1) {
		w_error(Mix_GetError());
        return false;
    }
    // allocate 16 mixing channels
	this->w_full("soundrender -> allocating channels");
    Mix_AllocateChannels(mMaxAllocatedChannels);
    return true;
}

bool SoundRender::deinit() {
    this->w_full("destructing soundrender");
    // free sounds
    for (auto it = mChunks.begin(); it != mChunks.cend();)
    {
        this->w_full("freeing " + it->first);
        Mix_FreeChunk(it->second);
        mChunks.erase(it++);
    }
    // free music
    for (auto it = mMusics.begin(); it != mMusics.cend();)
    {
        this->w_full("freeing " + it->first);
        Mix_FreeMusic(it->second);
        mMusics.erase(it++);
    }
    this->w_full("soundrender -> deiniting (Mix_Init(0))");
    while (Mix_Init(0)) {
        Mix_Quit();
    }
    this->w_full("soundrender -> close audio");
    Mix_CloseAudio();
    return true;
}

bool SoundRender::loadSound(std::string soundName, std::string fileName) {
    this->w_full("loading sound -> " + soundName + " at " + fileName);
    if (mChunks.count(soundName) > 0) {
        this->w_full("sound with given name already exists!");
        return false;
    }
    Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());
    if (chunk == NULL) {
        this->w_full("sound loading [fail]");
        this->w_full(Mix_GetError());
        return false;
    }
    mChunks[soundName] = chunk;
    return true;
}

bool SoundRender::playSound(std::string soundName) {
	try {
	    if (Mix_PlayChannel(-1, mChunks.at(soundName), 0) == -1) {
	        this->w_full(Mix_GetError());
	        // may be critical error, or maybe just no channels were free.
	        // you could allocated another channel in that case...
	        return false;
	    }
	} catch (std::exception const & e) {
		this->w_full(e.what());
		return false;
	}
    return true;
}

bool SoundRender::loadMusic(std::string musicName, std::string fileName) {
    this->w_full("loading music -> " + musicName + " at " + fileName);
    if (mMusics.count(musicName) > 0) {
        this->w_full("music with given name already exists!");
        return false;
    }
    // load the WAV file "fileName" to play as music
    Mix_Music * music;
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        this->w_full(Mix_GetError());
        // this might be a critical error...
        return false;
    }
    mMusics[musicName] = music;
    return true;
}

bool SoundRender::playMusic(std::string musicName) {
    try {
        // stop other musics before doing anything
    	Mix_HaltMusic();
    	// play music forever
        if (Mix_PlayMusic(mMusics.at(musicName), -1) == -1) {
			this->w_full(Mix_GetError());
            // well, there's no music, but most games don't break without music...
            return false;
        }
    } catch (std::exception const & e) {
		this->w_full(e.what());
        return false;
    }
    return true;
}
