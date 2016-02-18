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

#include <main.hpp>
#include <list>
#include <Menu.class.hpp>
#include <ia.class.hpp>
#include <joystick.hpp>
#include <save.class.hpp>

Event *	main_event = Factory::create_event(); // GLOBAL

int		main( int ac, char **av ) {
	int            _time = 0;
	Ia *           ia_play = NULL;
    Save *         save = NULL;
	static float   time = 0;

	std::srand(std::time(0));
	ft42::logg = true;

    save = new Save();
    if (NULL == save) {
        std::cout << "Save() allocation error" << std::endl;
        return (-1);
    }

	try {
        ia_play = Factory::create_ia();
        main_event->menu = Factory::create_menu(main_event);
        main_event->joystick = Factory::create_joystick();
        main_event->soundrender = Factory::create_sound_render();
        if (TTF_Init() != 0){
            main_event->w_full("TTF_init initialization error ");
            throw std::exception();
        }

        main_event->init(ac, av);
        // std::atexit(TTF_Quit);
        srand(clock());
        globject::init(800, 600);

        main_event->joystick->load_config();

        main_event->mode_menu = true;
        main_event->menu->init();
        main_event->menu->introstart = false;
        main_event->w_log("Event Init");

        main_event->soundrender->load_files();
        main_event->soundrender->playSound("startup");
        main_event->soundrender->playMusic("ps1");

        main_event->menu->main_loop();
        while (true == main_event->event_running) {
            if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60) {
                continue ;
            }
            _time++;
            _time = _time % 60;
            main_event->joystick->read_key(1);
            ia_play->start(time);
            if (main_event->event_running == false)
                break;
            main_event->dec_timer();
            time = clock();
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
