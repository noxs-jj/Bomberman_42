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

#include <bonus.class.hpp>
#include <entity.class.hpp>
#include <soundrender.class.hpp>

Bonus::~Bonus( void ) {}

Bonus::Bonus( float x, float y, int status, int model ) : Entity( BONUS, x, y, status, model ) {
	this->model = model;
}

Bonus::Bonus( Bonus const & src ) {
    *this = src;
}

Bonus & Bonus::operator=( Bonus const & rhs ) {
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
        this->timer = rhs.timer;
    }
    return *this;
}

void Bonus::change_bomb(Entity *ent) {
	int rd = rand() % 4;

	if (rd == 0)
		ent->bomb_model = BOMB_DEFAULT;
	else if (rd == 1)
		ent->bomb_model = BOMB_WATER;
	else if (rd == 2)
		ent->bomb_model = BOMB_LIGHT;
	else
		ent->bomb_model = BOMB_WIND;
}

void	Bonus::affect(Entity *ent) {
	if (this->model == BONUS_POWER_UP) {
		ent->blast_radius++;
		main_event->soundrender->playSound("powerup");
	}
	else if (this->model == BONUS_PLUS_ONE) {
		ent->bomb_nbr++;
		main_event->soundrender->playSound("danger");
	}
	else if (this->model == BONUS_KICK) {
		ent->kick_bomb = true;
		main_event->soundrender->playSound("powerup");
	}
	else if (this->model == BONUS_CHANGE) {
		change_bomb(ent);
		main_event->soundrender->playSound("powerup");
	}
	else if (this->model == BONUS_REMOTE_BOMB) {
		ent->remote = true;
		ent->remote_nbr++;
		main_event->soundrender->playSound("special");
	}
}
