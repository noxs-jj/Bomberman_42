#include "soundrender.class.hpp"

int main(int argc, char const *argv[]) {
	(void)argc;
	(void)argv;
	std::cout << "start" << std::endl;

	// start SDL with audio support
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
	    std::printf("SDL_Init: %s\n", SDL_GetError());
	    exit(1);
	}

	SoundRender* sr = new SoundRender();

	// load sounds
	sr->loadSound("blast", "sound/blast.wav");
	sr->loadSound("startup", "sound/ps1.wav");
	sr->loadSound("startup", "sound/bgm.wav");
	sr->loadMusic("music", "sound/bgm.wav");

	// play sound
	sr->playSound("startup");
	sleep(2);
	sr->playSound("blast");
	sleep(2);
	std::cout << "Playing 17 sounds" << std::endl;
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sr->playSound("blast");
	sleep(6);
	sr->playSound("blast");
	sr->playSound("blast");
	sleep(3);
	std::cout << "Playing music" << std::endl;
	sr->playMusic("music");
	sleep(6);

	delete sr;
	std::cout << "end" << std::endl;
	return 0;
}
