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

#ifndef SOUNDRENDER_CLASS_HPP
# define SOUNDRENDER_CLASS_HPP
# include <string>
# include <ft42.class.hpp>
# include <SDL.h>
# include <SDL_mixer.h>
# include <map>
# include <stdexcept>

# define STEREO 2
# define MONO 1

# define VOLUME_HIGH (MIX_MAX_VOLUME / 1)
# define VOLUME_MEDIUM (MIX_MAX_VOLUME / 2)
# define VOLUME_LOW (MIX_MAX_VOLUME / 3)
# define VOLUME_OFF (0)
# define VOLUME_DEFAULT VOLUME_MEDIUM

class SoundRender : ft42 {

    public:

        SoundRender();
        virtual ~SoundRender();

		bool	init();
		bool	deinit();
        void	load_files(void); //loads all sounds

        // add a sound to sound list
        // play it with 'playSound(soundName);'
        // returns 'false' if something goes wrong
        bool	loadSound(std::string soundName, std::string fileName);

        // play the sound 'soundName'
        // which you added via 'loadSound(soundName, fileName);'
        // returns 'false' if it does not exist
        bool	playSound(std::string soundName);

        bool	loadMusic(std::string musicName, std::string fileName);
        bool	playMusic(std::string musicName);
        void    stopMusic(void);
        void    stopSounds(void);

        // Volume
        void    setSFXVolume(int volume);
        void    setMusicVolume(int volume);
        void    setGlobalVolume(int volume);

        int     getSFXVolume(void);
        int     getMusicVolume(void);


    private:
        int const                         mMaxAllocatedChannels = 8;
        std::map<std::string, Mix_Chunk*> mChunks;
        std::map<std::string, Mix_Music*> mMusics;
        SoundRender( SoundRender const & src ) = delete;
        SoundRender & operator=( SoundRender const & rhs ) = delete;
};

#endif // SOUNDRENDER_CLASS_HPP
