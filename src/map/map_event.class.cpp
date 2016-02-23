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

time_t Map_event::game_start = 0;
time_t Map_event::after_two_minutes = 0;
time_t Map_event::after_three_minutes = 0;

Map_event::Map_event() {}

Map_event::~Map_event() {}

void    Map_event::init_clock_at_game_start() {
    Map_event::game_start = time(&Map_event::game_start);
    Map_event::after_two_minutes = Map_event::game_start; // + 2 minutes
    Map_event::after_three_minutes = Map_event::game_start; // + 3 minutes

    std::cout << "Map_event::game_start " << ctime(&Map_event::game_start) << std::endl;
    std::cout << "(CLOCKS_PER_SEC / 2) = " << (CLOCKS_PER_SEC / 2) << std::endl;
}





/*
#include <iostream>
#include <ctime>

using namespace std;

int main( )
{
   // current date/time based on current system
time_t now = time(0);

 // convert now to string form
char* dt = ctime(&now);

cout << "The local date and time is: " << dt << endl;

// convert now to tm struct for UTC
tm *gmtm = gmtime(&now);
dt = asctime(gmtm);
cout << "The UTC date and time is:"<< dt << endl;
*/
