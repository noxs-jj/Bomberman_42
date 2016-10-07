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

#include <joystick.hpp>
#include <save.class.hpp>
#include <event.class.hpp>
#include <Menu.class.hpp>
#include <map_event.class.hpp>
#include <GameLauncher.class.hpp>

Joystick::Joystick(void) {
    this->config[0] = 1;
    this->config[1] = 1;
    this->config[2] = 0;
    this->config[3] = 0;
    this->config[4] = 0;
    this->config[5] = 0;
    this->config[6] = 0;
    this->config[7] = 0;
    this->config[8] = 0;
    this->config[9] = 0;
}

Joystick::~Joystick(void) {}

Joystick::Joystick( Joystick const & src ) { *this = src; }

Joystick & Joystick::operator=( Joystick const & rhs ) {
	int number = 0;
    if (this != &rhs) {
        this->timer = rhs.timer;
        this->test = rhs.test;
				while (number < 10) {
					this->manettes[number] = rhs.manettes[number];
					number++;
				}
        std::memcpy(this->config, rhs.config, sizeof(this->config));
        std::memcpy(this->arr_key_keyboard, rhs.arr_key_keyboard, sizeof(this->arr_key_keyboard));
        std::memcpy(this->arr_key_controller, rhs.arr_key_controller, sizeof(this->arr_key_controller));
    }
    return (*this);
}

void Joystick::init_joystick() {
    int number = 0;

    this->manettes = (SDL_Joystick **)std::malloc(sizeof(SDL_Joystick *) * 10);
    if (NULL == this->manettes){
        this->w_error("Joystick::init_joystick()  this->manettes Malloc error");
        throw std::exception();
    }
	while (number < main_event->menu->joystick_number) {
		this->manettes[number] = SDL_JoystickOpen(number);
		if (this->manettes[number] == NULL) {
            this->w_error("Could not open joystick");
            this->w_error(SDL_GetError());
            throw std::exception();
		}
		number++;
	}
	while (number < 10) {
		this->manettes[number] = NULL;
		number++;
	}
}

void Joystick::reset_key_pressed() {
	int	i = 0;

	while (i < 5) {
        this->arr_key_keyboard[i]->key_up = 0;
        this->arr_key_keyboard[i]->key_down = 0;
        this->arr_key_keyboard[i]->key_left = 0;
        this->arr_key_keyboard[i]->key_right = 0;
        i++;
	}
	i = 0;
	while (i < 10) {
        this->arr_key_controller[i]->key_up = 0;
        this->arr_key_controller[i]->key_down = 0;
        this->arr_key_controller[i]->key_left = 0;
        this->arr_key_controller[i]->key_right = 0;
        i++;
	}
}

void	Joystick::save_config( void ) {
	FILE *stream;
	char buf[128] = {0};

	if ((stream = fopen(CONFIG_FILE, "w")) == NULL)
		return ;
	sprintf(buf, "%d,%d,%d,%d,%d", this->config[0], this->config[1], this->config[2], this->config[3], this->config[4]);
	fputs(buf, stream);
	fclose(stream);
	set_key_config();
}

void	Joystick::save_default_config( void ) {
	FILE *stream;

	if ((stream = fopen(CONFIG_FILE, "w")) == NULL)
		return ;

	fputs("1,1,0,0,0", stream);
	fclose(stream);
	this->config[0] = 1;
	this->config[1] = 1;
	this->config[2] = 0;
	this->config[3] = 0;
	this->config[4] = 0;
	this->config[5] = 0;
	this->config[6] = 0;
	this->config[7] = 0;
	this->config[8] = 0;
	this->config[9] = 0;
	set_key();
}

void Joystick::load_config( void ) {
	FILE *stream;
	char buff[128] = {0};

	if ((stream = fopen(CONFIG_FILE, "r")) == NULL) {
		save_default_config();
		return ;
	}
	if ( fgets (buff , 128 , stream) == NULL ) {
		fclose(stream);
		save_default_config();
		return ;
	}

	if (strlen(buff) < 9)
		return ;
	if ((buff[0] - '0' != 1 && buff[0] - '0' != 0)
		|| (buff[2] - '0' != 1 && buff[2] - '0' != 0)
		|| (buff[4] - '0' != 1 && buff[4] - '0' != 0)
		|| (buff[6] - '0' != 1 && buff[6] - '0' != 0)
		|| (buff[8] - '0' != 1 && buff[8] - '0' != 0))
			return ;

	this->config[0] = buff[0] - '0';
	this->config[1] = buff[2] - '0';
	this->config[2] = buff[4] - '0';
	this->config[3] = buff[6] - '0';
	this->config[4] = buff[8] - '0';
	this->config[5] = 0;
	this->config[6] = 0;
	this->config[7] = 0;
	this->config[8] = 0;
	this->config[9] = 0;
	fclose(stream);

	int i = 0, tmp = 0;

	while (i < 5) {
		if (this->config[i] == 1)
			tmp++;
		if (tmp > 2) {
			save_default_config();
			return ;
		}
		i++;
	}

	set_key();
}

