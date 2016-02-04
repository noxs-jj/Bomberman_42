/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.class.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/04 17:43:39 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ia.class.hpp>

Ia::Ia( ) : layer(1) {
}

Ia::Ia( int layer ) : layer(layer) {
}

Ia::Ia( Ia const & src ) {
  (void)src;
  //(*this).layer = (*src).layer - 1;
}

Ia & Ia::operator=( Ia const & rhs ) {
    if (this != &rhs) {}
    return (*this);
}

Ia::~Ia( void ) {
    // delete this->soundrender;
}

int heuristic(std::vector<int> line) {
  int score = 0;

  for (
    std::vector<int>::iterator it = line.begin();
    it != line.end();
    ++it
  ) {
    if (*it == PLAYER || *it == BOMB) {
      if (*it == BOMB) {
        return (score - 60);
      }
      else {
        return (score - 50);
      }
    }
    score += 1;
  }
  return (score);
}

#ifdef KAMIKAZE
int    Ia::must_move_to( Entity *it ) {
  int  paths [4][2] = {
    {heuristic((*it).pretest_moves(DIR_UP)), DIR_UP},
    {heuristic((*it).pretest_moves(DIR_BOTTOM)), DIR_BOTTOM},
    {heuristic((*it).pretest_moves(DIR_LEFT)), DIR_LEFT},
    {heuristic((*it).pretest_moves(DIR_RIGHT)), DIR_RIGHT},
  };
  int  max [2] = {paths[0][0], 0};
  int  min [2] = {paths[0][0], 0};
  for ( int n=0 ; n<4 ; ++n ) {
    if (max[0] < paths[n][0]) {
      max[0] = paths[n][0];
      max[1] = n;
    }
    if (min[0] > paths[n][0]) {
      min[0] = paths[n][0];
      min[1] = n;
    }
  }
  if (min[0] <= 0 || ((*it).pretest_move((*it).dir) != EMPTY)) {
    return (DIR_UP + max[1]);
  }
  else {
    (*it).put_bomb (
      BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
      (*it).bomb_model, (*it).blast_radius,
      (*it).id
    );
    return ((*it).dir);
  }
}
#else
int    Ia::must_move_to( Entity *it ) {
  int  paths [4][2] = {
    {heuristic((*it).pretest_moves(DIR_UP)), DIR_UP},
    {heuristic((*it).pretest_moves(DIR_BOTTOM)), DIR_BOTTOM},
    {heuristic((*it).pretest_moves(DIR_LEFT)), DIR_LEFT},
    {heuristic((*it).pretest_moves(DIR_RIGHT)), DIR_RIGHT},
  };
  int  max [2] = {paths[0][0], 0};
  int  min [2] = {paths[0][0], 0};
  for ( int n=0 ; n<4 ; ++n ) {
    if (max[0] < paths[n][0]) {
      max[0] = paths[n][0];
      max[1] = n;
    }
    if (min[0] > paths[n][0]) {
      min[0] = paths[n][0];
      min[1] = n;
    }
  }
  if (min[0] <= 0 || ((*it).pretest_move((*it).dir) != EMPTY)) {
    return (DIR_UP + max[1]);
  }
  else {
    return ((*it).dir);
  }
}
#endif

bool    Ia::play_enemy(Enemy *it) {
  if ((*it).dir == ((*it).dir = Ia::must_move_to(static_cast<Entity*>(it)))) {
    if ((*it).memory > 400) {
      if (!(*it).friend_zone((*it).pos_x, (*it).pos_y)) {
        (*it).put_bomb (
          BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
          (*it).bomb_model, (*it).blast_radius,
          (*it).id
        );
      }
    }
    if ((*it).memory < 410) {
      (*it).memory += 1;
    }
    else {
      (*it).memory = 0;
    }
  }
  (*it).move((*it).dir);
  return (true);
}

bool    Ia::play_boss(Boss *it, int time) {
  std::list<Entity *>::iterator heros = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();

  (void)time;
  while (heros != end) {
    if ((*heros)->type == PLAYER) {
      if ((*it).dir == ((*it).dir = Ia::must_move_to(
        static_cast<Entity*>(it)
      ))) {
        if (time % 50 == 1) {
          main_event->char_list.push_back(main_event->create_enemy (
            ENEMY,
            (*heros)->pos_x,
            (*heros)->pos_y,
            ENEMY1
          ));
          /*ENEMY, (*heros)->pos_x, (*heros)->pos_y,
          ENEMY, (*heros)->blast_radius*/
        }
      }
      (*it).move((*it).dir);
    }
    heros++;
  }
  return (false);
}

void     Ia::start(int time) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();

  (void)time;
  while (it != end) {
    if ((*it)->type == ENEMY) {
      Ia::play_enemy(static_cast<Enemy*>(*it));
    }
    else if ((*it)->type == BOSS) {
      Ia::play_boss(static_cast<Boss*>(*it), time);
    }
    it++;
  }
}
