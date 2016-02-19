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

#ifndef FACTORY_EVENT_HPP
# define FACTORY_EVENT_HPP

# include <ft42.class.hpp>

class Entity;
class Wall;
class Bomb;
class Bonus;
class Fire;
class Player;
class Enemy;
class Boss;

class Event;
class Menu;
class Joystick;
class SoundRender;
class Ia;
class Save;

class Factory : public ft42 {
public:
    Factory();
    virtual ~Factory();

    static Wall *           create_wall(int status, float x, float y, int model);
    static Bonus *          create_bonus(int status, float x, float y, int model);
    static Bomb *           create_bomb(int status, float x, float y, int model, int id);
    static Fire *           create_fire(int status, float x, float y, int model);
    static Player *         create_player(int status, float x, float y, int model);
    static Enemy *          create_enemy(int status, float x, float y, int model);
    static Boss *           create_boss(int status, float x, float y, int name, int model);
    static Entity *         create_empty(int x, int y);

    static Menu *           create_menu(Event * event);
    static Joystick *       create_joystick();
    static SoundRender *    create_sound_render();
    static Ia *             create_ia();
    static Event *          create_event();
    static Save *           create_save();

private:
    Factory( Factory const & src ) = delete;
    Factory & operator=( Factory const & rhs ) = delete;
};

#endif
