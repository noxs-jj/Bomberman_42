#include <main.hpp>
#include <list>
#include <Menu.class.hpp>
#include <ia.class.hpp>
void			keyboard( void ); // A Mettre dans main.hpp

Event *		main_event = new Event(); // GLOBAL

int main( int ac, char **av ) {
	std::srand(std::time(0));
	(void)(av);
	(void)(ac);
	ft42::logg = true;
	int _time = 0;
	Ia * ia_play = new Ia();

	try {
		if (main_event == NULL) {
			std::cerr << "Event Global allocation error" << std::endl;
			throw std::exception();
		}
		main_event->menu = new Menu(main_event);
		if (main_event->menu == NULL) {
			main_event->w_full("Menu allocation error");
			throw std::exception();
		}
		if (ia_play == NULL) {
			ia_play->w_full("Menu allocation error");
			throw std::exception();
		}
		if (TTF_Init() != 0){
			main_event->w_full("TTF_init initialization error ");
			throw std::exception();
		}

		// main_event->render = new globject();
		// if (main_event->render == NULL) {
		// 	std::cerr << "main_event->render globject allocation error" << std::endl;
		// 	throw std::exception();
		// }


		ft42::logg = true; // ceci active les debugg ecran et fichier
		// std::atexit(TTF_Quit);
		srand(clock());
		globject::init();
		// main_event->render->init();
		main_event->mode_menu = true;
		main_event->menu->init();
		main_event->menu->introstart = false;
		main_event->w_log("Event Init");
		// main_event->print_map(); // DEBUGG
		main_event->load_sounds();
		main_event->soundrender->playSound("startup");

		std::cout << "ac= " << ac << std::endl;
		main_event->init(ac, av);

		main_event->menu->main_loop();


		// music
		main_event->soundrender->playMusic("music");

		// for (int i = 0; i < 30; i++) {
		// 	std::cout << main_event->render->_object[WALL].parser._textID[i] << std::endl;
		// }
		static float time = 0;
		while (true == main_event->event_running) {
			if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
				continue ;
				_time++;
				_time = _time % 60;
			keyboard();
			ia_play->start(time);
			if (main_event->event_running == false)
				break;
			main_event->dec_timer();
			time = clock();
				const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_RETURN]) {
				main_event->render->resize(1300, 1300);
			}
			if (false == main_event->mode_menu)
				main_event->render->render_all(main_event->map, main_event->char_list, NULL);
			else
				main_event->menu->main_loop();
		}

		main_event->w_log("Delete Main Event then EXIT");
		if (NULL != main_event)
			delete main_event;
	}
	catch (std::exception & e){
		std::cerr << "EXIT_FAILURE " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
  std::cout << "EXIT_SUCCESS" << std::endl;

	return (EXIT_SUCCESS);
}

void keyboard(void) {
	SDL_Event       event;
	static t_key		key = {0, 0, 0, 0};
	static t_key		key2 = {0, 0, 0, 0}; // key for p2
	static t_key		key3 = {0, 0, 0, 0};
	static t_key		key4 = {0, 0, 0, 0};

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
				else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
					std::cout << "controller key down" << std::endl;
				  switch (event.cbutton.button) {
						case SDL_CONTROLLER_BUTTON_A             : main_event->player_bomb(main_event->config[2]); break;
						case SDL_CONTROLLER_BUTTON_B             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_X             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_Y             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_BACK          : (void)0; break;
						case SDL_CONTROLLER_BUTTON_GUIDE         : (void)0; break;
						case SDL_CONTROLLER_BUTTON_START         : (void)0; break;
						case SDL_CONTROLLER_BUTTON_LEFTSTICK     : (void)0; break;
						case SDL_CONTROLLER_BUTTON_RIGHTSTICK    : (void)0; break;
						case SDL_CONTROLLER_BUTTON_LEFTSHOULDER  : (void)0; break;
						case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER : (void)0; break;
						case SDL_CONTROLLER_BUTTON_DPAD_UP       : key3.key_down = true; break;
						case SDL_CONTROLLER_BUTTON_DPAD_DOWN     : key3.key_up = true; break;
						case SDL_CONTROLLER_BUTTON_DPAD_LEFT     : key3.key_left = true; break;
						case SDL_CONTROLLER_BUTTON_DPAD_RIGHT    : key3.key_right = true; break;
						case SDL_CONTROLLER_BUTTON_MAX           : (void)0; break;
						default: break;
				  }
				}
				else if (event.type == SDL_CONTROLLERBUTTONUP) {
				  switch (event.cbutton.button) {
						case SDL_CONTROLLER_BUTTON_A             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_B             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_X             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_Y             : (void)0; break;
						case SDL_CONTROLLER_BUTTON_BACK          : (void)0; break;
						case SDL_CONTROLLER_BUTTON_GUIDE         : (void)0; break;
						case SDL_CONTROLLER_BUTTON_START         : (void)0; break;
						case SDL_CONTROLLER_BUTTON_LEFTSTICK     : (void)0; break;
						case SDL_CONTROLLER_BUTTON_RIGHTSTICK    : (void)0; break;
						case SDL_CONTROLLER_BUTTON_LEFTSHOULDER  : (void)0; break;
						case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER : (void)0; break;
						case SDL_CONTROLLER_BUTTON_DPAD_UP       : key3.key_down = false; break;
						case SDL_CONTROLLER_BUTTON_DPAD_DOWN     : key3.key_up = false; break;
						case SDL_CONTROLLER_BUTTON_DPAD_LEFT     : key3.key_left = false; break;
						case SDL_CONTROLLER_BUTTON_DPAD_RIGHT    : key3.key_right = false; break;
						case SDL_CONTROLLER_BUTTON_MAX           : (void)0; break;
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
