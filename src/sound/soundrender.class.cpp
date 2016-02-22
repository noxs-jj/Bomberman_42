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

#include <soundrender.class.hpp>
#include <main.hpp>
#include <save.class.hpp>
#define FUNC std::string(__PRETTY_FUNCTION__) + " -> "

SoundRender::SoundRender() {
	if (!init()) {
        return ;
    };
}

SoundRender::~SoundRender() {
    deinit();
}

bool    SoundRender::init() {
    this->w_log(FUNC + "soundrender -> constructing");
    // open 44.1KHz, signed 16bit, system byte order,
    // stereo audio, using 1024 byte chunks
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, STEREO, 1024) == -1) {
		w_error(Mix_GetError());
        return false;
    }
    // allocate 16 mixing channels
	this->w_log(FUNC + "soundrender -> allocating channels");
    Mix_AllocateChannels(mMaxAllocatedChannels);
    this->setGlobalVolume(VOLUME_DEFAULT);
    this->setGlobalVolume(main_event->save_config->global_config.sound_volume); // load from save config_file
    return true;
}

bool    SoundRender::deinit() {
    this->w_log(FUNC + "destructing soundrender");
    // free sounds
    for (auto it = mChunks.begin(); it != mChunks.cend();)
    {
        this->w_log(FUNC + "freeing " + it->first);
        Mix_FreeChunk(it->second);
        mChunks.erase(it++);
    }
    // free music
    for (auto it = mMusics.begin(); it != mMusics.cend();)
    {
        this->w_log(FUNC + "freeing " + it->first);
        Mix_FreeMusic(it->second);
        mMusics.erase(it++);
    }
    this->w_log(FUNC + "soundrender -> deiniting (Mix_Init(0))");
    while (Mix_Init(0)) {
        Mix_Quit();
    }
    this->w_log(FUNC + "soundrender -> close audio");
    Mix_CloseAudio();
    return true;
}

void    SoundRender::load_files(void) {
    if (!(
               this->loadSound("blast", "assets/sound_wav/blast.wav")
            && this->loadSound("startup", "assets/sound_wav/pause.wav")
            && this->loadSound("die", "assets/sound_wav/PLAYER_OUT.wav")
            && this->loadSound("ready", "assets/sound_wav/readymegaman.wav")
            && this->loadSound("menu2", "assets/sound_wav/megamenu2.wav")
            && this->loadSound("menu1", "assets/sound_wav/menu1.wav")
            && this->loadSound("bombmove", "assets/sound_wav/BOM_SET.wav")
            && this->loadSound("pause", "assets/sound_wav/pause.wav")
            && this->loadSound("buldingfire", "assets/sound_wav/3s_the_building_is_on_fire.wav")
            && this->loadSound("dogsout", "assets/sound_wav/3s_who_let_the_dogs_out.wav")
            && this->loadSound("switchselect", "assets/sound_wav/SE_02.wav")
            && this->loadSound("return", "assets/sound_wav/SE_07.wav")
            && this->loadSound("dogsout_long", "assets/sound_wav/10s_who_let_the_dogs_out.wav")
            && this->loadSound("lose", "assets/sound_wav/deuxheures.wav")
            && this->loadSound("kick", "assets/sound_wav/BOM_KICK.wav")
            && this->loadSound("powerup", "assets/sound_wav/ITEM_GET.wav")
            && this->loadSound("danger", "assets/sound_wav/B_A040.wav")
            && this->loadSound("special", "assets/sound_wav/B_SPECIAL.wav")
            // music
            && this->loadMusic("victory", "assets/sound_wav/victory.wav")
            && this->loadMusic("victory_multiplayer", "assets/sound_wav/victory_multiplayer.wav")
            && this->loadMusic("victory_final", "assets/sound_wav/victory_finalfantasy.wav")
            && this->loadMusic("music", "assets/sound_wav/bgm.wav")
            && this->loadMusic("ps1", "assets/sound_wav/ps1.wav")
        )) {
        this->w_error(FUNC + "loadsound error");
        throw std::exception();
    }
    this->w_log(FUNC + "sounds loaded");
}


bool    SoundRender::loadSound(std::string soundName, std::string fileName) {
    this->w_log(FUNC + "loading sound -> " + soundName + " at " + fileName);
    if (mChunks.count(soundName) > 0) {
        this->w_log("sound with given name already exists!");
        return false;
    }
    Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());
    if (chunk == NULL) {
        this->w_log(FUNC + "sound loading [fail]");
        this->w_log(FUNC + Mix_GetError());
        return false;
    }
    mChunks[soundName] = chunk;
    return true;
}

bool    SoundRender::playSound(std::string soundName) {
	this->w_log(FUNC + "Trying to play sound " + soundName);
	try {
	    if (Mix_PlayChannel(-1, mChunks.at(soundName), 0) == -1) {
	        this->w_error(FUNC + Mix_GetError());
	        return false;
	    }
	} catch (std::exception const & e) {
		this->w_error(FUNC + e.what());
		return false;
	}
    return true;
}

bool    SoundRender::loadMusic(std::string musicName, std::string fileName) {
    this->w_log(FUNC + "loading music -> " + musicName + " at " + fileName);
    if (mMusics.count(musicName) > 0) {
        this->w_error(FUNC + "music with given name already exists!");
        return false;
    }
    // load the WAV file "fileName" to play as music
    Mix_Music * music;
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        this->w_error(FUNC + Mix_GetError());
        // this might be a critical error...
        return false;
    }
    mMusics[musicName] = music;
    return true;
}

bool    SoundRender::playMusic(std::string musicName) {
    this->w_log(FUNC + "Trying to play music " + musicName);
    try {
        // stop other musics before doing anything
    	this->stopMusic();
    	// play music forever
        if (Mix_PlayMusic(mMusics.at(musicName), -1) == -1) {
			this->w_error(FUNC + Mix_GetError());
            // well, there's no music, but most games don't break without music...
            return false;
        }
    } catch (std::exception const & e) {
		this->w_error(FUNC + e.what());
        return false;
    }
    return true;
}

void	SoundRender::stopMusic(void) {
    this->w_log(FUNC);
	Mix_HaltMusic();
}

void	SoundRender::stopSounds(void) {
    this->w_log(FUNC);
	Mix_HaltChannel(-1);
}

void    SoundRender::setSFXVolume(int volume) {
    this->w_log(FUNC + std::to_string(volume));
    Mix_Volume(-1, volume);
}

void    SoundRender::setMusicVolume(int volume) {
    this->w_log(FUNC + std::to_string(volume));
    Mix_VolumeMusic(volume);
}

void    SoundRender::setGlobalVolume(int volume) {
    this->w_log(FUNC + std::to_string(volume));
    setSFXVolume(volume);
    setMusicVolume(volume);
}

int     SoundRender::getSFXVolume(void) {
    return (Mix_Volume(1, Mix_Volume(-1,-1)));
}

int     SoundRender::getMusicVolume(void) {
    return (Mix_Volume(1, Mix_VolumeMusic(-1)));
}
