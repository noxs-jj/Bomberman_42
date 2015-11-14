/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 13:27:34 by jmoiroux          #+#    #+#             */
/*   Updated: 2015/11/07 20:05:03 by jmoiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
  {"3#a", BOSS_A},
  {"3#b", BOSS_B},
  {"3#c", BOSS_C},
  {"3#c", BOSS_C},
  {"4#1", PLAYER1},
  {"4#2", PLAYER2},
  {"4#3", PLAYER3},
  {"4#4", PLAYER4}

};

class Entity;

class Mapparser : public ft42 {
public:
  static std::string *  error;

  Mapparser();
  virtual ~Mapparser();

  void        get_error() const ;
  static int  valid_map( char const *map_path ) ;

  static Entity ***  map_from_file( char *map_path );
  static Entity ***  map_alloc();
  static Entity *    get_entity_from_map( std::string & casemap, float x, float y);

};

#endif