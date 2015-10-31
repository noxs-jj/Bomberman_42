#include <main.hpp>
#include <list>
#include <Menu.class.hpp>
void		keyboard( void ); // A Mettre dans main.hpp
Event *		main_event = new Event(); // GLOBAL

int main( int ac, char **av ) {
	(void)(av);
	(void)(ac);

	try {
		if (main_event == NULL) {
			std::cerr << "Event Global allocation error" << std::endl;
			throw std::exception();
		}
		Menu * menu = new Menu(main_event);
		if (menu == NULL) {
			main_event->w_full("Menu allocation error");
			throw std::exception();
		}
		if (TTF_Init() != 0){
			main_event->w_full("TTF_init initialization error ");
			throw std::exception();
		}
		atexit(TTF_Quit);
		srand(clock());
		globject::init();
		main_event->mode_menu = true;
		menu->init();
		menu->introstart = false;
		static float time = 0;
		main_event->init(ac, av);


		for (int i = 0; i < 30; i++) {
			std::cout << globject::_object[WALL].parser._textID[i] << std::endl;
		}

		while (1) {
			if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
				continue ;
			keyboard();
			main_event->dec_timer();
			time = clock();
				const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_RETURN]) {
				globject::resize(1300, 1300);
			}


			if (false == main_event->mode_menu)
				globject::render_all(main_event->map, main_event->char_list, NULL);
			else
				menu->main_loop();
			std::cerr << "qpwoei" << std::endl;

		}





		delete main_event;
	}
	catch (std::exception & e){
		std::cerr << "EXIT_FAILURE" << std::endl;
		return (EXIT_FAILURE);
	}
  std::cout << "EXIT_SUCCESS" << std::endl;
	return (EXIT_SUCCESS);
}

void keyboard(void) {
	SDL_Event           event;
	static t_key		key = {0, 0, 0, 0};
	static t_key		key2 = {0, 0, 0, 0}; // key for p2
	// static t_key		key3 = {0, 0, 0, 0};
	// static t_key		key4 = {0, 0, 0, 0};

	while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch((event).key.keysym.sym) {
			case SDLK_ESCAPE:   _exit(0); break;
			case SDLK_DOWN:     key.key_up = 1; break;
			case SDLK_UP:       key.key_down = 1; break;
			case SDLK_RIGHT:    key.key_right = 1; break;
			case SDLK_LEFT:     key.key_left = 1; break;
			case SDLK_KP_0:    	main_event->player_bomb(PLAYER1); break;
			case SDLK_s:     		key2.key_up = 1; break;
			case SDLK_w:       	key2.key_down = 1; break;
			case SDLK_d:    		key2.key_right = 1; break;
			case SDLK_a:     		key2.key_left = 1; break;
			case SDLK_SPACE:    main_event->player_bomb(PLAYER2); break;

			case SDLK_p:        if (true == main_event->mode_menu)
														main_event->mode_menu = false;
													else
														main_event->mode_menu = true;
													break;

			default: break;
			}
		}
        if (event.type == SDL_KEYUP) {
            switch((event).key.keysym.sym) {
            case SDLK_DOWN:     key.key_up = 0; break;
            case SDLK_UP:       key.key_down = 0; break;
            case SDLK_RIGHT:    key.key_right = 0; break;
            case SDLK_LEFT:     key.key_left = 0; break;
						case SDLK_s:     key2.key_up = 0; break;
            case SDLK_w:       key2.key_down = 0; break;
            case SDLK_d:    key2.key_right = 0; break;
            case SDLK_a:     key2.key_left = 0; break;
            default: break;
            }
        }
    }
	if (key.key_right)
		main_event->player_move(PLAYER1, DIR_RIGHT);
  if (key.key_left)
		main_event->player_move(PLAYER1, DIR_LEFT);
  if (key.key_up)
		main_event->player_move(PLAYER1, DIR_UP);
  if (key.key_down)
		main_event->player_move(PLAYER1, DIR_BOTTOM);

	if (key2.key_right)
		main_event->player_move(PLAYER2, DIR_RIGHT);
	if (key2.key_left)
		main_event->player_move(PLAYER2, DIR_LEFT);
	if (key2.key_up)
		main_event->player_move(PLAYER2, DIR_UP);
	if (key2.key_down)
		main_event->player_move(PLAYER2, DIR_BOTTOM);
}
