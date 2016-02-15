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

#ifndef IA_CLASS_HPP
# define IA_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>
# include <enemy.class.hpp>
# include <boss.class.hpp>

class Ia : public ft42 {
public:
    unsigned long   layer;
    int             direction;

	Ia( int layer );
	Ia( Ia const & src );
	Ia & operator=( Ia const & rhs );
	virtual ~Ia( void );
	Ia( void );

    void    start( int time );
    int     must_move_to( Entity *it );
    bool    play_enemy( Enemy *it );
    bool    play_boss(Boss *it, int time);
};

#endif
