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

#include <mapparser.class.hpp>
#include <entity.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>

Entity ***      Mapparser::map_from_file( char *map_path ) {
    if (NULL != main_event->map)
        Mapparser::free_old_map();
  Entity ***    tmp = Mapparser::map_alloc();
  Entity *      elem = NULL;
  std::fstream  file;
  std::string   line;
  std::string   casemap;
  int           i = 0,
                j = globject::mapY_size - 1,
                x = 0;

  Mapparser::valid_map(map_path);

  file.open(map_path , std::fstream::in);
  for (int x = 0; x < 3; x++)
    std::getline(file, line);

  while (j >= 0) {
    i = ((globject::mapX_size - 1) * 4 );
    x = globject::mapX_size - 1;
    std::getline(file, line);

    while (i >= 0) {
        casemap += line[i];
        casemap += line[i + 1];
        casemap += line[i + 2];

        elem = Mapparser::get_entity_from_map( casemap, (float)x, (float)j );
        if (elem->type == PLAYER || elem->type == ENEMY || elem->type == BOSS) {
          tmp[j][x] = Factory::create_empty((int)x, (int)j);
          main_event->char_list.push_back(elem);
        }
        else
          tmp[j][x] = elem;

        casemap.clear();
        i -= 4;
        x--;

        if ( i < 0 )
          break;
    }
    j--;
  }

  main_event->w_log("Mapparser::map_from_file LOADED");
  return tmp;
}

Entity *    Mapparser::get_entity_from_map( std::string & casemap, float x, float y) {
  Entity *  tmp = NULL;

  if ( g_mapcase.count(casemap) == 0) {
    main_event->w_error("Map file Case Syntax error/doesn't exist");
    throw std::exception();
  }
  else {
    switch (g_mapcase.at(casemap)) {
        case EMPTY:                 return static_cast<Entity*>( Factory::create_empty(x, y) );
        case WALL_INDESTRUCTIBLE:   return static_cast<Entity*>( Factory::create_wall(WALL_INDESTRUCTIBLE, x, y, WALL_INDESTRUCTIBLE) );
        case WALL_HP_1:             return static_cast<Entity*>( Factory::create_wall(WALL_HP_1, x, y, WALL_HP_1) );
        case WALL_HP_2:             return static_cast<Entity*>( Factory::create_wall(WALL_HP_2, x, y, WALL_HP_2) );
        case WALL_HP_3:             return static_cast<Entity*>( Factory::create_wall(WALL_HP_3, x, y, WALL_HP_3) );
        case WALL_HP_4:             return static_cast<Entity*>( Factory::create_wall(WALL_HP_4, x, y, WALL_HP_4) );
        case ENEMY1:                return static_cast<Entity*>( Factory::create_enemy(ENEMY, x, y, ENEMY1) );
        case ENEMY2:                return static_cast<Entity*>( Factory::create_enemy(ENEMY, x, y, ENEMY2) );
        case ENEMY3:                return static_cast<Entity*>( Factory::create_enemy(ENEMY, x, y, ENEMY3) );
        case ENEMY4:                return static_cast<Entity*>( Factory::create_enemy(ENEMY, x, y, ENEMY4) );
        case ENEMY5:                return static_cast<Entity*>( Factory::create_enemy(ENEMY, x, y, ENEMY5) );
        case BOSS_A:                return static_cast<Entity*>( Factory::create_boss(BOSS, x, y, BOSS_A, BOSS_A) );
        case BOSS_B:                return static_cast<Entity*>( Factory::create_boss(BOSS, x, y, BOSS_B, BOSS_B) );
        case BOSS_C:                return static_cast<Entity*>( Factory::create_boss(BOSS, x, y, BOSS_C, BOSS_C) );
        case BOSS_D:                return static_cast<Entity*>( Factory::create_boss(BOSS, x, y, BOSS_C, BOSS_D) );
        case PLAYER1:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER1) );
        case PLAYER2:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER2) );
        case PLAYER3:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER3) );
        case PLAYER4:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER4) );
        case PLAYER5:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER5) );
        case PLAYER6:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER6) );
        case PLAYER7:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER7) );
        case PLAYER8:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER8) );
        case PLAYER9:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER9) );
        case PLAYER10:               return static_cast<Entity*>( Factory::create_player( PLAYER, x, y, PLAYER10) );
        case BONUS_POWER_UP:        return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_POWER_UP) );
        case BONUS_PLUS_ONE:        return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_PLUS_ONE) );
        case BONUS_KICK:            return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_KICK) );
        case BONUS_CHANGE:          return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_CHANGE) );
        case BONUS_REMOTE_BOMB:     return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_REMOTE_BOMB) );
        case BONUS_SPEED_UP:        return static_cast<Entity*>( Factory::create_player( BONUS, x, y, BONUS_SPEED_UP) );
        default:                    return static_cast<Entity*>( Factory::create_empty(x, y) );
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
        main_event->w_error("Mapparser::valid_map file access error");
        throw std::exception();
    }
    file.open(map_path , std::fstream::in);
    if (!file.is_open()) {
        main_event->w_error("Mapparser::valid_map file open error");
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
        if ((int)line.length() != (4 * x - 1) ) {
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

// TO DELETE SI SEGFAULT
    // if (main_event->map != NULL) {
    //     while (y < globject::mapY_size) {
    //         std::free(main_event->map[y]);
    //         main_event->map[y] = NULL;
    //         y++;
    //     }
    //     std::free(main_event->map);
    //     main_event->map = NULL;
    // }
/////////////////////

    new_map = (Entity ***)std::malloc(sizeof(Entity **) * globject::mapY_size);
    if (new_map == NULL) {
        main_event->w_error("Mapparser::map_alloc() new_map Allocation error");
        throw std::exception();
    }
    y = 0;
    while (y < globject::mapY_size) {
        new_map[y] = NULL;
        new_map[y] = (Entity **)std::malloc(sizeof(Entity *) * globject::mapX_size);
        if (new_map[y] == NULL) {
            main_event->w_error("Mapparser::map_alloc() new_map[y] Allocation error");
            throw std::exception();
        }
        y++;
    }

  return new_map;
}

void        Mapparser::free_old_map() {
    int y = 0;

    while (y < globject::mapY_size) {
        if (NULL != main_event->map[y])
            std::free( main_event->map[y]);
        y++;
    }
    if (NULL != main_event->map)
        std::free(main_event->map);
    main_event->map = NULL;
}

void         Mapparser::get_error() const {
  if (NULL != Mapparser::error)
    std::cerr << Mapparser::error;
}

std::string * Mapparser::error = NULL;

Mapparser::Mapparser() {}

Mapparser::~Mapparser() {}

Mapparser::Mapparser( Mapparser const & src ) {
    *this = src;
}

Mapparser & Mapparser::operator=( Mapparser const & rhs ) {
    if (this != &rhs) {
        this->error = rhs.error;
    }
    return *this;
}
