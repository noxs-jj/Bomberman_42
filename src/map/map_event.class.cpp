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
#include <soundrender.class.hpp>

time_t  Map_event::game_start = 0;
time_t  Map_event::after_two_minutes = 0;
time_t  Map_event::after_three_minutes = 0;
time_t  Map_event::time_last_event = 0;
clock_t Map_event::time_last_demi_second = 0;
int     Map_event::last_y = 0;
int     Map_event::last_x = 0;
int     Map_event::barrage_iterator = 0;

Map_event::Map_event() {}

Map_event::~Map_event() {}

void    Map_event::init_clock_at_game_start() {
    Map_event::game_start = time(0);
    Map_event::after_two_minutes = Map_event::game_start + WARM_UP_1; // + 2 minutes
    Map_event::after_three_minutes = Map_event::game_start + WARN_UP_2; // + 3 minutes
    Map_event::last_y = 1;
    Map_event::last_x = 0;
    Map_event::barrage_iterator = 0;

    // std::cout << "Map_event::game_start ctime = " << ctime(&Map_event::game_start) << std::endl;
    // std::cout << "Map_event::game_start = " << Map_event::game_start << std::endl;
    // std::cout << "Map_event::game_start + 2 min = " << Map_event::after_two_minutes << std::endl;
    // std::cout << "Map_event::game_start + 3 min = " << Map_event::after_three_minutes << std::endl;
    // std::cout << "(CLOCKS_PER_SEC / 2) = " << (CLOCKS_PER_SEC / 2) << std::endl;
}

void    Map_event::check_warm_up() {
    if (0 == Map_event::game_start)
        return;

    if (main_event->multi >= 2 || main_event->arena >= 2) {
        time_t  current = time(0);
        time_t  current_demi_second = clock();

        // if (current >= Map_event::after_three_minutes && current - Map_event::time_last_event >= 1) {
        if (current >= Map_event::after_three_minutes && current_demi_second - Map_event::time_last_demi_second >= 250000) {
            if (current == Map_event::after_three_minutes) {
                main_event->soundrender->stopMusic();
                main_event->soundrender->playSound("warm_up_2");
            }
            Map_event::time_last_event = current;
            Map_event::time_last_demi_second = current_demi_second;
            Map_event::add_one_wall_to_map();

            // std::cout << ">= 3 min " << current;
            // std::cout << "  |  demiSecond " << current_demi_second << std::endl;
        }
        // else if (current >= Map_event::after_two_minutes && current - Map_event::time_last_event >= 1) {
        else if (current >= Map_event::after_two_minutes && current_demi_second - Map_event::time_last_demi_second >= 250000) {
            if (current == Map_event::after_two_minutes)
                main_event->soundrender->playMusic("warm_up_1");
            Map_event::time_last_event = current;
            Map_event::time_last_demi_second = current_demi_second;
            Map_event::add_one_wall_to_map();
            // std::cout << ">= 2 min" << current;
            // std::cout << "  |  demiSecond " << current_demi_second << std::endl;
        }
    }
}

void    Map_event::add_one_wall_to_map() {
    if ((Map_event::barrage_iterator >= 0 && Map_event::barrage_iterator <= 17) \
        || (Map_event::barrage_iterator >= 68 && Map_event::barrage_iterator <= 83) \
        || (Map_event::barrage_iterator >= 128 && Map_event::barrage_iterator <= 141) \
        || (Map_event::barrage_iterator >= 180 && Map_event::barrage_iterator <= 191)
        ) {
            Map_event::last_x++;
            Map_event::put_barrage_on_slop(Map_event::last_y, Map_event::last_x);
            Map_event::barrage_iterator++;
    }
    else if ((Map_event::barrage_iterator >= 18 && Map_event::barrage_iterator <= 34) \
        || (Map_event::barrage_iterator >= 84 && Map_event::barrage_iterator <= 98) \
        || (Map_event::barrage_iterator >= 142 && Map_event::barrage_iterator <= 154) \
        || (Map_event::barrage_iterator >= 192 && Map_event::barrage_iterator <= 202)
        ) {
            Map_event::last_y++;
            Map_event::put_barrage_on_slop(Map_event::last_y, Map_event::last_x);
            Map_event::barrage_iterator++;
    }
    else if ((Map_event::barrage_iterator >= 35 && Map_event::barrage_iterator <= 51) \
        || (Map_event::barrage_iterator >= 99 && Map_event::barrage_iterator <= 113) \
        || (Map_event::barrage_iterator >= 155 && Map_event::barrage_iterator <= 167) \
        || (Map_event::barrage_iterator >= 203 && Map_event::barrage_iterator <= 213)
        ) {
            Map_event::last_x--;
            Map_event::put_barrage_on_slop(Map_event::last_y, Map_event::last_x);
            Map_event::barrage_iterator++;
    }
    else if ((Map_event::barrage_iterator >= 52 && Map_event::barrage_iterator <= 67) \
        || (Map_event::barrage_iterator >= 114 && Map_event::barrage_iterator <= 127) \
        || (Map_event::barrage_iterator >= 168 && Map_event::barrage_iterator <= 179) \
        || (Map_event::barrage_iterator >= 214 && Map_event::barrage_iterator <= 222)
        ) {
            Map_event::last_y--;
            Map_event::put_barrage_on_slop(Map_event::last_y, Map_event::last_x);
            Map_event::barrage_iterator++;
    }
    // std::cout << "Map_event::last_x " << Map_event::last_x;
    // std::cout << "  |  Map_event::last_y " << Map_event::last_y;
    // std::cout << "  |  Map_event::barrage_iterator " << Map_event::barrage_iterator << std::endl;
}

void    Map_event::put_barrage_on_slop(int y, int x) {
    delete main_event->map[y][x];
    main_event->map[y][x] = NULL;
    main_event->map[y][x] = static_cast<Entity*>( Factory::create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_INDESTRUCTIBLE) );
}
