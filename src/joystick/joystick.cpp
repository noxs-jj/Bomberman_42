#include <joystick.hpp>
#include <event.class.hpp>
#include <Menu.class.hpp>

Joystick::Joystick(void) {}
Joystick::~Joystick(void) {}
// Joystick::Joystick( Joystick const & src ) {}
// Joystick::Joystick & operator=( Joystick const & rhs ) {}

void Joystick::read_key(int mode) {
  SDL_Event           event;
  int i = 0;
  // static float time = 0;
  // int _time = 0;
  static t_key		key = {0, 0, 0, 0};
	static t_key		key2 = {0, 0, 0, 0}; // key for p2
	static t_key		key3 = {0, 0, 0, 0};
  static t_key		key4 = {0, 0, 0, 0};
	static t_key		key5 = {0, 0, 0, 0};
  t_key *         arr_key[5];
  arr_key[0] = &key;
  arr_key[1] = &key2;
  arr_key[2] = &key3;
  arr_key[3] = &key4;
  arr_key[4] = &key5;

  // std::list<Entity *>::iterator it = main_event->char_list.begin();
	// std::list<Entity *>::iterator end = main_event->char_list.end();
  //
	// while (it != end) {
  //   if ((*it)->type == PLAYER) {
  //     printf("%d\n", (*it)->id);
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

          case SDLK_SPACE:    if (false == main_event->menu->introstart) {
            main_event->menu->introstart = true;
            main_event->mode_menu = true;
          }
          break;

          case SDLK_DOWN:     main_event->menu->move_menu_ver(1); break;
          case SDLK_UP:       main_event->menu->move_menu_ver(-1); break;
          case SDLK_RIGHT:    std::cout << "hey" << std::endl; break;
          case SDLK_LEFT:     std::cout << "hey" << std::endl; break;
          case SDLK_RETURN:   if (main_event->draw_winner_multi != 0
            || main_event->draw_winner_campaign != 0
            || main_event->draw_lose_campaign != 0
            || main_event->draw_end_campaign != 0) {
              main_event->draw_winner_multi = 0;
              main_event->draw_winner_campaign = 0;
              main_event->draw_lose_campaign = 0;
              main_event->draw_end_campaign = 0;
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
            case 0:   if (main_event->draw_winner_multi != 0
              || main_event->draw_winner_campaign != 0
              || main_event->draw_lose_campaign != 0
              || main_event->draw_end_campaign != 0) {
                main_event->draw_winner_multi = 0;
                main_event->draw_winner_campaign = 0;
                main_event->draw_lose_campaign = 0;
                main_event->draw_end_campaign = 0;
                main_event->mode_menu = false;
              }
              else
                main_event->menu->change_menu();
              break;
            case 1:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 2:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 3:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 4:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 5:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 6:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 7:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 8:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
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
              case SDL_HAT_LEFT:      fprintf(stdout, "joystick[%d] LEFT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_DOWN:      main_event->menu->move_menu_ver(1); break;
              case SDL_HAT_RIGHT:     fprintf(stdout, "joystick[%d] RIGHT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
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

    							case SDLK_KP_5:     key2.key_up = 1; break;
    							case SDLK_KP_8:     key2.key_down = 1; break;
    							case SDLK_KP_6:    	key2.key_right = 1; break;
    							case SDLK_KP_4:     key2.key_left = 1; break;
    							case SDLK_KP_0:    	main_event->player_bomb(main_event->config[1]); break;

    							case SDLK_s:     		key.key_up = 1; break;
    							case SDLK_w:       	key.key_down = 1; break;
    							case SDLK_d:    		key.key_right = 1; break;
    							case SDLK_a:     		key.key_left = 1; break;
    							case SDLK_SPACE:    main_event->player_bomb(main_event->config[0]); break;

    							case SDLK_k:     		key4.key_up = 1; break;
    							case SDLK_i:       	key4.key_down = 1; break;
    							case SDLK_l:    		key4.key_right = 1; break;
    							case SDLK_j:     		key4.key_left = 1; break;
    							case SDLK_n:    		main_event->player_bomb(main_event->config[3]); break;

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
                case 2:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 3:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 4:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 5:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 6:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 7:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
                case 8:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
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
                  case SDL_HAT_UP:        arr_key[event.jbutton.which]->key_down = 1; break;
                  case SDL_HAT_LEFT:      arr_key[event.jbutton.which]->key_left = 1; break;
                  case SDL_HAT_DOWN:      arr_key[event.jbutton.which]->key_up = 1; break;
                  case SDL_HAT_RIGHT:     arr_key[event.jbutton.which]->key_right = 1; break;
                  case SDL_HAT_CENTERED:  arr_key[event.jbutton.which]->key_down = 0;
                                          arr_key[event.jbutton.which]->key_up = 0;
                                          arr_key[event.jbutton.which]->key_left = 0;
                                          arr_key[event.jbutton.which]->key_right = 0;
                                          break;
                  default:                break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch((event).key.keysym.sym) {
    							case SDLK_KP_5:     key2.key_up = 0; break;
    							case SDLK_KP_8:     key2.key_down = 0; break;
    							case SDLK_KP_6:     key2.key_right = 0; break;
    							case SDLK_KP_4:     key2.key_left = 0; break;

    							case SDLK_s:     		key.key_up = 0; break;
    							case SDLK_w:       	key.key_down = 0; break;
    							case SDLK_d:    		key.key_right = 0; break;
    							case SDLK_a:     		key.key_left = 0; break;

    							case SDLK_k:     		key4.key_up = 0; break;
    							case SDLK_i:       	key4.key_down = 0; break;
    							case SDLK_l:    		key4.key_right = 0; break;
    							case SDLK_j:     		key4.key_left = 0; break;

    				      default: break;
    				    }
            }
        }

    	if (key.key_right)
    		main_event->player_move(main_event->config[0], DIR_RIGHT);
    	if (key.key_left)
    		main_event->player_move(main_event->config[0], DIR_LEFT);
    	if (key.key_up)
    		main_event->player_move(main_event->config[0], DIR_UP);
    	if (key.key_down)
    		main_event->player_move(main_event->config[0], DIR_BOTTOM);

    	if (key2.key_right)
    		main_event->player_move(main_event->config[1], DIR_RIGHT);
    	if (key2.key_left)
    		main_event->player_move(main_event->config[1], DIR_LEFT);
    	if (key2.key_up)
    		main_event->player_move(main_event->config[1], DIR_UP);
    	if (key2.key_down)
    		main_event->player_move(main_event->config[1], DIR_BOTTOM);

    	if (key3.key_right)
    		main_event->player_move(main_event->config[2], DIR_RIGHT);
    	if (key3.key_left)
    		main_event->player_move(main_event->config[2], DIR_LEFT);
    	if (key3.key_up)
    		main_event->player_move(main_event->config[2], DIR_UP);
    	if (key3.key_down)
    		main_event->player_move(main_event->config[2], DIR_BOTTOM);

    	if (key4.key_right)
    		main_event->player_move(main_event->config[3], DIR_RIGHT);
    	if (key4.key_left)
    		main_event->player_move(main_event->config[3], DIR_LEFT);
    	if (key4.key_up)
    		main_event->player_move(main_event->config[3], DIR_UP);
    	if (key4.key_down)
    		main_event->player_move(main_event->config[3], DIR_BOTTOM);
    }


  }
