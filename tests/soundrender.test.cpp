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
#include <thread>

int main(int argc, char const *argv[]) {
	(void)argc;
	(void)argv;
	{
		ft42::logg = true;

		std::cout << "start" << std::endl;
		// start SDL with audio support
		if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		    std::printf("SDL_Init: %s\n", SDL_GetError());
		    exit(1);
		}

		std::shared_ptr<SoundRender> sr(new SoundRender);

		// load sounds
		sr->loadSound("blast", "sound/blast.wav");
		sr->loadSound("startup", "sound/ps1.wav");
		sr->loadMusic("music", "sound/bgm.wav");
		std::cout << "next step SHOULD FAIL" << std::endl;
		sr->loadMusic("music", "sosad0");
		std::cout << "next step SHOULD FAIL" << std::endl;
		sr->loadMusic("musicasdsad", "sosad1");
		std::cout << "next step SHOULD FAIL" << std::endl;
		sr->loadSound("zxc", "sosad2");
		std::cout << "next step SHOULD FAIL" << std::endl;
		sr->loadSound("zxc", "sosad3");

		// play sound
		sr->playSound("startup");
		sleep(2);
		sr->playSound("blast");
		sleep(2);
		std::cout << "Playing 17 sounds" << std::endl;
		std::cout << "Some sounds SHOULD FAIL because of too few channels" << std::endl;
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
		std::cout << "Testing thread safety" << std::endl;
		std::thread t([&sr](){
			sr->playMusic("music");
			sleep(6);
		});

		t.join();
		// delete sr;
		std::cout << "end" << std::endl;
	}
	return 0;
}
