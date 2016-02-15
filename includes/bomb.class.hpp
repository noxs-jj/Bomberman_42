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

#ifndef BOMB_CLASS_HPP
# define BOMB_CLASS_HPP

# include <entity.class.hpp>

class entity;
class Bomb : public Entity {
public:
    int     timer;
    int     creator_id;
    bool    pushed = false;
    int     pushed_dir = 0;

    Bomb( float x, float y, int status, int model, int id );
    Bomb( Bomb const & src );
    Bomb & operator=( Bomb const & rhs );
    virtual ~Bomb( void );

    void    detonate( void );
    int     blast_case(int y, int x);
    void    bomb_timer( void );
    void    damage_entity(int x, int y );
    void    add_bomb_nbr(int id);
    void    add_bonus(int x, int y);
    void    push_bomb();
    void    suppr_remote_lst( void );

private:
    Bomb( void );
};

#endif
