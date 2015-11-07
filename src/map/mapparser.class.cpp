/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 13:27:58 by jmoiroux          #+#    #+#             */
/*   Updated: 2015/11/07 13:45:33 by jmoiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mapparser.class.hpp>
# include <entity.class.hpp>

Entity ***  Mapparser::map_alloc() {
  int         y = 0,
              x = 0;
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
    x = 0;
    while (x < MAP_X_SIZE) {
      if (new_map[y][x] == NULL) {
        this->w_error("Mapparser::map_alloc() new_map[y][x] Allocation error");
        throw std::exception();
      }
      x++;
    }
    y++;
  }

  return new_map;
}


Mapparser::Mapparser() {}

Mapparser::~Mapparser() {}
