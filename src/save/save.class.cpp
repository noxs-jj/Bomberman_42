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
    main_event->save_config = this;
    main_event->save_config->load_global_config_file();
    main_event->full_screen = main_event->save_config->global_config.video_fullscreen;
}

Save::~Save() {}

void Save::save_level(int level) {
	main_event->save_level_mode = level;
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
    this->global_config.video_fullscreen = main_event->full_screen;
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
        this->global_config.windowed_width = RESOLUTION_800;
    }
    else if (RESOLUTION_800 == main_event->actual_resolution) {
        this->global_config.windowed_width = RESOLUTION_800;
    }
    else if (RESOLUTION_1280 == main_event->actual_resolution) {
        this->global_config.windowed_width = RESOLUTION_1280;
    }
    else if (RESOLUTION_1600 == main_event->actual_resolution) {
        this->global_config.windowed_width = RESOLUTION_1600;
    }
    else if (RESOLUTION_1920 == main_event->actual_resolution) {
        this->global_config.windowed_width = RESOLUTION_1920;
    }
    else if (RESOLUTION_2560 == main_event->actual_resolution) {
        this->global_config.windowed_width = RESOLUTION_2560;
    }
    else {
        this->global_config.windowed_width = RESOLUTION_800;
    }
}


void    Save::save_global_config_to_file() {
    static const char   num[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    FILE                *stream;
    char                buf[128] = {0};
    int                 i = 0;
    int                 len = sizeof(num) - 1;

    this->fill_info_config();
    while(i < 32) {
        buf[i] = num[rand() % len];
        i++;
    }

    if ((stream = fopen(GLOBAL_CONFIG_FILE, "w")) == NULL)
    	return ;

    if (this->global_config.sound_activated == true)
        buf[0] = '1';
    else
        buf[0] = '0';

    if (this->global_config.sound_volume == VOLUME_OFF)
        buf[1] = '0';
    else if (this->global_config.sound_volume == VOLUME_LOW)
        buf[1] = '1';
    else if (this->global_config.sound_volume == VOLUME_MEDIUM)
        buf[1] = '2';
    else if (this->global_config.sound_volume == VOLUME_HIGH)
        buf[1] = '3';

    if (this->global_config.video_fullscreen == false)
        buf[2] = '0';
    else
        buf[2] = '1';

    if (this->global_config.windowed_width == RESOLUTION_NOT_SET)
        buf[3] = '0';
    else if (this->global_config.windowed_width == RESOLUTION_800)
        buf[3] = '1';
    else if (this->global_config.windowed_width == RESOLUTION_1280)
        buf[3] = '2';
    else if (this->global_config.windowed_width == RESOLUTION_1600)
        buf[3] = '3';
    else if (this->global_config.windowed_width == RESOLUTION_1920)
        buf[3] = '4';
    else if (this->global_config.windowed_width == RESOLUTION_2560)
        buf[3] = '5';
    else
        buf[3] = '0';

    fputs(buf, stream);
    fclose(stream);
}

void    Save::load_global_config_file() {
    FILE    *stream;
    char    buff[128] = {0};

    if ((stream = fopen(GLOBAL_CONFIG_FILE, "r")) == NULL) {
        return ;
    }
    if ( fgets (buff , 128 , stream) == NULL ) {
        fclose(stream);
        return ;
    }
    if (strlen(buff) < 30)
        return ;

    if (buff[0] == '1')
        this->global_config.sound_activated = true;
    else
        this->global_config.sound_activated = false;

    if (buff[1] == '0')
        this->global_config.sound_volume = VOLUME_OFF;
    else if (buff[1] == '1')
        this->global_config.sound_volume = VOLUME_LOW;
    else if (buff[1] == '2')
        this->global_config.sound_volume = VOLUME_MEDIUM;
    else if (buff[1] == '3')
        this->global_config.sound_volume = VOLUME_HIGH;
    else
        this->global_config.sound_volume = VOLUME_MEDIUM;

    if (buff[2] == '1')
        this->global_config.video_fullscreen = true;
    else
        this->global_config.video_fullscreen = false;

    if (buff[3] == '0')
        this->global_config.windowed_width = RESOLUTION_NOT_SET;
    else if (buff[3] == '1')
        this->global_config.windowed_width = RESOLUTION_800;
    else if (buff[3] == '2')
        this->global_config.windowed_width = RESOLUTION_1280;
    else if (buff[3] == '3')
        this->global_config.windowed_width = RESOLUTION_1600;
    else if (buff[3] == '4')
        this->global_config.windowed_width = RESOLUTION_1920;
    else if (buff[3] == '5')
        this->global_config.windowed_width = RESOLUTION_2560;
    else
        this->global_config.windowed_width = RESOLUTION_NOT_SET;
}
