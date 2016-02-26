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

#ifndef MAPPARSER_CLASS_HPP
# define MAPPARSER_CLASS_HPP

# include <ft42.class.hpp>

static std::map<std::string, int> const g_mapcase = {

    {"   ", EMPTY},
    {"1##", WALL_INDESTRUCTIBLE},
    {"1#1", WALL_HP_1},
    {"1#2", WALL_HP_2},
    {"1#3", WALL_HP_3},
    {"1#4", WALL_HP_4},
    {"2#1", ENEMY1},
    {"2#2", ENEMY2},
    {"2#3", ENEMY3},
    {"2#4", ENEMY4},
    {"2#5", ENEMY5},
    {"3#a", BOSS_A},
    {"3#b", BOSS_B},
    {"3#c", BOSS_C},
    {"3#c", BOSS_C},
    {"3#d", BOSS_D},
    {"4#1", PLAYER1},
    {"4#2", PLAYER2},
    {"4#3", PLAYER3},
    {"4#4", PLAYER4},
    {"4#5", PLAYER5},
    {"5#1", BONUS_POWER_UP},
    {"5#2", BONUS_PLUS_ONE},
    {"5#3", BONUS_KICK},
    {"5#4", BONUS_CHANGE},
    {"5#5", BONUS_REMOTE_BOMB},
    {"5#6", BONUS_SPEED_UP},
};

class Entity;

class Mapparser : public ft42 {
public:
    static std::string *    error;

    Mapparser();
    Mapparser( Mapparser const & src );
    Mapparser & operator=( Mapparser const & rhs );
    virtual ~Mapparser();

    void                get_error() const ;
    static int          valid_map( char const *map_path ) ;

    static Entity ***   map_from_file( char *map_path );
    static Entity ***   map_alloc();
    static Entity *     get_entity_from_map( std::string & casemap, float x, float y);
    static void         free_old_map();

};

#endif
