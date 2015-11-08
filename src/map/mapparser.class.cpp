/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 13:27:58 by jmoiroux          #+#    #+#             */
/*   Updated: 2015/11/07 20:09:21 by jmoiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mapparser.class.hpp>
#include <entity.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>

Entity ***      Mapparser::map_from_file( char *map_path ) {
  Entity ***    tmp = Mapparser::map_alloc();
  std::fstream  file;
  std::string   line;
  std::string   casemap;
  int           i = 0,
                j = 0,
                x = 0;

  Mapparser::valid_map(map_path);

  file.open(map_path , std::fstream::in);
  for (int x = 0; x < 3; x++)
    std::getline(file, line);

  while (j < MAP_Y_SIZE) {
    i = 0;
    x = 0;
    std::getline(file, line);
    // std::cout << line << std::endl;

    while (i < (MAP_X_SIZE * 4 - 1) ) {
      casemap += line[i];
      casemap += line[i + 1];
      casemap += line[i + 2];

      tmp[j][x] = Mapparser::get_entity_from_map( casemap, (float)x, (float)j );

      std::cout << casemap;
      casemap.clear();
      i += 4;
      x++;

      if ( i >= (int)line.length() )
        break;
    }
    std::cout << std::endl;
    j++;
  }

  std::cout << "Mapparser::map_from_file LOADED" << std::endl;
  return tmp;
}


Entity *    Mapparser::get_entity_from_map( std::string & casemap, float x, float y) {
  Entity *  tmp = NULL;

  if ( g_mapcase.count(casemap) == 0) {
    main_event->w_full("Map file Case Syntax error/doesn't exist");
    throw std::exception();
  }
  else {
    switch (g_mapcase.at(casemap)) {
      case EMPTY:                 return static_cast<Entity*>( main_event->create_empty(x, y) );
      case WALL_INDESTRUCTIBLE:   return static_cast<Entity*>( main_event->create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_INDESTRUCTIBLE) );
      case WALL_HP_1:             return static_cast<Entity*>( main_event->create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_HP_1) );
      case WALL_HP_2:             return static_cast<Entity*>( main_event->create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_HP_2) );
      case WALL_HP_3:             return static_cast<Entity*>( main_event->create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_HP_3) );
      case WALL_HP_4:             return static_cast<Entity*>( main_event->create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_HP_4) );
      case ENEMY1:                return static_cast<Entity*>( main_event->create_enemy(ENEMY, x, y, ENEMY1) );
      case ENEMY2:                return static_cast<Entity*>( main_event->create_enemy(ENEMY, x, y, ENEMY2) );
      case ENEMY3:                return static_cast<Entity*>( main_event->create_enemy(ENEMY, x, y, ENEMY3) );
      case ENEMY4:                return static_cast<Entity*>( main_event->create_enemy(ENEMY, x, y, ENEMY4) );
      case BOSS_A:                return static_cast<Entity*>( main_event->create_boss(BOSS, x, y, BOSS_A, BOSS_A) );
      case BOSS_B:                return static_cast<Entity*>( main_event->create_boss(BOSS, x, y, BOSS_B, BOSS_B) );
      case BOSS_C:                return static_cast<Entity*>( main_event->create_boss(BOSS, x, y, BOSS_C, BOSS_C) );
      case PLAYER1:               return static_cast<Entity*>( main_event->create_player( PLAYER, x, y, PLAYER1) );
      case PLAYER2:               return static_cast<Entity*>( main_event->create_player( PLAYER, x, y, PLAYER2) );
      case PLAYER3:               return static_cast<Entity*>( main_event->create_player( PLAYER, x, y, PLAYER3) );
      case PLAYER4:               return static_cast<Entity*>( main_event->create_player( PLAYER, x, y, PLAYER4) );
      default:                    return static_cast<Entity*>( main_event->create_empty(x, y) );
    }
  }

  return tmp;
}


int         Mapparser::valid_map( char const *map_path ) {
  std::fstream  file;
  std::string   line;
  int           x = 0,
                y = 0,
                j = 0;

  if( access( map_path, F_OK ) < 0 ) {
    main_event->w_full("Mapparser::valid_map file access error");
    throw std::exception();
  }
  file.open(map_path , std::fstream::in);
  if (!file.is_open()) {
    main_event->w_full("Mapparser::valid_map file open error");
    throw std::exception();
  }
  std::getline(file, line); // y: 20
  if (line.length() >= 4)
    x = std::stoi(&line[3]);
  else
    main_event->w_exception("map line 1 error");
  std::getline(file, line); // x: 20
  if (line.length() >= 4)
    y = std::stoi(&line[3]);
  else
    main_event->w_exception("map line 2 error");
  std::getline(file, line); // <-- MAP -->

  j = 0;
  while ( std::getline(file, line) ) {
    // std::cout << line << std::endl;
    if ((int)line.length() != (4 * x - 1) ) {
      std::cout << "Mapline " << j + 4 << " error" << std::endl;
      std::cout << line << std::endl;
      main_event->w_exception("width doesn't correspond");
    }
    if (j >= y - 1)
      break;
    j++;

  }
  if (j != y - 1)
    main_event->w_exception("Map height doesn't correspond");
  file.close();
  return 0;
}

Entity ***  Mapparser::map_alloc() { // return map 2d without entity
  int         y = 0;
  Entity ***  new_map = NULL;

  new_map = (Entity ***)std::malloc(sizeof(Entity **) * MAP_Y_SIZE);
  if (new_map == NULL) {
    main_event->w_error("Mapparser::map_alloc() new_map Allocation error");
    throw std::exception();
  }
  while (y < MAP_Y_SIZE) {
    new_map[y] = NULL;
    new_map[y] = (Entity **)std::malloc(sizeof(Entity *) * MAP_X_SIZE);
    if (new_map[y] == NULL) {
      main_event->w_error("Mapparser::map_alloc() new_map[y] Allocation error");
      throw std::exception();
    }
    y++;
  }

  return new_map;
}

void         Mapparser::get_error() const {
  if (NULL != Mapparser::error)
    std::cerr << Mapparser::error;
}

std::string * Mapparser::error = NULL;

Mapparser::Mapparser() {}

Mapparser::~Mapparser() {}
