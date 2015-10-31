#include <string>
#include <ft42.class.hpp>
#include <SDL_mixer.h>
#include <map>

class SoundRender {

    public:

        SoundRender();
        SoundRender(SoundRender const & rhs);
        SoundRender & operator=(SoundRender const & rhs);
        ~SoundRender();

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
