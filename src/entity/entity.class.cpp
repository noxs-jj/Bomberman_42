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

#include <entity.class.hpp>
#include <main.hpp>
#include <bomb.class.hpp>
#include <bonus.class.hpp>
#include <globject.class.hpp>
#include <save.class.hpp>

#include <iostream>
#include <vector>

int		Entity::autoincrement = 5;

Entity::Entity(void) {}

Entity::~Entity( void ) {}

Entity::Entity( int type, float x, float y, int status, int model ) : type(type), pos_x(x),
															pos_y(y), status(status), zoom_m(1) {
	if (type == PLAYER)
		this->id = model - PLAYER1;
	else {
		Entity::autoincrement++;
		this->id = Entity::autoincrement;
	}
	// this->remote_lst.clear();
}

Entity::Entity( Entity const & src ) {
    *this = src;
}
Entity & Entity::operator=( Entity const & rhs ) {
    if (this != &rhs) {
        this->remote_lst = rhs.remote_lst;
        this->type = rhs.type;
        this->id = rhs.id;
        this->model = rhs.model;
        this->pos_x = rhs.pos_x;
        this->pos_y = rhs.pos_y;
        this->dir = rhs.dir;
        this->status = rhs.status;
        this->frame = rhs.frame;
        this->speed = rhs.speed;
        this->blast_radius = rhs.blast_radius;
        this->zoom_m = rhs.zoom_m;
        this->bomb_nbr = rhs.bomb_nbr;
        this->kick_bomb = rhs.kick_bomb;
        this->bomb_model = rhs.bomb_model;
        this->remote = rhs.remote;
        this->remote_nbr = rhs.remote_nbr;
        this->autoincrement = rhs.autoincrement;
    }
    return *this;
}

int		Entity::check_move( float x, float y ) {
  if (main_event->map[(int)y][(int)x] == NULL)
      return EMPTY;
	if (main_event->map[(int)y][(int)x]->type == EMPTY)
		return EMPTY;
	else if (main_event->map[(int)y][(int)x]->type == BOMB
			&& !((int)this->pos_y == (int)y && (int)this->pos_x == (int)x))
		return BOMB;
	else if (main_event->map[(int)y][(int)x]->type == BOMB
			&& ((int)this->pos_y == (int)y && (int)this->pos_x == (int)x))
		return EMPTY;
	else if (main_event->map[(int)y][(int)x]->type == FIRE)
		return FIRE;
	else if (main_event->map[(int)y][(int)x]->type == BONUS)
		return BONUS;
	return WALL;
}

bool Entity::friend_zone( float x, float y ) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((int)x -3 < (int)((*it)->pos_x)
		&&  (int)y -3 < (int)((*it)->pos_y)
		&&  (int)((*it)->pos_x) < (int)x +3
		&&  (int)((*it)->pos_y) < (int)y +3
		) {
	    if ((*it)->type == PLAYER) {
				return (false);
			}
			else if ((*it)->type == ENEMY
			||  (*it)->type == ENEMY) {
				return (true);
			}
		}
    it++;
  }
	return (false);
}

bool Entity::position_is_player( float x, float y ) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
    if ((*it)->type == PLAYER) {
      if ((int)x == (int)((*it)->pos_x)
			&&  (int)y == (int)((*it)->pos_y)) {
				return (true);
			}
    }
    it++;
  }
	return (false);
}

std::vector<int>	Entity::pretest_moves( int dir ) {
	std::vector<int> line;
	float	x; //this->pos_x;
	float	y; //this->pos_y;
	int pre_move = 0;

	x = y = 0;
	while (42) {
		if (dir == DIR_UP)
			y += -0.08f * 3;
		else if (dir == DIR_BOTTOM)
			y += 0.08f * 3;
		else if (dir == DIR_LEFT)
			x += -0.08f * 3;
		else if (dir == DIR_RIGHT)
			x += 0.08f * 3;
		pre_move = check_move (
			(x + this->pos_x),
			(y + this->pos_y)
		);
		if (pre_move == EMPTY) {
			if (Entity::position_is_player (
				(x + this->pos_x),
				(y + this->pos_y)
			)) {
				pre_move = PLAYER;
			}
		}
		line.push_back(pre_move);
		if (pre_move != EMPTY) {
			break ;
		}
	}
	return (line);
}

int	Entity::pretest_move( int dir ) {
	float	x = 0;//this->pos_x;
	float	y = 0;//this->pos_y;

	if (dir == DIR_UP)
		y += -0.08f;
	else if (dir == DIR_BOTTOM)
		y += 0.08f;
	else if (dir == DIR_LEFT)
		x += -0.08f;
	else if (dir == DIR_RIGHT)
		x += 0.08f;
	return (check_move(x * 4 + this->pos_x, y * 4 + this->pos_y));
}

