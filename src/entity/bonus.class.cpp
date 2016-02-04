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

Bonus::~Bonus( void ) {}

Bonus::Bonus( float x, float y, int status, int model ) : Entity( BONUS, x, y, status ) {
	this->model = model;
}

void	Bonus::affect(Entity *ent) {
	if (this->model == BONUS_POWER_UP)
		ent->blast_radius++;
	else if (this->model == BONUS_PLUS_ONE)
		ent->bomb_nbr++;
	else if (this->model == BONUS_KICK)
		ent->kick_bomb = true;
	else if (this->model == BONUS_CHANGE)
		ent->bomb_model = BOMB;
}
