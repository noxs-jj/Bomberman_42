#include <main.hpp>
#include <list>
#include <Menu.class.hpp>
#include <ia.class.hpp>
#include <joystick.hpp>

Event *	main_event = new Event(); // GLOBAL

int		main( int ac, char **av ) {
	int				_time = 0;
	Ia *			ia_play = NULL;
	static float	time = 0;

	std::srand(std::time(0));
	(void)(av);
	(void)(ac);
	ft42::logg = true;

	try {
		if (main_event == NULL) {
			std::cerr << "Event Global allocation error" << std::endl;
			throw std::exception();
		}
		ia_play = new Ia();
		if (ia_play == NULL) {
			main_event->w_full("ia_play allocation error");
			throw std::exception();
		}
		main_event->menu = new Menu(main_event);
		if (main_event->menu == NULL) {
			main_event->w_full("Menu allocation error");
			throw std::exception();
		}
		if (TTF_Init() != 0){
			main_event->w_full("TTF_init initialization error ");
			throw std::exception();
		}
		main_event->joystick = new Joystick();
		if (main_event->joystick == NULL) {
			main_event->w_full("Joystick allocation error");
			throw std::exception();
		}

		ft42::logg = true; // ceci active les debugg ecran et fichier
		// std::atexit(TTF_Quit);
		srand(clock());
		# ifdef linux
			globject::init(1600, 900);
		#endif
		# ifdef __APPLE__
			globject::init(2560, 1440);
		#endif
		// main_event->render->init();
		main_event->mode_menu = true;
		main_event->menu->init();
		main_event->menu->introstart = false;
		main_event->w_log("Event Init");
		// main_event->print_map(); // DEBUGG
		main_event->load_sounds();
		main_event->soundrender->playSound("startup");

		main_event->init(ac, av);
		main_event->menu->main_loop();

		// music
		main_event->soundrender->playMusic("music");


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
