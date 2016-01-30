#include <main.hpp>
#include <list>
#include <Menu.class.hpp>
#include <ia.class.hpp>
#include <joystick.hpp>

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
		// globject::init(1600, 900);
		globject::init(2560, 1440);
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
		main_event->joystick = new Joystick();

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
			main_event->joystick->read_key(1);
			ia_play->start(time);
			if (main_event->event_running == false)
				break;
			main_event->dec_timer();
			time = clock();
				//const Uint8 *state = SDL_GetKeyboardState(NULL);

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
