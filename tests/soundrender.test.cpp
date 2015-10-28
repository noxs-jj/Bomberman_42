#include "soundrender.class.hpp"

int main(int argc, char const *argv[]) {
	(void)argc;
	(void)argv;

	// start SDL with audio support
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
	    std::printf("SDL_Init: %s\n", SDL_GetError());
	    exit(1);
	}

	SoundRender* sr = new SoundRender();

	sr->loadSound("blast", "sound/blast.wav");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");

	std::cout << "start" << std::endl;
	sleep(3);


	delete sr;
	std::cout << "end" << std::endl;
	return 0;
}
