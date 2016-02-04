/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/04 18:28:44 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bomb.class.hpp>
#include <fire.class.hpp>
#include <bonus.class.hpp>
#include <soundrender.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( float x, float y, int status, int model, int id ) : Entity( BOMB, x, y, status ) {
	this->model = model;
	this->creator_id = id;
	this->timer = 180;
}

void	Bomb::damage_entity(int x, int y ) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((int)(*it)->pos_x == (int)x && (int)(*it)->pos_y == (int)y
			&& ((*it)->type == ENEMY || (*it)->type == BOSS || (*it)->type == PLAYER)) {
				(*it)->take_damage();
				if (main_event->to_die_entity == true)
					it = main_event->char_list.begin();
			}

		it++;
	}
}

void Bomb::add_bonus(int x, int y) {
	int rd = rand() % 12;
	int bonus = BONUS_POWER_UP;

	if (rd == 9 || rd == 8)
		bonus = BONUS_KICK;
	else if (rd == 7 || rd == 6)
		bonus = BONUS_CHANGE;
	else if (rd == 5 || rd == 4)
		bonus = BONUS_REMOTE_BOMB;
	else if (rd % 2 == 0)
		bonus = BONUS_POWER_UP;
	else
		bonus = BONUS_PLUS_ONE;

	main_event->map[y][x] = main_event->create_bonus(BONUS, x, y, bonus);
}

int		Bomb::blast_case(int y, int x) {
	if (main_event->map[y][x]->type == WALL) {
		if (main_event->map[y][x]->status == WALL_HP_4)
			main_event->map[y][x]->status = WALL_HP_3;
		else if (main_event->map[y][x]->status == WALL_HP_3)
			main_event->map[y][x]->status = WALL_HP_2;
		else if (main_event->map[y][x]->status == WALL_HP_2)
			main_event->map[y][x]->status = WALL_HP_1;
		else if (main_event->map[y][x]->status == WALL_HP_1) {
			delete main_event->map[y][x];
			if ((rand() % 20) <= 8)
				add_bonus(x, y);
			else
				main_event->map[y][x] = main_event->create_empty(x, y);
			// main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x + 0.5, (float)y + 0.5, FIRE_2);
			// damage_entity(x, y);
		}
	}
	else if (main_event->map[y][x]->type == BOMB)
		static_cast<Bomb*>(main_event->map[y][x])->detonate();
	else if (main_event->map[y][x]->type == EMPTY) {
		delete main_event->map[y][x];
		main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x + 0.5, (float)y + 0.5, FIRE_2);
		damage_entity(x, y);
		return (0);
	}
	else if (main_event->map[y][x]->type == FIRE) {
		main_event->map[y][x]->status = FIRE_2;
		damage_entity(x, y);
		return (0);
	}
	else if (main_event->map[y][x]->type == BONUS) {
		delete main_event->map[y][x];
		main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x + 0.5, (float)y + 0.5, FIRE_2);
		damage_entity(x, y);
		return (0);
	}
	return (1);
}

void	Bomb::add_bomb_nbr(int id) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((*it)->id == id) {
				if (this->model == BOMB_REMOTE)
					(*it)->remote_nbr++;
				else
					(*it)->bomb_nbr++;
				return ;
			}
		it++;
	}
}

void	Bomb::detonate( void ) {
	int i = 0;
	int dir[4] = {0};
	add_bomb_nbr(this->creator_id);
	delete main_event->map[(int)this->pos_y][(int)this->pos_x];
	main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
	damage_entity((int)this->pos_x ,(int)this->pos_y);
	// main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_fire(FIRE_2, (int)this->pos_x - 0.5, (int)this->pos_y - 0.5, FIRE_2);

	while (i <= this->blast_radius) {
		if (dir[0] == 0 && check_coord_exist((int)(this->pos_y - i), (int)(this->pos_x)) == true)
			dir[0] = blast_case((int)(this->pos_y - i), (int)this->pos_x);

		if (dir[1] == 0 && check_coord_exist((int)(this->pos_y + i), (int)(this->pos_x)) == true)
			dir[1] = blast_case((int)(this->pos_y + i), (int)this->pos_x);

		if (dir[2] == 0 && check_coord_exist((int)(this->pos_x - i), (int)(this->pos_y)) == true)
			dir[2] = blast_case((int)this->pos_y, (int)(this->pos_x - i));

		if (dir[3] == 0 && check_coord_exist((int)(this->pos_x + i), (int)(this->pos_y)) == true)
			dir[3] = blast_case((int)this->pos_y, (int)(this->pos_x + i));

		i++;
	}
	main_event->soundrender->playSound("blast");
}

void	Bomb::push_bomb() {
	float	x = 0;//this->pos_x;
	float	y = 0;//this->pos_y;
	int		ret = EMPTY;

	if (this->pushed_dir == DIR_UP)
		y += -0.08f;
	else if (this->pushed_dir == DIR_BOTTOM)
		y += 0.08f;
	else if (this->pushed_dir == DIR_LEFT)
		x += -0.08f;
	else if (this->pushed_dir == DIR_RIGHT)
		x += 0.08f;
	ret = check_move(x * 3 + this->pos_x, y + this->pos_y);
	if (ret == EMPTY) {
		if ((int)this->pos_x != (int)(x + this->pos_x) || (int)this->pos_y != (int)(y + this->pos_y)) {
			delete main_event->map[(int)(this->pos_y + y)][(int)(this->pos_x + x)];
			main_event->map[(int)(this->pos_y + y)][(int)(this->pos_x + x)] = main_event->map[(int)this->pos_y][(int)this->pos_x];
			// delete main_event->map[(int)this->pos_y][(int)this->pos_x];
			main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
			this->pos_x = x + this->pos_x;
			this->pos_y = y + this->pos_y;
			// delete main_event->map[(int)this->pos_y][(int)this->pos_x];
			// main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
		}
		else {
			this->pos_x = x + this->pos_x;
			this->pos_y = y + this->pos_y;
		}
	}
	else
		this->pushed = false;
}

void	Bomb::bomb_timer( void ) {
	if (this->pushed == true)
		push_bomb();
	if (this->model == BOMB_REMOTE)
	 	return ;
	if (this->timer - 1 > 0) {
		if (this->timer % 9 == 0)
			this->frame++;
		this->timer--;
	}
	else
		detonate();
}
