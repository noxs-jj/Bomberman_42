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

class Map_event : public ft42 {
public:
    static time_t  game_start;
    static time_t  after_two_minutes;
    static time_t  after_three_minutes;
    char           in_string[128] = {0};

    Map_event();
    virtual ~Map_event();

    static void     init_clock_at_game_start();

};

#endif