void Joystick::set_key() {
    static t_key   key = {0, 0, 0, 0};
    static t_key   key2 = {0, 0, 0, 0}; // key for p2 (keyboard)
    static t_key   key3 = {0, 0, 0, 0};
    static t_key   key4 = {0, 0, 0, 0};
    static t_key   key5 = {0, 0, 0, 0};

    static t_key   ckey = {0, 0, 0, 0};
    static t_key   ckey2 = {0, 0, 0, 0}; // key for p2 (controller)
    static t_key   ckey3 = {0, 0, 0, 0};
    static t_key   ckey4 = {0, 0, 0, 0};
    static t_key   ckey5 = {0, 0, 0, 0};

    static t_key   ckey6 = {0, 0, 0, 0};
    static t_key   ckey7 = {0, 0, 0, 0};
    static t_key   ckey8 = {0, 0, 0, 0};
    static t_key   ckey9 = {0, 0, 0, 0};
    static t_key   ckey10 = {0, 0, 0, 0};

    this->arr_key_keyboard[0] = &key;
    this->arr_key_keyboard[1] = &key2;
    this->arr_key_keyboard[2] = &key3;
    this->arr_key_keyboard[3] = &key4;
	this->arr_key_keyboard[4] = &key5;

    this->arr_key_controller[0] = &ckey;
    this->arr_key_controller[1] = &ckey2;
    this->arr_key_controller[2] = &ckey3;
    this->arr_key_controller[3] = &ckey4;
    this->arr_key_controller[4] = &ckey5;
    this->arr_key_controller[5] = &ckey6;
    this->arr_key_controller[6] = &ckey7;
    this->arr_key_controller[7] = &ckey8;
    this->arr_key_controller[8] = &ckey9;
    this->arr_key_controller[9] = &ckey10;
    set_key_config();
}

void Joystick::set_key_config() {
	int i = 0;
	int nbr = 0;
	int nbr_keyboard = 0;

	main_event->config_keyboard[0] = -1;
	main_event->config_keyboard[1] = -1;
	main_event->config_keyboard[2] = -1;
	main_event->config_keyboard[3] = -1;
	main_event->config_keyboard[4] = -1;
	main_event->config[0] = -1;
	main_event->config[1] = -1;
	main_event->config[2] = -1;
	main_event->config[3] = -1;
	main_event->config[4] = -1;
	main_event->config[5] = -1;
	main_event->config[6] = -1;
	main_event->config[7] = -1;
	main_event->config[8] = -1;
	main_event->config[9] = -1;

	while (i < 5) {
		if (this->config[i] == 0) {
			main_event->config[nbr] = PLAYER1 + i;
			nbr++;
		}
		else {
			main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
			nbr_keyboard++;
		}
		i++;
	}
	while (i < 10) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
		i++;
	}
}

