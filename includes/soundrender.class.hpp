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

class SoundRender : ft42 {

    public:

        SoundRender();
        SoundRender(SoundRender const & rhs) = default;
        SoundRender & operator=(SoundRender const & rhs) = default;
        ~SoundRender();

		bool init();
		bool deinit();

        // add a sound to sound list
        // play it with 'playSound(soundName);'
        // returns 'false' if something goes wrong
        bool loadSound(std::string soundName, std::string fileName);

        // play the sound 'soundName'
        // which you added via 'loadSound(soundName, fileName);'
        // returns 'false' if it does not exist
        bool playSound(std::string soundName) const;

        bool loadMusic(std::string musicName, std::string fileName);
        bool playMusic(std::string musicName) const;

    private:

        int const                         mMaxAllocatedChannels = 16;
        std::map<std::string, Mix_Chunk*> mChunks;
        std::map<std::string, Mix_Music*> mMusics;
};

#endif // SOUNDRENDER_CLASS_HPP
