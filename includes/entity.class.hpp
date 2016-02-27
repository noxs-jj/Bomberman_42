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

#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <ft42.class.hpp>
# include <event.class.hpp>
// # include <wall.class.hpp>

class Entity : public ft42 {
public:
    std::list<Entity *>     remote_lst;
    int                     type;
    int                     id;
    int                     model;
    float                   pos_x;
    float                   pos_y;
    int                     dir;
    int                     status;
    float                   frame;
    int                     speed;
    int                     blast_radius;
    long long int           time_creation;
    float                   zoom_m;
    int                     bomb_nbr = 1;
    bool                    kick_bomb = false;
    int                     bomb_model = BOMB_DEFAULT;
    bool                    remote = false;
    int                     remote_nbr = 0;
    static int              autoincrement;

    Entity( int type, float x, float y, int status, int model );
    Entity( Entity const & src );
    Entity & operator=( Entity const & rhs );
    virtual ~Entity( void );
    Entity( void );

    int                     pretest_move( int dir );
    std::vector<int>        pretest_moves(int dir);
    void                    move( int dir );
    int                     check_move( float x, float y );
    void                    die( void );
    void                    take_damage( void );
    void                    put_bomb(int status, float x, float y, int model, int blast, int id);
    bool                    position_is_player( float x, float y );
    bool                    friend_zone( float x, float y );
    int                     count_entity(int type);
    void                    destroy_bomb_list();
};

#endif
