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

#include <ia.class.hpp>

Ia::Ia( ) : layer(1) {}

Ia::Ia( int layer ) : layer(layer) {}

Ia::Ia( Ia const & src ) {
  *this = src;
}

Ia & Ia::operator=( Ia const & rhs ) {
    if (this != &rhs) {
        this->layer = rhs.layer;
        this->direction = rhs.direction;
    }
    return (*this);
}

Ia::~Ia( void ) {}

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

int    Ia::must_move_to( Entity *it ) {
    int paths [4][2] = {
        {heuristic((*it).pretest_moves(DIR_UP)), DIR_UP},
        {heuristic((*it).pretest_moves(DIR_BOTTOM)), DIR_BOTTOM},
        {heuristic((*it).pretest_moves(DIR_LEFT)), DIR_LEFT},
        {heuristic((*it).pretest_moves(DIR_RIGHT)), DIR_RIGHT},
    };
    int max [2] = {paths[0][0], 0};
    int min [2] = {paths[0][0], 0};

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
    //KAMIKAZE On
    if (true == main_event->option_ia_kamikaze) {
        if (min[0] <= 0 || ((*it).pretest_move((*it).dir) != EMPTY)) {
            return (DIR_UP + max[1]);
        }
        else {
            main_event->ia_bomb ((*it).id);
            return ((*it).dir);
        }
    }
    //KAMIKAZE OFF
    else {
        if (min[0] <= 0 || ((*it).pretest_move((*it).dir) != EMPTY)) {
            return (DIR_UP + max[1]);
        }
        else {
            return ((*it).dir);
        }
    }
}

bool    Ia::play_enemy(Enemy *it) {
  int move = (*it).dir = Ia::must_move_to(static_cast<Entity*>(it));

  if (move != DIR_LEFT && move != DIR_RIGHT) {
    (*it).pos_x = trunc((*it).pos_x) + 0.5f;
  }
  else {
    (*it).pos_y = trunc((*it).pos_y) + 0.5f;
  }
  if ((*it).dir == move) {
    if ((*it).memory > 400) {
      if (!(*it).friend_zone((*it).pos_x, (*it).pos_y)) {
        main_event->ia_bomb ((*it).id);
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
      if ((*it).dir == ((*it).dir = Ia::must_move_to (
        static_cast<Entity*>(it)
      ))) {
        if (time % 50 == 1) {
          int move = (*it).dir = Ia::must_move_to(static_cast<Entity*>(it));

          if (move != DIR_LEFT && move != DIR_RIGHT) {
            (*it).pos_x = trunc((*it).pos_x) + 0.5f;
          }
          else {
            (*it).pos_y = trunc((*it).pos_y) + 0.5f;
          }
          main_event->char_list.push_back(Factory::create_enemy (
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
  size_t 	entity_nbr = main_event->char_list.size();

  (void)time;
  while (it != end) {
	// arena 5 : le jeu plante quand l'ia tue le joueur en haut a gauche
	if (entity_nbr != main_event->char_list.size()) // segv quand ia meurt
		return ;
    if ((*it)->type == ENEMY) {
      Ia::play_enemy(static_cast<Enemy*>(*it));
    }
    else if ((*it)->type == BOSS) {
      Ia::play_boss(static_cast<Boss*>(*it), time);
    }
    it++;
  }
}
