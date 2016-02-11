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

#include <boss.class.hpp>

Boss::~Boss( void ) {}

Boss::Boss( float x, float y, int status, int name, int model ) : Entity( BOSS, x, y, status, model ) {
	this->frame = 0;
	this->speed = 1;
	this->dir = DIR_BOTTOM;
	this->name = name;
	this->blast_radius = 2;
	this->zoom_m = 2;
	this->model = model;
}
