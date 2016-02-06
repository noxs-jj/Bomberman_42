#include <entity.class.hpp>
#include <main.hpp>
#include <bomb.class.hpp>
#include <bonus.class.hpp>
#include <globject.class.hpp>

#include <iostream>
#include <vector>

int		Entity::autoincrement = 0;


Entity::Entity(void)
{

}

Entity::~Entity( void ) {}

Entity::Entity( int type, float x, float y, int status ) : type(type), pos_x(x),
															pos_y(y), status(status), zoom_m(1) {
	Entity::autoincrement++;
	this->id = Entity::autoincrement;
	this->remote_lst.clear();
}

int		Entity::check_move( float x, float y ) {
	if (main_event->map[(int)y][(int)x]->type == WALL)
		return WALL;
	else if (main_event->map[(int)y][(int)x]->type == BOMB
			&& !((int)this->pos_y == (int)y && (int)this->pos_x == (int)x))
		return BOMB;
	else if (main_event->map[(int)y][(int)x]->type == FIRE)
		return FIRE;
	else if (main_event->map[(int)y][(int)x]->type == BONUS)
		return BONUS;
	return EMPTY;
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
	return (check_move(x * 3 + this->pos_x, y + this->pos_y));
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
	ret = check_move(x * 3 + this->pos_x, y + this->pos_y);
	if (ret == EMPTY || ret == BONUS) {
		this->dir = dir;
		this->pos_x = x + this->pos_x;
		this->pos_y = y + this->pos_y;
		if (ret == BONUS)
		{
			static_cast<Bonus*>(main_event->map[(int)this->pos_y][(int)this->pos_x])->affect(this);
			delete main_event->map[(int)this->pos_y][(int)this->pos_x];
			main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
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
		// std::cout << "bomb detected kick =" << this->kick_bomb << " id= " << this->id << " bomb_id= " << static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->creator_id << std::endl;
		if (this->kick_bomb == true && static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->creator_id == this->id){
			static_cast<Bomb*>(main_event->map[(int)tmp_y][(int)tmp_x])->pushed = true;
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
	// dec health
	// if health <= 0
	// destroy_bomb_list();
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
	std::cout << "Someone died " << std::endl;
	std::cout << "count_entity" << count_entity(PLAYER) << std::endl;
	main_event->soundrender->playSound("die");
	if (this->type == PLAYER && main_event->multi > 0 && count_entity(PLAYER) == 2) {
		std::cout << "Someone died 01 " << std::endl;
		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
				main_event->char_list.erase(it); // delete this ?
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
		main_event->game_pause = true;
		main_event->mode_menu = true; // desactive menu render
	}
	else if (this->type == PLAYER && count_entity(PLAYER) == 1) { // loose
		std::cout << "Someone died 02 " << std::endl;
		globject::spin(this->pos_x, this->pos_y);
		main_event->mode_menu = true; // desactive menu render
		main_event->game_pause = true;
		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
				main_event->char_list.erase(it); // delete this ?
				main_event->to_die_entity = true;
				it = main_event->char_list.begin();
			}
			else
				it++;
		}
		globject::reinit_level(0);
		main_event->draw_lose_campaign = 1;
		main_event->game_pause = true;
		main_event->mode_menu = true; // desactive menu render

	}
	else {
		std::cout << "Someone died 03 " << std::endl;
		std::list<Entity *>::iterator it = main_event->char_list.begin();
		std::list<Entity *>::iterator end = main_event->char_list.end();
		while (it != end) {
			if (this->id == (*it)->id) {
				main_event->char_list.erase(it); // delete this ?
				main_event->to_die_entity = true;
				it = main_event->char_list.begin();
			}
			else
				it++;
				// main_event->to_die_entity = true;
		}
	}
	std::cout << "Someone died 10 " << std::endl;
	if (main_event->multi == 0 && main_event->arena == 0
		&& count_entity(ENEMY) == 0 && count_entity(BOSS) == 0) { // campaign win
			std::cout << "Someone died 10.1 " << std::endl;
			main_event->game_pause = true;
			main_event->mode_menu = true; // desactive menu render
			if (main_event->actual_level == MAX_LEVEL) {
				main_event->actual_level = 1;
				main_event->draw_end_campaign = 1;
			}
			else
				main_event->draw_winner_campaign = 1;
		}
		std::cout << "Someone died end " << std::endl;
}

void	Entity::put_bomb(int status, float x, float y, int model, int blast, int id) {
	delete main_event->map[(int)y][(int)x];
	// main_event->map[(int)y][(int)x] = main_event->create_empty((int)x, (int)y);
	main_event->map[(int)y][(int)x] = main_event->create_bomb(status, (int)x + 0.5, (int)y + 0.5, model, id);
	main_event->map[(int)y][(int)x]->blast_radius = blast;
	if (model != BOMB_REMOTE)
	{
		main_event->soundrender->playSound("bombmove");
	}
}
