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

#include <save.class.hpp>
#include <event.class.hpp>
#include <globject.class.hpp>
#include <soundrender.class.hpp>

Save::Save() {
    std::cout << sizeof(this->global_config) << std::endl;;
    main_event->save_config = this;
}

Save::~Save() {}

void Save::save_level(int level) {
	static const char num[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	if (level < 1)
	level = 1;
	FILE *stream;
	char buf[128] = {0};
	int i = 0;
	int len = sizeof(num) - 1;
	while(i < 32) {
		buf[i] = num[rand() % len];
		i++;
	}
	if (main_event->coop == false)
		buf[0] = '1';
	else
		buf[0] = '0';
	buf[2] = '0' + level;

	if ((stream = fopen(LEVEL_FILE, "w")) == NULL)
		return ;

	fputs(buf, stream);
	fclose(stream);
}

void Save::load_level( void ) {
	FILE *stream;
	char buff[128] = {0};

	if ((stream = fopen(LEVEL_FILE, "r")) == NULL) {
		save_level(1);
		return ;
	}
	if ( fgets (buff , 128 , stream) == NULL ) {
		fclose(stream);
		save_level(1);
		return ;
	}
	if (strlen(buff) < 30)
		return ;
	if (buff[0] - '0' == 1)
		main_event->save_level_mode = false;
	else
		main_event->save_level_mode = true;
	main_event->save_level = buff[2] - '0';
}

void    Save::fill_info_config() {
    int i = 0;

    this->global_config.sound_volume = main_event->soundrender->getMusicVolume();
    if (this->global_config.sound_volume == 0)
        this->global_config.sound_activated = false;
    else
        this->global_config.sound_activated = true;
    this->global_config.video_fullscreen = false;
    this->fill_actual_resolution();

    while (i < 9) {
        this->global_config.keyboard[i] = 49 + i;
        i++;
    }
}

void    Save::print_config_debugg() {
    std::cout << "this->global_config.sound_volume " << this->global_config.sound_volume << std::endl;
    std::cout << "this->global_config.sound_activated " << this->global_config.sound_activated << std::endl;
    std::cout << "this->global_config.video_fullscreen " << this->global_config.video_fullscreen << std::endl;
    std::cout << "this->global_config.windowed_width " << this->global_config.windowed_width << std::endl;
    std::cout << "this->global_config.windowed_height " << this->global_config.windowed_height << std::endl;
    std::cout << "this->global_config.keyboard " << this->global_config.keyboard << std::endl;
}

void    Save::fill_actual_resolution() {
    if (RESOLUTION_NOT_SET == main_event->actual_resolution) {
        main_event->actual_resolution = RESOLUTION_800;
        this->global_config.windowed_width = 800;
        this->global_config.windowed_height = 600;
    }
    else if (RESOLUTION_800 == main_event->actual_resolution) {
        this->global_config.windowed_width = 800;
        this->global_config.windowed_height = 600;
    }
    else if (RESOLUTION_1280 == main_event->actual_resolution) {
        this->global_config.windowed_width = 1280;
        this->global_config.windowed_height = 720;
    }
    else if (RESOLUTION_1600 == main_event->actual_resolution) {
        this->global_config.windowed_width = 1600;
        this->global_config.windowed_height = 900;
    }
    else if (RESOLUTION_1920 == main_event->actual_resolution) {
        this->global_config.windowed_width = 1920;
        this->global_config.windowed_height = 1080;
    }
    else if (RESOLUTION_2560 == main_event->actual_resolution) {
        this->global_config.windowed_width = 2560;
        this->global_config.windowed_height = 1440;
    }
    else {
        this->global_config.windowed_width = 800;
        this->global_config.windowed_height = 600;
    }
}

// void	Save::save_config( void ) {
// 	FILE *stream;
// 	char buf[128] = {0};
//
// 	if ((stream = fopen(GLOBAL_CONFIG_FILE, "w")) == NULL)
// 		return ;
// 	sprintf(buf, "%d,%d,%d,%d,%d", this->config[0], this->config[1], this->config[2], this->config[3], this->config[4]);
// 	fputs(buf, stream);
// 	fclose(stream);
// 	set_key_config();
// }
//
// void	Save::save_default_config( void ) {
// 	FILE *stream;
//
// 	if ((stream = fopen(GLOBAL_CONFIG_FILE, "w")) == NULL)
// 		return ;
//
// 	fputs("1,1,0,0,0", stream);
// 	fclose(stream);
// 	this->config[0] = 1;
// 	this->config[1] = 1;
// 	this->config[2] = 0;
// 	this->config[3] = 0;
// 	this->config[4] = 0;
// }
//
// void Joystick::load_config( void ) {
// 	FILE *stream;
// 	char buff[128] = {0};
//
// 	if ((stream = fopen(GLOBAL_CONFIG_FILE, "r")) == NULL) {
// 		save_default_config();
// 		return ;
// 	}
// 	if ( fgets (buff , 128 , stream) == NULL ) {
// 		fclose(stream);
// 		save_default_config();
// 		return ;
// 	}
//
// 	if (strlen(buff) < 9)
// 		return ;
// 	if ((buff[0] - '0' != 1 && buff[0] - '0' != 0)
// 		|| (buff[2] - '0' != 1 && buff[2] - '0' != 0)
// 		|| (buff[4] - '0' != 1 && buff[4] - '0' != 0)
// 		|| (buff[6] - '0' != 1 && buff[6] - '0' != 0)
// 		|| (buff[8] - '0' != 1 && buff[8] - '0' != 0))
// 			return ;
//
// 	this->config[0] = buff[0] - '0';
// 	this->config[1] = buff[2] - '0';
// 	this->config[2] = buff[4] - '0';
// 	this->config[3] = buff[6] - '0';
// 	this->config[4] = buff[8] - '0';
// 	fclose(stream);
//
// 	int i = 0, tmp = 0;
//
// 	while (i < 5) {
// 		if (this->config[i] == 1)
// 			tmp++;
// 		if (tmp > 2) {
// 			save_default_config();
// 			return ;
// 		}
// 		i++;
// 	}
//
// 	set_key();
// }
