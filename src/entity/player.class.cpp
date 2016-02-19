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

#include <player.class.hpp>

Player::Player( void ) {}

Player::~Player( void ) {}

Player::Player( float x, float y, int status, int model ) : Entity( PLAYER, x, y, status, model ) {
	this->speed = 1;
	this->frame = 0;
	this->blast_radius = 2;
	this->model = model;
}


Player::Player( Player const & src ) {
    *this = src;
}

Player & Player::operator=( Player const & rhs ) {
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
