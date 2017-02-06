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
#include <bomb.class.hpp>
#include <soundrender.class.hpp>

time_t  Map_event::game_start = 0;
time_t  Map_event::after_two_minutes = 0;
time_t  Map_event::after_three_minutes = 0;
time_t  Map_event::time_last_event = 0;
clock_t Map_event::time_last_demi_second = 0;
int     Map_event::last_y = 0;
int     Map_event::last_x = 0;
int     Map_event::barrage_iterator = 0;
int     Map_event::barrage_x = 0;
int     Map_event::barrage_y = 0;
bool    Map_event::first_barrage = false;
bool    Map_event::second_barrage = false;

Map_event::Map_event() {}

Map_event::~Map_event() {}

void    Map_event::init_clock_at_game_start() {
    Map_event::game_start = time(0);
    Map_event::after_two_minutes = Map_event::game_start + WARM_UP_1; // + 1 minutes
    Map_event::after_three_minutes = Map_event::game_start + WARN_UP_2; // + 2 minutes
    Map_event::last_y = 1;
    Map_event::last_x = 0;
    Map_event::barrage_iterator = 0;
    Map_event::first_barrage = false;
    Map_event::second_barrage = false;
}

        // Warm up 1 time + WARN_UP_1
void    Map_event::check_warm_up() {
    if (0 == Map_event::game_start)
        return;

    if (main_event->multi >= 2 || main_event->arena >= 2) {
        time_t  current = time(0);
        time_t  current_demi_second = clock();

        // Warm up 2 time + WARN_UP_2
        if (current >= Map_event::after_three_minutes && current_demi_second - Map_event::time_last_demi_second >= 111000) {
            if (current == Map_event::after_three_minutes) {
                main_event->soundrender->stopMusic();
                main_event->soundrender->stopSounds();
                main_event->soundrender->playSound("warm_up_2");
            }
            Map_event::time_last_event = current;
            Map_event::time_last_demi_second = current_demi_second;
            // Map_event::add_one_barrage_die_to_map();
            if (Map_event::barrage_x != 11 ||  Map_event::barrage_y != 14)
                Map_event::add_second_barrage_map();
        }
        // Warm up 1 time + WARN_UP_1
        else if (current >= Map_event::after_two_minutes && current_demi_second - Map_event::time_last_demi_second >= 113421) { // 250000
            if (current == Map_event::after_two_minutes)
                main_event->soundrender->playMusic("warm_up_1");
            Map_event::time_last_event = current;
            Map_event::time_last_demi_second = current_demi_second;
            // Map_event::add_one_barrage_to_map();
            if (Map_event::barrage_x != 6 ||  Map_event::barrage_y != 7)
                Map_event::add_first_barrage_map();
        }
    }
}

void    Map_event::add_first_barrage_map() {
    if (Map_event::first_barrage == false) {
        Map_event::first_barrage = true;
        Map_event::barrage_x = 1;
        Map_event::barrage_y = 1;
        barrage_iterator++;
        Map_event::put_barrage_on_slop(Map_event::barrage_y, Map_event::barrage_x);
    }
    else {
        if ((globject::mapX_size - 1 != Map_event::barrage_x + 1 && main_event->map[Map_event::barrage_y][Map_event::barrage_x + 1]->status != WALL_BARRAGE)
        && (main_event->map[Map_event::barrage_y - 1][Map_event::barrage_x]->status == WALL_BARRAGE || 1 == Map_event::barrage_y)) {
            Map_event::barrage_x++;
            Map_event::put_barrage_on_slop(Map_event::barrage_y, Map_event::barrage_x);
        }
        else if ((globject::mapX_size - 1 == Map_event::barrage_x + 1 || main_event->map[Map_event::barrage_y][Map_event::barrage_x + 1]->status == WALL_BARRAGE)
        && (globject::mapY_size - 1 != Map_event::barrage_y + 1 && main_event->map[Map_event::barrage_y + 1][Map_event::barrage_x]->status != WALL_BARRAGE)) {
            Map_event::barrage_y++;
            Map_event::put_barrage_on_slop(Map_event::barrage_y, Map_event::barrage_x);
        }
        else if (0 != Map_event::barrage_x - 1 && main_event->map[Map_event::barrage_y][Map_event::barrage_x - 1]->status != WALL_BARRAGE) {
            Map_event::barrage_x--;
            Map_event::put_barrage_on_slop(Map_event::barrage_y, Map_event::barrage_x);
        }
        else if (0 != Map_event::barrage_y - 1 && main_event->map[Map_event::barrage_y - 1][Map_event::barrage_x]->status != WALL_BARRAGE) {
            Map_event::barrage_y--;
            Map_event::put_barrage_on_slop(Map_event::barrage_y, Map_event::barrage_x);
        }
    }
    barrage_iterator++;

}

