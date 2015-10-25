#include <string>
#include <ft42.class.hpp>

class SoundRender {

    public:

        SoundRender();
        SoundRender(SoundRender const & rhs);
        SoundRender & operator=(SoundRender const & rhs);
        ~SoundRender();

        // add a sound to sound list
        // play it with 'playSound(soundName);'
        // returns 'false' if something goes wrong
        void addSound(std::string soundName, std::string fileName);

        // play the sound 'soundName'
        // which you added via 'addSound(soundName, fileName);'
        // returns 'false' if it does not exist
        bool playSound(std::string soundName);

};
