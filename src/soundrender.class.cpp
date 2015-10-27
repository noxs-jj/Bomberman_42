#include "soundrender.class.hpp"

SoundRender::SoundRender() {
    // load support for the OGG sample/music format
    int flags = MIX_INIT_OGG;
    // init
    int initted = Mix_Init(flags);

    // test init success
    if ((initted & flags) != flags) {
        // error
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        return ;
    }
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

}
