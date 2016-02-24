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

#include <map_event.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>
#include <entity.class.hpp>
#include <wall.class.hpp>

time_t  Map_event::game_start = 0;
time_t  Map_event::after_two_minutes = 0;
time_t  Map_event::after_three_minutes = 0;
time_t  Map_event::time_last_event = 0;
int     Map_event::last_y = 0;
int     Map_event::last_x = 0;
int     Map_event::barrage_iterator = 0;

Map_event::Map_event() {}

Map_event::~Map_event() {}

void    Map_event::init_clock_at_game_start() {
    // Map_event::game_start = time(&Map_event::game_start);
    Map_event::game_start = time(0);
    Map_event::after_two_minutes = Map_event::game_start + 1; // + 2 minutes
    Map_event::after_three_minutes = Map_event::game_start + 2; // + 3 minutes
    Map_event::last_y = 1;
    Map_event::last_x = 0;
    Map_event::barrage_iterator = 0;

    std::cout << "Map_event::game_start ctime = " << ctime(&Map_event::game_start) << std::endl;
    std::cout << "Map_event::game_start = " << Map_event::game_start << std::endl;
    std::cout << "Map_event::game_start + 2 min = " << Map_event::after_two_minutes << std::endl;
    std::cout << "Map_event::game_start + 3 min = " << Map_event::after_three_minutes << std::endl;
    std::cout << "(CLOCKS_PER_SEC / 2) = " << (CLOCKS_PER_SEC / 2) << std::endl;
}

void    Map_event::check_warm_up() {
    if (0 == Map_event::game_start)
        return;

    // if (main_event->multi >= 2 || main_event->arena >= 2) {
        time_t  current = time(0);

        if (current >= Map_event::after_three_minutes && current - Map_event::time_last_event >= 1) {
            Map_event::time_last_event = current;
            Map_event::add_one_wall_to_map();
            std::cout << ">= 3 min " << current << std::endl;
        }
        else if (current >= Map_event::after_two_minutes && current - Map_event::time_last_event >= 1) {
            Map_event::time_last_event = current;
            Map_event::add_one_wall_to_map();
            std::cout << ">= 2 min" << current << std::endl;
        }
    // }
}

void    Map_event::add_one_wall_to_map() {
    std::cout << "deb 0" << std::endl;
    if (Map_event::last_y == 1) {
        std::cout << "deb 1" << std::endl;
        if (Map_event::last_x < globject::mapX_size) {
            Map_event::last_x++;
            if (Map_event::last_x >= globject::mapX_size) {
                std::cout << "deb 2" << std::endl;
                Map_event::last_y++;
                Map_event::last_x = 0;
            }
            std::cout << "Map_event::last_x " << Map_event::last_x << "  |  Map_event::last_y " << Map_event::last_y << std::endl;
            Map_event::put_barrage_on_slop(Map_event::last_y, Map_event::last_x);
        }
    }
}

void    Map_event::put_barrage_on_slop(int y, int x) {
    std::cout << "deb 3" << std::endl;
    delete main_event->map[y][x];
    main_event->map[y][x] = NULL;
    std::cout << "deb 4" << std::endl;
    main_event->map[y][x] = static_cast<Entity*>( Factory::create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_INDESTRUCTIBLE) );
    std::cout << "deb 5" << std::endl;
}