void Joystick::read_key(int mode) {
    SDL_Event   event;

    Joystick::intro_read_key();
    // IN MENU
    if (mode == 0){
        while (SDL_PollEvent(&event) && main_event->event_running == true) {
            // KEYBOARD BUTTON
            if (event.type == SDL_KEYDOWN) {
                switch((event).key.keysym.sym) {
                    case SDLK_ESCAPE:   main_event->exit_free(); break;
                    case SDLK_DOWN:     main_event->menu->move_menu_ver(1); break;
                    case SDLK_UP:       main_event->menu->move_menu_ver(-1); break;
                    case SDLK_RIGHT:    main_event->menu->move_menu_hor(); break;
                    case SDLK_LEFT:     main_event->menu->move_menu_hor(); break;
                    case SDLK_RETURN:   this->in_menu_SDLK_RETURN(); break;
                    case SDLK_c:        std::cout << "SDL_NumJoysticks(void) " << SDL_NumJoysticks() << std::endl;
                    case SDLK_p:        this->in_menu_SDLK_p(); break;
                    case SDLK_k:        this->in_menu_SDLK_k();
                    case SDLK_u:        this->in_menu_SDLK_u();
                    case SDLK_1:        this->in_menu_SDLK_1(); break;
                    case SDLK_2:        this->in_menu_SDLK_2(); break;
                    case SDLK_3:        this->in_menu_SDLK_3(); break;
                    default:            break;
                }
            }
            // JOYSTICK BUTTON
            else if (event.type == SDL_JOYBUTTONDOWN) {
                switch (event.cbutton.button) {
                    case 3:     this->in_menu_controller_3(); break;
                    case 2:     main_event->menu->change_menu_back(); break;
                    case 4:     Gamelauncher::retry_previous_game(); break;
                    case 9:     this->in_menu_controller_9(); break;
                    default: break;
                  }
            }
            // JOYSTICK CROIX DIRECTIONNEL
            else if (event.type == SDL_JOYAXISMOTION) {
                this->in_menu_controller_axis_motion(event);
    		}
            // CROSS HAT DIR
            else if (event.type == SDL_JOYHATMOTION || event.type == 1536) {
                this->in_menu_controller_hat_motion(event);
            }
        }
    }
    //In GAME
    else {
        while (SDL_PollEvent(&event)) {
            fprintf(stdout, "joystick[%d] type[%d] button[%d] state[%d]\n", event.jbutton.which, event.type, event.jbutton.button, event.jbutton.state);
            if (event.type == SDL_KEYDOWN) {
                switch((event).key.keysym.sym) {
                    case SDLK_ESCAPE:       main_event->exit_free(); break;
                    case SDLK_KP_5:         this->arr_key_keyboard[1]->key_up = 1; break;
                    case SDLK_KP_8:         this->arr_key_keyboard[1]->key_down = 1; break;
                    case SDLK_KP_6:         this->arr_key_keyboard[1]->key_right = 1; break;
                    case SDLK_KP_4:         this->arr_key_keyboard[1]->key_left = 1; break;
                    case SDLK_KP_PLUS:      main_event->player_bomb(main_event->config_keyboard[1]); break;
                    case SDLK_KP_MINUS:     main_event->remote_put(main_event->config_keyboard[1]); break;
                    case SDLK_KP_MULTIPLY:  main_event->remote_detonate(main_event->config_keyboard[1]); break;
                    case SDLK_s:            this->arr_key_keyboard[0]->key_up = 1; break;
                    case SDLK_w:            this->arr_key_keyboard[0]->key_down = 1; break;
                    case SDLK_d:            this->arr_key_keyboard[0]->key_right = 1; break;
                    case SDLK_a:            this->arr_key_keyboard[0]->key_left = 1; break;
                    case SDLK_c:            main_event->player_bomb(main_event->config_keyboard[0]); break;
                    case SDLK_v:            main_event->remote_put(main_event->config_keyboard[0]); break;
                    case SDLK_b:            main_event->remote_detonate(main_event->config_keyboard[0]); break;
                    case SDLK_n:            Map_event::debugg_change_timer_lunch_warmup_1(); break;
                    case SDLK_m:            Map_event::debugg_change_timer_lunch_warmup_2(); break;
                    case SDLK_z:            main_event->print_map();
                    case SDLK_RETURN:       this->in_game_SDLK_RETURN(); break;
                    case SDLK_k:            this->in_game_SDLK_k(); break;
                    case SDLK_p:            this->in_game_SDLK_p(); break;
                    default: break;
                }
            }
            // JOYSTICK BUTTON
            else if (event.type == SDL_JOYBUTTONDOWN) {
                switch (event.cbutton.button) {
                    case 3:   main_event->player_bomb(main_event->config[event.jbutton.which]); break;
                    case 2:   main_event->remote_put(main_event->config[event.jbutton.which]); break;
                    case 1:   main_event->remote_detonate(main_event->config[event.jbutton.which]); break;
                    case 9:   this->in_game_controller_9(event); break;
                    case 8:   this->in_game_controller_8(); break;
                    default: break;
              }
            }
            // JOYSTICK CROIX DIRECTIONNEL
            else if (event.type == SDL_JOYHATMOTION) {
                this->in_game_controller_hat_motion(event);
            }
            // CROSS HAT DIR
            else if (event.type == SDL_JOYAXISMOTION) {
                this->in_game_controller_axis_motion(event);
            }
            if (event.type == SDL_KEYUP) {
                switch((event).key.keysym.sym) {
                    case SDLK_KP_5:     this->arr_key_keyboard[1]->key_up = 0; break;
                    case SDLK_KP_8:     this->arr_key_keyboard[1]->key_down = 0; break;
                    case SDLK_KP_6:     this->arr_key_keyboard[1]->key_right = 0; break;
                    case SDLK_KP_4:     this->arr_key_keyboard[1]->key_left = 0; break;
                    case SDLK_s:        this->arr_key_keyboard[0]->key_up = 0; break;
                    case SDLK_w:        this->arr_key_keyboard[0]->key_down = 0; break;
                    case SDLK_d:        this->arr_key_keyboard[0]->key_right = 0; break;
                    case SDLK_a:        this->arr_key_keyboard[0]->key_left = 0; break;
                    default: break;
                }
            }
        }
    }
    this->refresh_all_dir_joystick();
	int number = 0;
	while (number < 2) {
		if (this->arr_key_keyboard[number]->key_right)
           main_event->player_move(main_event->config_keyboard[number], DIR_RIGHT);
	    if (this->arr_key_keyboard[number]->key_left)
	        main_event->player_move(main_event->config_keyboard[number], DIR_LEFT);
	    if (this->arr_key_keyboard[number]->key_up)
	        main_event->player_move(main_event->config_keyboard[number], DIR_UP);
	    if (this->arr_key_keyboard[number]->key_down)
	        main_event->player_move(main_event->config_keyboard[number], DIR_BOTTOM);
		number++;
	}
	number = 0;
	while (number < 10) {
		if (this->arr_key_controller[number]->key_right)
	        main_event->player_move(main_event->config[number], DIR_RIGHT);
	    if (this->arr_key_controller[number]->key_left)
	        main_event->player_move(main_event->config[number], DIR_LEFT);
	    if (this->arr_key_controller[number]->key_up)
	        main_event->player_move(main_event->config[number], DIR_UP);
	    if (this->arr_key_controller[number]->key_down)
	        main_event->player_move(main_event->config[number], DIR_BOTTOM);
		number++;
	}
  }

