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

Fire::Fire( float x, float y, int status, int model ) : Entity( FIRE, x, y, status ) {
	this->model = model;
	this->timer = 40;
}

void	Fire::fire_timer( void ) {
	if (this->timer - 1 > 0) {
		if (this->timer % 2 == 0)
			this->frame++;
		this->timer--;
	}
	else {
		delete main_event->map[(int)this->pos_y][(int)this->pos_x];
		main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
	}
}
