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

#ifndef WALL_CLASS_HPP
# define WALL_CLASS_HPP

# include <entity.class.hpp>
// #include <event.class.hpp>

class Entity;
// class Event;
class Wall : public Entity {
public:
	Wall( float x, float y, int status, int model );
	Wall( Wall const & src );
	Wall & operator=( Wall const & rhs );
	virtual ~Wall( void );

private:
	Wall( void );
};

#endif