void    Joystick::refresh_dir_joystick(t_key *key, Sint16 x_move, Sint16 y_move) {
    key->key_up = 0;
    key->key_down = 0;
    key->key_left = 0;
    key->key_right = 0;
    if (x_move > 3200)
        key->key_right = 1;
    else if (x_move < -3200)
        key->key_left = 1;
    if (y_move > 3200)
        key->key_up = 1;
    else if (y_move < -3200)
        key->key_down = 1;
}

void    Joystick::refresh_all_dir_joystick() {
	Sint16 x_move, y_move;
	int number = 0;

	while (number < 10) {
		if (this->manettes[number] != NULL) {
            # ifdef linux
                x_move = SDL_JoystickGetAxis(this->manettes[number], 0);
                y_move = SDL_JoystickGetAxis(this->manettes[number], 1);
            # endif
            # ifdef __APPLE__
                x_move = SDL_JoystickGetAxis(this->manettes[number], 3);
                y_move = SDL_JoystickGetAxis(this->manettes[number], 4);
            # endif
            refresh_dir_joystick(this->arr_key_controller[number], x_move, y_move);
        }
		number++;
	}
}

void    Joystick::change_dir_joystick(t_key *key, int dir) {
    key->key_up = 0;
    key->key_down = 0;
    key->key_left = 0;
    key->key_right = 0;
    if (dir == DIR_UP)
        key->key_down = 1;
    if (dir == DIR_BOTTOM)
        key->key_up = 1;
    if (dir == DIR_LEFT)
        key->key_left = 1;
    if (dir == DIR_RIGHT)
        key->key_right = 1;
}

void    Joystick::intro_read_key() {
    SDL_Event   event;

    // IN INTRO
    if (false == main_event->menu->introstart) {
        while (SDL_PollEvent(&event) && main_event->event_running == true) {
            if (event.type == SDL_KEYDOWN) {
                if ((event).key.keysym.sym == SDLK_ESCAPE)
                    main_event->exit_free();
                else
                    Joystick::intro_pass();
            }
            else if (event.type == SDL_JOYBUTTONDOWN)
                Joystick::intro_pass();
        }
    }
}

