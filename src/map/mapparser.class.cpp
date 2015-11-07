/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 13:27:58 by jmoiroux          #+#    #+#             */
/*   Updated: 2015/11/07 16:56:28 by jmoiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mapparser.class.hpp>
# include <entity.class.hpp>

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
    this->w_error("Mapparser::map_alloc() new_map Allocation error");
    throw std::exception();
  }
  while (y < MAP_Y_SIZE) {
    new_map[y] = NULL;
    new_map[y] = (Entity **)std::malloc(sizeof(Entity *) * MAP_X_SIZE);
    if (new_map[y] == NULL) {
      this->w_error("Mapparser::map_alloc() new_map[y] Allocation error");
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
