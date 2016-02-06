/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundrender.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/06 15:47:05 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

class SoundRender : ft42 {

    public:

        SoundRender();
        SoundRender(SoundRender const & rhs) = default;
        SoundRender & operator=(SoundRender const & rhs) = default;
        virtual ~SoundRender();

		bool init();
		bool deinit();

        // add a sound to sound list
        // play it with 'playSound(soundName);'
        // returns 'false' if something goes wrong
        bool loadSound(std::string soundName, std::string fileName);

        // play the sound 'soundName'
        // which you added via 'loadSound(soundName, fileName);'
        // returns 'false' if it does not exist
        bool playSound(std::string soundName);

        bool loadMusic(std::string musicName, std::string fileName);
        bool playMusic(std::string musicName);

    private:

        int const                         mMaxAllocatedChannels = 4;
        std::map<std::string, Mix_Chunk*> mChunks;
        std::map<std::string, Mix_Music*> mMusics;
};

#endif // SOUNDRENDER_CLASS_HPP