void    Joystick::in_menu_SDLK_RETURN() {
    if (false == main_event->menu->introstart)
        Joystick::intro_pass();
    else if (main_event->draw_winner_multi >= 0
        || main_event->draw_winner_campaign >= 0
        || main_event->draw_lose_campaign >= 0
        || main_event->draw_end_campaign >= 0) {

        main_event->draw_winner_multi = -1;
        main_event->draw_lose_campaign = -1;
        main_event->draw_end_campaign = -1;
        main_event->mode_menu = true;
        if (main_event->game_playing == true) {
            main_event->game_playing = false;
            main_event->free_game();
            main_event->menu->menu_selected = BIG_MENU;
            main_event->menu->detail_menu_selected = MENU_CAMPAIGN;
        }
        if (main_event->draw_winner_campaign >= 0) {
            main_event->draw_winner_campaign = -1;
            main_event->make_new_game(0);
            main_event->mode_menu = false;
            main_event->game_playing = true;
        }
    }
    else
        main_event->menu->change_menu();
}

void    Joystick::in_menu_SDLK_p() {
    if (true == main_event->mode_menu && main_event->game_playing == true)
        main_event->mode_menu = false;
    else if (main_event->game_playing == true)
        main_event->mode_menu = true;
}

void    Joystick::in_menu_SDLK_k() {
    main_event->save_config->fill_info_config();
    main_event->save_config->print_config_debugg();
}

void    Joystick::in_menu_SDLK_u() {
    int i = 0;

    main_event->save_config->save_global_config_to_file();
    while ( i < SDL_NumJoysticks() ) {
        printf("    %s\n", SDL_GameControllerNameForIndex(i) );
        i++;
    }
}

void    Joystick::in_menu_SDLK_1() {
    if (main_event->menu->menu_selected == BIG_MENU
        && main_event->game_playing == true
        && main_event->multi == 0 && main_event->arena == 0) {

        main_event->draw_winner_multi = -1;
        main_event->draw_winner_campaign = -1;
        main_event->draw_lose_campaign = -1;
        main_event->draw_end_campaign = -1;
        main_event->mode_menu = false;
        main_event->make_new_game(1);
        main_event->game_playing = true;
    }
}

void    Joystick::in_menu_SDLK_2() {
    if (main_event->menu->menu_selected == BIG_MENU
        && main_event->game_playing == false) {

        this->test = 1;
        main_event->make_new_game(0);
        main_event->mode_menu = false;
        main_event->game_playing = true;
        this->test = 0;
    }
}

void    Joystick::in_menu_SDLK_3() {
    if (main_event->menu->menu_selected == BIG_MENU
        && main_event->game_playing == true) {

        main_event->cheat_stats();
    }
}

void    Joystick::in_menu_controller_3() {
    if (false == main_event->menu->introstart) {
        main_event->menu->introstart = true;
        main_event->mode_menu = true;
    }
    else if (main_event->draw_winner_multi >= 0
        || main_event->draw_winner_campaign >= 0
        || main_event->draw_lose_campaign >= 0
        || main_event->draw_end_campaign >= 0) {

        main_event->draw_winner_multi = -1;
        // main_event->draw_winner_campaign = -1;
        main_event->draw_lose_campaign = -1;
        main_event->draw_end_campaign = -1;
        main_event->mode_menu = true;
        if (main_event->game_playing == true) {
            main_event->game_playing = false;
            main_event->free_game();
            main_event->menu->menu_selected = BIG_MENU;
            main_event->menu->detail_menu_selected = MENU_CAMPAIGN;
        }
        if (main_event->draw_winner_campaign >= 0) {
            main_event->draw_winner_campaign = -1;
            main_event->make_new_game(0);
            main_event->mode_menu = false;
            main_event->game_playing = true;
        }
    }
    else
        main_event->menu->change_menu();
}

void    Joystick::in_menu_controller_9() {
    if (true == main_event->mode_menu && main_event->game_playing == true)
        main_event->mode_menu = false;
    else if (main_event->game_playing == true)
        main_event->mode_menu = true;
}

