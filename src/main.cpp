#include <main.hpp>
#include <list>
void  				keyboard( void );

Event *		main_event = new Event();

int main( int ac, char **av ) {
	(void)(av);
	(void)(ac);

	//SoundRender sr;

	try {
		main_event->init(ac, av);
		// event->lauchGame();


		// delete main_event;
	}
	catch (std::exception & e){
		return (EXIT_FAILURE);
	}

	srand(clock());
	globject::init();
	// Entity map[20][20];

	// for (int i = 0; i < 20; i++)
	// {
	// 	for (int j = 0; j < 20; j++)
	// 	{
	// 		map[i][j].type = WALL;
	// 		if (!(rand() % 2))
	// 			map[i][j].type = 10;
	// 	}
	// }
	// std::list<Player*> lol;
	static float time = 0;
	for (int i = 0; i < 30; i++)
	{
		std::cout << globject::_object[WALL].parser._textID[i] << std::endl;
	}
	while (1)
	{
		if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
			continue ;
		keyboard();
		main_event->dec_timer();

		//usleep(300);

		// main_event->print_map(); // DEBUGG
		// sleep(1);

		//	std::cout << (1 / (clock() - time)) * CLOCKS_PER_SEC << std::endl;
		time = clock();
			const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RETURN]) {
			globject::resize(1300, 1300);
		}
		globject::render_all(main_event->map, main_event->char_list, NULL);
	}
    //Test graphique...
	return (EXIT_SUCCESS);
}

void keyboard(void)
{
	SDL_Event           event;
	static t_key		key = {0, 0, 0, 0};

	while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch((event).key.keysym.sym) {
			case SDLK_ESCAPE:   _exit(0); break;
                // case SDLK_ESCAPE:    this->addKey(ECHAP); break;
                // case SDLK_q:     this->addKey(ECHAP); break;
			case SDLK_DOWN:     key.key_up = 1; break;
                // case SDLK_s:     this->addKey(DOWN); break;
			case SDLK_UP:       key.key_down = 1; break;
                // case SDLK_w:     this->addKey(UP); break;
			case SDLK_RIGHT:    key.key_right = 1; break;
                // case SDLK_d:     this->addKey(RIGHT); break;
			case SDLK_LEFT:     key.key_left = 1; break;
			    // case SDLK_a:     this->addKey(LEFT); break;
			case SDLK_SPACE:    main_event->player_bomb(PLAYER1); break;
                // case SDLK_p:     this->addKey(SPACE); break;
                // case SDLK_1:     this->addKey(ONE); break;
                // case SDLK_2:     this->addKey(TWO); break;
                // case SDLK_3:     this->addKey(THREE); break;
			default: break;
			}
		}
        if (event.type == SDL_KEYUP) {
            switch((event).key.keysym.sym) {
                // case SDLK_ESCAPE:    this->addKey(ECHAP); break;
                // case SDLK_q:     this->addKey(ECHAP); break;
            case SDLK_DOWN:     key.key_up = 0; break;
                // case SDLK_s:     this->addKey(DOWN); break;
            case SDLK_UP:       key.key_down = 0; break;
                // case SDLK_w:     this->addKey(UP); break;
            case SDLK_RIGHT:    key.key_right = 0; break;
                // case SDLK_d:     this->addKey(RIGHT); break;
            case SDLK_LEFT:     key.key_left = 0; break;
                // case SDLK_a:     this->addKey(LEFT); break;
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
}
/*
void  				keyboard( void ) {
	SDL_Event 			event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch((event).key.keysym.sym) {
				case SDLK_ESCAPE:	_exit(0); break;
				// case SDLK_ESCAPE:	this->addKey(ECHAP); break;
				// case SDLK_q:		this->addKey(ECHAP); break;
				case SDLK_DOWN:		main_event->player_move(PLAYER1, DIR_UP); break;
				// case SDLK_s:		this->addKey(DOWN); break;
				case SDLK_UP:		main_event->player_move(PLAYER1, DIR_BOTTOM); break;
				// case SDLK_w:		this->addKey(UP); break;
				case SDLK_RIGHT:	main_event->player_move(PLAYER1, DIR_RIGHT); break;
				// case SDLK_d:		this->addKey(RIGHT); break;
				case SDLK_LEFT:		main_event->player_move(PLAYER1, DIR_LEFT); break;
				// case SDLK_a:		this->addKey(LEFT); break;
				case SDLK_SPACE:	main_event->player_bomb(PLAYER1); break;
				// case SDLK_p:		this->addKey(SPACE); break;
				// case SDLK_1:		this->addKey(ONE); break;
				// case SDLK_2:		this->addKey(TWO); break;
				// case SDLK_3:		this->addKey(THREE); break;
				default: break;
			}
		}
	}
}
*/