void	Entity::move( int dir ) {
	float	x = 0;//this->pos_x;
	float	y = 0;//this->pos_y;
	int		ret = EMPTY;
	int		tmp_x = this->pos_x, tmp_y = this->pos_y;

	frame += 0.3;
	if (dir == DIR_UP)
		y += -0.08f;
	else if (dir == DIR_BOTTOM)
		y += 0.08f;
	else if (dir == DIR_LEFT)
		x += -0.08f;
	else if (dir == DIR_RIGHT)
		x += 0.08f;
	else
		frame = 0;
	if (check_coord_exist(x * 4 + this->pos_x, y * 4 + this->pos_y) == false)
		return ;
	ret = check_move(x * 4 + this->pos_x, y * 4 + this->pos_y);
	if (ret == WALL || check_move(x + this->pos_x, y + this->pos_y) == WALL)
		return;
	if (ret == EMPTY || ret == BONUS) {
		this->dir = dir;
		this->pos_x = x + this->pos_x;
		this->pos_y = y + this->pos_y;
		if (ret == BONUS) {
			static_cast<Bonus*>(main_event->map[(int)this->pos_y][(int)this->pos_x])->affect(this);
			if (main_event->map[(int)this->pos_y][(int)this->pos_x]->type == BONUS) {
				delete main_event->map[(int)this->pos_y][(int)this->pos_x];
                main_event->map[(int)this->pos_y][(int)this->pos_x] = NULL;
				main_event->map[(int)this->pos_y][(int)this->pos_x] = Factory::create_empty((int)this->pos_x, (int)this->pos_y);
			}
		}
		// change frame here
	}
	else if (ret == FIRE) {
		take_damage();
	}
	else if (ret == BOMB) {
		if (dir == DIR_UP)
			tmp_y--;
		else if (dir == DIR_BOTTOM)
			tmp_y++;
		else if (dir == DIR_LEFT)
			tmp_x--;
		else if (dir == DIR_RIGHT)
			tmp_x++;
		if (this->kick_bomb == true && static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->creator_id == this->id){
			static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->pushed = true;
            if (true == this->kick_bomb)
			    main_event->soundrender->playSound("kick");
			static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->pushed_dir = dir;
		}
	}
	if (frame >= 4)
		frame = 0;
}

void Entity::destroy_bomb_list() {
	// main_event->remote_detonate(this->model);
}

void	Entity::take_damage( void ) {
	main_event->live_player[this->model - PLAYER1] = false;
	die();
}

int		Entity::count_entity(int type) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	int i = 0;
	while (it != end) {
		if ((*it)->type == type)
			i++;
		it++;
	}
	return i;
}

void	Entity::die( void ) {
	main_event->soundrender->playSound("die");
	if (this->type == PLAYER && main_event->multi > 0 && count_entity(PLAYER) == 2) {
		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
                delete *it;
				main_event->char_list.erase(it); // delete this ?
                // std::cout << "fuite 4" << std::endl;
				main_event->to_die_entity = true;
				it = main_event->char_list.begin();
				end = main_event->char_list.end();
			}
			else if ((*it)->type == PLAYER) {
				main_event->draw_winner_multi = (*it)->model - PLAYER;
				it++;
			}
			else
				it++;
		}
		main_event->game_ended = 150;
	}
	else if (this->type == PLAYER && count_entity(PLAYER) == 1) { // loose
		if (main_event->coop == true || (main_event->multi <= 0 && main_event->arena <= 0))
			globject::spin(this->pos_x, this->pos_y);
		main_event->game_ended = 150;

		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
                delete *it;
				main_event->char_list.erase(it); // delete this ?
                // std::cout << "fuite 2" << std::endl;
				main_event->to_die_entity = true;
				it = main_event->char_list.begin();
			}
			else
				it++;
		}
		main_event->draw_lose_campaign = 1;
		main_event->game_ended = 150;

	}
	else {
		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
                delete *it;
				main_event->char_list.erase(it); // delete this ?
                // std::cout << "fuite 3" << std::endl;
				main_event->to_die_entity = true;
				it = main_event->char_list.begin();
			}
			else
				it++;
		}
	}
	if (main_event->multi == 0 && main_event->arena == 0
		&& count_entity(ENEMY) == 0 && count_entity(BOSS) == 0) { // campaign win
			main_event->game_ended = 150;

			if (main_event->actual_level == MAX_LEVEL) {
				main_event->draw_end_campaign = 1;
			}
			else
				main_event->draw_winner_campaign = 1;
		}
		else if (main_event->arena != 0 && count_entity(ENEMY) == 0 && count_entity(BOSS) == 0) {
			main_event->game_ended = 150;
			main_event->draw_end_campaign = 1;
		}
		else if (main_event->arena != 0 && count_entity(PLAYER) == 0) {
			main_event->game_ended = 150;
			main_event->draw_lose_campaign = 1;
		}
}

void	Entity::put_bomb(int status, float x, float y, int model, int blast, int id) {
	delete main_event->map[(int)y][(int)x];
    main_event->map[(int)y][(int)x] = NULL;
	main_event->map[(int)y][(int)x] = Factory::create_empty((int)x, (int)y);
	main_event->map[(int)y][(int)x] = Factory::create_bomb(status, (int)x + 0.5, (int)y + 0.5, model, id);
	main_event->map[(int)y][(int)x]->blast_radius = blast;
	if (model != BOMB_REMOTE && PLAYER == this->type) {
		main_event->soundrender->playSound("bombmove");
	}
}
