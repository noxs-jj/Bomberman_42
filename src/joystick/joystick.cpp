/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joystick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/06 13:36:40 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <joystick.hpp>
#include <event.class.hpp>
#include <Menu.class.hpp>

Joystick::Joystick(void) {
	this->config[0] = 1;
	this->config[1] = 1;
	this->config[2] = 0;
	this->config[3] = 0;
	this->config[4] = 0;
	int	devices = SDL_NumJoysticks();

	SDL_JoystickEventState(SDL_ENABLE);
	if (devices > 0) {
		this->manette1 = SDL_JoystickOpen(0);
		if (this->manette1 < 0) {
			std::cerr << "Could not open joystick 1 " << SDL_GetError() << std::endl;
			throw std::exception();
		}
	}
	if (devices > 1) {
		this->manette2 = SDL_JoystickOpen(1);
		if (this->manette2 < 0) {
			std::cerr << "Could not open joystick 2 " << SDL_GetError() << std::endl;
			throw std::exception();
		}
	}
}

Joystick::~Joystick(void) {}
// Joystick::Joystick( Joystick const & src ) {}
// Joystick::Joystick & operator=( Joystick const & rhs ) {}

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
	static t_key		key = {0, 0, 0, 0};
	static t_key		key2 = {0, 0, 0, 0}; // key for p2 (keyboard)
	static t_key		key3 = {0, 0, 0, 0};
	static t_key		key4 = {0, 0, 0, 0};
	static t_key		key5 = {0, 0, 0, 0};


	static t_key		ckey = {0, 0, 0, 0};
	static t_key		ckey2 = {0, 0, 0, 0}; // key for p2 (controller)
	static t_key		ckey3 = {0, 0, 0, 0};
	static t_key		ckey4 = {0, 0, 0, 0};
	static t_key		ckey5 = {0, 0, 0, 0};

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

	if (this->config[0] == 0) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
	}
	else {
		main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
		nbr_keyboard++;
	}
	i++;
	if (this->config[1] == 0) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
	}
	else {
		main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
		nbr_keyboard++;
	}
	i++;
	if (this->config[2] == 0) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
	}
	else {
		main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
		nbr_keyboard++;
	}
	i++;
	if (this->config[3] == 0) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
	}
	else {
		main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
		nbr_keyboard++;
	}
	i++;
	if (this->config[4] == 0) {
		main_event->config[nbr] = PLAYER1 + i;
		nbr++;
	}
	else {
		main_event->config_keyboard[nbr_keyboard] = PLAYER1 + i;
		nbr_keyboard++;
	}
	std::cout << "set_key_config " << main_event->config_keyboard[0] << " " << " " << PLAYER1 << std::endl;
}

