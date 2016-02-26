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

#ifndef MAP_EVENT_CLASS_HPP
# define MAP_EVENT_CLASS_HPP

# include <ft42.class.hpp>

# define WARM_UP_1 60
# define WARN_UP_2 120

class Map_event : public ft42 {
public:
    static time_t   game_start;
    static time_t   after_two_minutes;
    static time_t   after_three_minutes;
    static time_t   time_last_event;
    static int      last_y;
    static int      last_x;
    static int      barrage_iterator;
    static clock_t  time_last_demi_second;
    char            in_string[128] = {0};

    Map_event();
    virtual ~Map_event();

    static void     init_clock_at_game_start();
    static void     check_warm_up();
    static void     add_one_barrage_to_map();
    static void     add_one_barrage_die_to_map();
    static void     put_barrage_on_slop(int y, int x);
    static void     put_barrage_die_on_slop(int y, int x);
    static void     debugg_change_timer_lunch_warmup_1();
    static void     debugg_change_timer_lunch_warmup_2();
    static void     kill_entity_list(int y, int x);

};

#endif