void    Joystick::in_menu_controller_axis_motion(SDL_Event &event) {
    if(event.jaxis.axis == 3 || event.jaxis.axis == 0) {
        if (event.jaxis.value > 3200)
            main_event->menu->move_menu_hor();
        else if (event.jaxis.value < -3200)
            main_event->menu->move_menu_hor();
    }

    if( event.jaxis.axis == 4 || event.jaxis.axis == 1) {
        if (event.jaxis.value > 3200)
            main_event->menu->move_menu_ver(1);
        else if (event.jaxis.value < -3200)
            main_event->menu->move_menu_ver(-1);
    }
}

void    Joystick::in_menu_controller_hat_motion(SDL_Event &event) {
    if (0 == event.jhat.hat && 0 != event.jhat.value) {
        switch (event.jhat.value) {
            case SDL_HAT_UP:        main_event->menu->move_menu_ver(-1); break;
            case SDL_HAT_LEFT:      main_event->menu->move_menu_hor(); break;
            case SDL_HAT_DOWN:      main_event->menu->move_menu_ver(1); break;
            case SDL_HAT_RIGHT:     main_event->menu->move_menu_hor(); break;
            case SDL_HAT_CENTERED:  fprintf(stdout, "joystick[%d] CENTERED state[%d]\n", event.jbutton.which, event.jhat.hat); break;
            default:                break;
        }
    }
}

void    Joystick::in_game_SDLK_RETURN() {
    if (false == main_event->menu->introstart) {
        main_event->menu->introstart = true;
        main_event->mode_menu = true;
        if (main_event->game_playing == true) {
            main_event->game_playing = false;
            main_event->free_game();
        }
    }
}

void    Joystick::in_game_SDLK_k() {
    main_event->save_config->fill_info_config();
    main_event->save_config->print_config_debugg();
}

void    Joystick::in_game_SDLK_p() {
    if (true == main_event->mode_menu && main_event->game_playing == true)
        main_event->mode_menu = false;
    else if (main_event->game_playing == true)
        main_event->mode_menu = true;
}

void    Joystick::in_game_controller_9(SDL_Event &event) {
    if ((main_event->multi > 0 || main_event->arena > 0)
        && main_event->live_player[main_event->config[event.jbutton.which] - PLAYER1] == true) {

        if (true == main_event->mode_menu && main_event->game_playing == true)
            main_event->mode_menu = false;
        else if (main_event->game_playing == true)
            main_event->mode_menu = true;
    }
    else if (main_event->multi == 0 && main_event->arena == 0) {
        if (true == main_event->mode_menu && main_event->game_playing == true)
            main_event->mode_menu = false;
        else if (main_event->game_playing == true)
            main_event->mode_menu = true;
    }
}

void    Joystick::in_game_controller_8() {
    if (false == main_event->menu->introstart) {
        main_event->menu->introstart = true;
        main_event->mode_menu = true;
        if (main_event->game_playing == true) {
            main_event->game_playing = false;
            main_event->free_game();
        }
    }
}

void    Joystick::in_game_controller_hat_motion(SDL_Event &event) {
    switch (event.jhat.value) {
        case SDL_HAT_UP:        this->change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_UP); break;
        case SDL_HAT_LEFT:      this->change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_LEFT); break;
        case SDL_HAT_DOWN:      this->change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_BOTTOM); break;
        case SDL_HAT_RIGHT:     this->change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_RIGHT); break;
        case SDL_HAT_CENTERED:  this->change_dir_joystick(this->arr_key_controller[event.jbutton.which], -1); break;
        default:                break;
    }
}

void    Joystick::in_game_controller_axis_motion(SDL_Event &event) {
    if( event.jaxis.axis == 3 || event.jaxis.axis == 0 ) {
        if (event.jaxis.value > 3200) {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], DIR_RIGHT);
        }
        else if (event.jaxis.value < -3200) {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], DIR_LEFT);
        }
        else {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], -1);
        }
        /* Left-right movement code goes here */
    }

    if( event.jaxis.axis == 4 || event.jaxis.axis == 1 ) {
        if (event.jaxis.value > 3200) {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], DIR_BOTTOM);
        }
        else if (event.jaxis.value < -3200) {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], DIR_UP);
        }
        else {
            this->change_dir_joystick(this->arr_key_controller[event.jaxis.which], -1);
        }
            /* Up-Down movement code goes here */
    }
}

void    Joystick::intro_pass() {
    main_event->menu->introstart = true;
    main_event->mode_menu = true;
}