void    Map_event::add_second_barrage_map() {
    if (main_event->map[Map_event::barrage_y + 1][Map_event::barrage_x]->status != WALL_BARRAGE
            && main_event->map[Map_event::barrage_y][Map_event::barrage_x - 1]->status == WALL_BARRAGE) {
        Map_event::barrage_y++;
        Map_event::put_barrage_die_on_slop(Map_event::barrage_y, Map_event::barrage_x);
    }
    else if (main_event->map[Map_event::barrage_y + 1][Map_event::barrage_x]->status == WALL_BARRAGE
            && main_event->map[Map_event::barrage_y][Map_event::barrage_x + 1]->status != WALL_BARRAGE) {
        Map_event::barrage_x++;
        Map_event::put_barrage_die_on_slop(Map_event::barrage_y, Map_event::barrage_x);
    }
    else if (main_event->map[Map_event::barrage_y][Map_event::barrage_x + 1]->status == WALL_BARRAGE
            && main_event->map[Map_event::barrage_y - 1][Map_event::barrage_x]->status != WALL_BARRAGE) {
        Map_event::barrage_y--;
        Map_event::put_barrage_die_on_slop(Map_event::barrage_y, Map_event::barrage_x);
    }
    else if (main_event->map[Map_event::barrage_y - 1][Map_event::barrage_x]->status == WALL_BARRAGE
            && main_event->map[Map_event::barrage_y][Map_event::barrage_x - 1]->status != WALL_BARRAGE) {
        Map_event::barrage_x--;
        Map_event::put_barrage_die_on_slop(Map_event::barrage_y, Map_event::barrage_x);
    }
}

        // Warm up 2 time + WARN_UP_2
void    Map_event::put_barrage_on_slop(int y, int x) {
    if (main_event->map[y][x]->type == BOMB) {
        Bomb *tmp = reinterpret_cast<Bomb*>(main_event->map[y][x]);
        tmp->add_bomb_nbr(tmp->creator_id);
    }
    delete main_event->map[y][x];
    main_event->map[y][x] = NULL;
    main_event->map[y][x] = static_cast<Entity*>( Factory::create_wall(WALL_BARRAGE, x, y, WALL_BARRAGE) );
    main_event->map[y][x]->time_creation  = clock();
    Map_event::kill_entity_list(y, x);
}

        // Warm up 2 time + WARN_UP_2
void    Map_event::put_barrage_die_on_slop(int y, int x) {
    if (main_event->map[y][x]->type == BOMB) {
        Bomb *tmp = reinterpret_cast<Bomb*>(main_event->map[y][x]);
        tmp->add_bomb_nbr(tmp->creator_id);
    }
    delete main_event->map[y][x];
    main_event->map[y][x] = NULL;
    main_event->map[y][x] = static_cast<Entity*>( Factory::create_wall(WALL_BARRAGE, x, y, WALL_BARRAGE_DIE) );
    main_event->map[y][x]->time_creation  = clock();
    Map_event::kill_entity_list(y, x);
}

void    Map_event::kill_entity_list(int y, int x) {
    (void)x;
    (void)y;
    // Do kill player, enemy, boss here
    std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
        if ((int)x == (int)((*it)->pos_x)
            && (int)y == (int)((*it)->pos_y)) {
            (*it)->die();
            it = main_event->char_list.begin();
            end = main_event->char_list.end();
        }
        if (it != end)
            it++;
    }
}

        // Warm up 1 time + WARN_UP_1
void    Map_event::debugg_change_timer_lunch_warmup_1() {
    Map_event::last_y = 1;
    Map_event::last_x = 0;
    Map_event::barrage_iterator = 0;
    Map_event::game_start = time(0);
    Map_event::after_two_minutes = Map_event::game_start; // + 2 minutes
    Map_event::after_three_minutes = Map_event::game_start + 6000;
}

        // Warm up 2 time + WARN_UP_2
void    Map_event::debugg_change_timer_lunch_warmup_2() {
    Map_event::last_y = 4;
    Map_event::last_x = 14;
    Map_event::barrage_iterator = 224;
    Map_event::game_start = time(0);
    Map_event::after_two_minutes = Map_event::game_start + 6000; // + 2 minutes
    Map_event::after_three_minutes = Map_event::game_start;
}
