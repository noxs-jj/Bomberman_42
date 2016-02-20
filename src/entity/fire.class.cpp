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

#include <fire.class.hpp>

Fire::~Fire( void ) {}

Fire::Fire( float x, float y, int status, int model ) : Entity( FIRE, x, y, status, model ) {
	this->model = model;
	this->timer = 40;
}

Fire::Fire( Fire const & src ) {
    *this = src;
}
Fire & Fire::operator=( Fire const & rhs ) {
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

void	Fire::fire_timer( void ) {
    Entity *tmp = NULL;
	if (this->timer - 1 > 0) {
		if (this->timer % 2 == 0)
			this->frame++;
		this->timer--;
	}
	else {
		tmp = main_event->map[(int)this->pos_y][(int)this->pos_x];
        main_event->map[(int)this->pos_y][(int)this->pos_x] = NULL;
		main_event->map[(int)this->pos_y][(int)this->pos_x] = Factory::create_empty((int)this->pos_x, (int)this->pos_y);
        delete tmp;
	}
}
