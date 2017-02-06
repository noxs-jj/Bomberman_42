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

#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>
#include <factory.class.hpp>

Wall::Wall( void ) {}

Wall::~Wall( void ) {}

Wall::Wall( float x, float y, int status, int model ) : Entity( WALL, x, y, status, model ) {
	this->model = model;
    this->to_destroy = false;
}

Wall::Wall( Wall const & src ) : Entity(src.type, src.pos_x, src.pos_y, src.status, src.model) {
    *this = src;
}

Wall & Wall::operator=( Wall const & rhs ) {
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

void    Wall::delete_wall_destoyed() {
    int y = 0,
        x = 0;

        while (y < globject::mapY_size) {
            x = 0;
            while (x < globject::mapX_size) {
                if (NULL != main_event->map[y][x] \
                        && WALL == main_event->map[y][x]->type \
    && true == reinterpret_cast<Wall*>(main_event->map[y][x])->to_destroy) {

                    delete main_event->map[y][x];
                    main_event->map[y][x] = NULL;
                    if ((rand() % 20) <= 8)
        				Bomb::add_bonus(x, y);
        			else
        				main_event->map[y][x] = Factory::create_empty(x, y);
                }
                x++;
            }
            y++;
        }
}