void Joystick::read_key(int mode) {
	SDL_Event			event;
	int					i = 0;
  // static float time = 0;
  // int _time = 0;
	// static t_key		key = {0, 0, 0, 0};
	// static t_key		key2 = {0, 0, 0, 0}; // key for p2 (keyboard)
	// static t_key		key3 = {0, 0, 0, 0};
	// static t_key		key4 = {0, 0, 0, 0};


  // std::list<Entity *>::iterator it = main_event->char_list.begin();
	// std::list<Entity *>::iterator end = main_event->char_list.end();

  // printf("%d\n", main_event->config[0]);
  // printf("%d\n", main_event->config[1]);
	// while (it != end) {
  //   if ((*it)->type == PLAYER) {
  //     printf("id %d player %d\n", (*it)->id, (*it)->model);
	// 	}
  //   it++;
  // }

  // if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
  //   return ;
  //   _time++;
  //   _time = _time % 60;
  if (mode == 0){
    while (SDL_PollEvent(&event) && main_event->event_running == true) {
      if (event.type == SDL_KEYDOWN) {
        std::cout << "(event).key.keysym.sym " << (event).key.keysym.sym << std::endl;
        switch((event).key.keysym.sym) {
          case SDLK_ESCAPE:   main_event->exit_free();
          break;

          // case SDLK_SPACE:
          // break;

          case SDLK_DOWN:     main_event->menu->move_menu_ver(1); break;
          case SDLK_UP:       main_event->menu->move_menu_ver(-1); break;
					case SDLK_RIGHT:    main_event->menu->move_menu_hor(); break;
          case SDLK_LEFT:    main_event->menu->move_menu_hor(); break;
          case SDLK_RETURN:   if (false == main_event->menu->introstart) {
            main_event->menu->introstart = true;
            main_event->mode_menu = true;
          }
          else if (main_event->draw_winner_multi >= 0
            || main_event->draw_winner_campaign >= 0
            || main_event->draw_lose_campaign >= 0
            || main_event->draw_end_campaign >= 0) {
              main_event->draw_winner_multi = -1;
              main_event->draw_winner_campaign = -1;
              main_event->draw_lose_campaign = -1;
              main_event->draw_end_campaign = -1;
              main_event->mode_menu = false;
            }
            else
              main_event->menu->change_menu();
            break;
            case SDLK_p:        if (true == main_event->mode_menu && main_event->game_playing == true)
            main_event->mode_menu = false;
            else if (main_event->game_playing == true)
            main_event->mode_menu = true;
            break;
						case SDLK_1: 		if (main_event->menu->menu_selected == BIG_MENU && main_event->game_playing == true
															&& main_event->multi == 0 && main_event->arena == 0) {
														main_event->draw_winner_multi = -1;
													  main_event->draw_winner_campaign = -1;
													  main_event->draw_lose_campaign = -1;
													  main_event->draw_end_campaign = -1;
														// main_event->config[0] = PLAYER1;
														// if (main_event->coop > 0)
													  	// main_event->config[1] = PLAYER2;
													  main_event->mode_menu = false;
													  main_event->make_new_game(1);
													  main_event->game_playing = true;
													}
													break;
						case SDLK_2:	if (main_event->menu->menu_selected == BIG_MENU && main_event->game_playing == false) {
														this->test = 1;
														main_event->make_new_game(0);
														main_event->mode_menu = false;
														main_event->game_playing = true;
														// main_event->config[0] = PLAYER1;

														this->test = 0;
													}
													break;
						case SDLK_3:	if (main_event->menu->menu_selected == BIG_MENU && main_event->game_playing == true) {
														main_event->cheat_stats();
													}
													break;
            case SDLK_c:        std::cout << "SDL_NumJoysticks(void) " << SDL_NumJoysticks() << std::endl;
            while ( i < SDL_NumJoysticks() ){
              printf("    %s\n", SDL_GameControllerNameForIndex(i) );
              i++;
            }
            break;

            default: break;
          }
        }
        // JOYSTICK BUTTON
        else if (event.type == SDL_JOYBUTTONDOWN) {
          switch (event.cbutton.button) {
            case 0:   if (false == main_event->menu->introstart) {
              main_event->menu->introstart = true;
              main_event->mode_menu = true;
            }
            else if (main_event->draw_winner_multi >= 0
              || main_event->draw_winner_campaign >= 0
              || main_event->draw_lose_campaign >= 0
              || main_event->draw_end_campaign >= 0) {
                main_event->draw_winner_multi = -1;
                main_event->draw_winner_campaign = -1;
                main_event->draw_lose_campaign = -1;
                main_event->draw_end_campaign = -1;
                main_event->mode_menu = false;
              }
              else
                main_event->menu->change_menu();
              break;
            case 1:   main_event->menu->change_menu_back(); break;
            case 2:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 3:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 4:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 5:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 6:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 7:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 8:   if (true == main_event->mode_menu && main_event->game_playing == true)
            main_event->mode_menu = false;
            else if (main_event->game_playing == true)
            main_event->mode_menu = true;
            break;
            case 9:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 10:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 11:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 12:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            default: break;
          }
        }
        // JOYSTICK CROIX DIRECTIONNEL
        else if (event.type == SDL_JOYHATMOTION) {
          if (0 == event.jhat.hat && 0 != event.jhat.value)
          {
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
      }
    }
    else {
      while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch((event).key.keysym.sym) {
    							case SDLK_ESCAPE:   main_event->exit_free();
    																	break;

    							case SDLK_KP_5:     this->arr_key_keyboard[1]->key_up = 1; break;
    							case SDLK_KP_8:     this->arr_key_keyboard[1]->key_down = 1; break;
    							case SDLK_KP_6:    	this->arr_key_keyboard[1]->key_right = 1; break;
    							case SDLK_KP_4:     this->arr_key_keyboard[1]->key_left = 1; break;
									case SDLK_KP_PLUS: 			main_event->player_bomb(main_event->config_keyboard[1]); break;
									case SDLK_KP_MINUS: 		main_event->remote_put(main_event->config_keyboard[1]); break;
									case SDLK_KP_MULTIPLY: 	main_event->remote_detonate(main_event->config_keyboard[1]); break;

    							case SDLK_s:     		this->arr_key_keyboard[0]->key_up = 1; break;
    							case SDLK_w:       	this->arr_key_keyboard[0]->key_down = 1; break;
    							case SDLK_d:    		this->arr_key_keyboard[0]->key_right = 1; break;
    							case SDLK_a:     		this->arr_key_keyboard[0]->key_left = 1; break;
									case SDLK_c: 				main_event->player_bomb(main_event->config_keyboard[0]); break;
									case SDLK_v: 				main_event->remote_put(main_event->config_keyboard[0]); break;
									case SDLK_b: 				main_event->remote_detonate(main_event->config_keyboard[0]); break;

    							case SDLK_p:        if (true == main_event->mode_menu && main_event->game_playing == true)
    																		main_event->mode_menu = false;
    																	else if (main_event->game_playing == true)
    																		main_event->mode_menu = true;
    																	break;

    							default: break;
    						}
    				}
            // JOYSTICK BUTTON
            else if (event.type == SDL_JOYBUTTONDOWN) {
              switch (event.cbutton.button) {
                case 0:   main_event->player_bomb(main_event->config[event.jbutton.which]); break;
                case 1:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 2:   main_event->remote_put(main_event->config[event.jbutton.which]); break;
                case 3:   main_event->remote_detonate(main_event->config[event.jbutton.which]); break;
                case 4:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 5:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 6:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 7:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 8:   if (true == main_event->mode_menu && main_event->game_playing == true)
                main_event->mode_menu = false;
                else if (main_event->game_playing == true)
                main_event->mode_menu = true;
                break;
                case 9:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 10:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 11:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 12:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                default: break;
              }
            }
            // JOYSTICK CROIX DIRECTIONNEL
            else if (event.type == SDL_JOYHATMOTION) {
                switch (event.jhat.value) {
                  case SDL_HAT_UP:        change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_UP); break;
                  case SDL_HAT_LEFT:      change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_LEFT); break;
                  case SDL_HAT_DOWN:      change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_BOTTOM); break;
                  case SDL_HAT_RIGHT:     change_dir_joystick(this->arr_key_controller[event.jbutton.which], DIR_RIGHT); break;
                  case SDL_HAT_CENTERED:  change_dir_joystick(this->arr_key_controller[event.jbutton.which], -1); break;
                  default:                break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch((event).key.keysym.sym) {
    							case SDLK_KP_5:     this->arr_key_keyboard[1]->key_up = 0; break;
    							case SDLK_KP_8:     this->arr_key_keyboard[1]->key_down = 0; break;
    							case SDLK_KP_6:     this->arr_key_keyboard[1]->key_right = 0; break;
    							case SDLK_KP_4:     this->arr_key_keyboard[1]->key_left = 0; break;

    							case SDLK_s:     		this->arr_key_keyboard[0]->key_up = 0; break;
    							case SDLK_w:       	this->arr_key_keyboard[0]->key_down = 0; break;
    							case SDLK_d:    		this->arr_key_keyboard[0]->key_right = 0; break;
    							case SDLK_a:     		this->arr_key_keyboard[0]->key_left = 0; break;


    				      default: break;
    				    }
            }
        }
			if (this->arr_key_keyboard[0]->key_right)
				main_event->player_move(main_event->config_keyboard[0], DIR_RIGHT);
			if (this->arr_key_keyboard[0]->key_left)
				main_event->player_move(main_event->config_keyboard[0], DIR_LEFT);
			if (this->arr_key_keyboard[0]->key_up)
				main_event->player_move(main_event->config_keyboard[0], DIR_UP);
			if (this->arr_key_keyboard[0]->key_down)
				main_event->player_move(main_event->config_keyboard[0], DIR_BOTTOM);

			if (this->arr_key_keyboard[1]->key_right)
				main_event->player_move(main_event->config_keyboard[1], DIR_RIGHT);
			if (this->arr_key_keyboard[1]->key_left)
				main_event->player_move(main_event->config_keyboard[1], DIR_LEFT);
			if (this->arr_key_keyboard[1]->key_up)
				main_event->player_move(main_event->config_keyboard[1], DIR_UP);
			if (this->arr_key_keyboard[1]->key_down)
				main_event->player_move(main_event->config_keyboard[1], DIR_BOTTOM);

			if (this->arr_key_controller[0]->key_right)
				main_event->player_move(main_event->config[0], DIR_RIGHT);
			if (this->arr_key_controller[0]->key_left)
				main_event->player_move(main_event->config[0], DIR_LEFT);
			if (this->arr_key_controller[0]->key_up)
				main_event->player_move(main_event->config[0], DIR_UP);
			if (this->arr_key_controller[0]->key_down)
				main_event->player_move(main_event->config[0], DIR_BOTTOM);


			if (this->arr_key_controller[1]->key_right)
				main_event->player_move(main_event->config[1], DIR_RIGHT);
			if (this->arr_key_controller[1]->key_left)
				main_event->player_move(main_event->config[1], DIR_LEFT);
			if (this->arr_key_controller[1]->key_up)
				main_event->player_move(main_event->config[1], DIR_UP);
			if (this->arr_key_controller[1]->key_down)
				main_event->player_move(main_event->config[1], DIR_BOTTOM);


			if (this->arr_key_controller[2]->key_right)
				main_event->player_move(main_event->config[2], DIR_RIGHT);
			if (this->arr_key_controller[2]->key_left)
				main_event->player_move(main_event->config[2], DIR_LEFT);
			if (this->arr_key_controller[2]->key_up)
				main_event->player_move(main_event->config[2], DIR_UP);
			if (this->arr_key_controller[2]->key_down)
				main_event->player_move(main_event->config[2], DIR_BOTTOM);


			if (this->arr_key_controller[3]->key_right)
				main_event->player_move(main_event->config[3], DIR_RIGHT);
			if (this->arr_key_controller[3]->key_left)
				main_event->player_move(main_event->config[3], DIR_LEFT);
			if (this->arr_key_controller[3]->key_up)
				main_event->player_move(main_event->config[3], DIR_UP);
			if (this->arr_key_controller[3]->key_down)
				main_event->player_move(main_event->config[3], DIR_BOTTOM);

			if (this->arr_key_controller[4]->key_right)
				main_event->player_move(main_event->config[4], DIR_RIGHT);
			if (this->arr_key_controller[4]->key_left)
				main_event->player_move(main_event->config[4], DIR_LEFT);
			if (this->arr_key_controller[4]->key_up)
				main_event->player_move(main_event->config[4], DIR_UP);
			if (this->arr_key_controller[4]->key_down)
				main_event->player_move(main_event->config[4], DIR_BOTTOM);
    }
  }

void Joystick::change_dir_joystick(t_key *key, int dir) {
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
