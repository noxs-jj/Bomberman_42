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

#include <factory.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <bonus.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>
#include <Menu.class.hpp>
#include <soundrender.class.hpp>
#include <ia.class.hpp>
#include <save.class.hpp>

Factory::Factory() {}

Factory::~Factory() {}

Wall *          Factory::create_wall(int status, float x, float y, int model) {
	Wall * wall = new Wall(x, y, status, model);
	if (NULL == wall) {
		main_event->w_error("Factory::create_wall:: wall Malloc error");
		throw std::exception();
	}
	return wall;
}

Bonus *         Factory::create_bonus(int status, float x, float y, int model) {
	Bonus * bonus = new Bonus(x, y, status, model);
	if (NULL == bonus) {
		main_event->w_error("create_bonus:: bonus Malloc error");
		throw std::exception();
	}
	return bonus;
}

Bomb *          Factory::create_bomb(int status, float x, float y, int model, int id) {
	Bomb * bomb = new Bomb(x, y, status, model, id);
	if (NULL == bomb) {
		main_event->w_error("create_bomb:: bomb Malloc error");
		throw std::exception();
	}
	return bomb;
}

Fire *          Factory::create_fire(int status, float x, float y, int model) {
	Fire * fire = new Fire(x, y, status, model);
	if (NULL == fire) {
		main_event->w_error("create_fire:: fire Malloc error");
		throw std::exception();
	}
	return fire;
}

Player *        Factory::create_player(int status, float x, float y, int model) {
	Player * player = new Player(x, y, status, model);
	if (NULL == player) {
		main_event->w_error("create_player:: player Malloc error");
		throw std::exception();
	}
	return player;
}

Enemy *         Factory::create_enemy(int status, float x, float y, int model) {
	Enemy * enemy = new Enemy(x, y, status, model);
	if (NULL == enemy) {
		main_event->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}
	return enemy;
}

Boss *         Factory::create_boss(int status, float x, float y, int name, int model) {
	Boss * boss = new Boss(x, y, status, name, model);
	if (NULL == boss) {
		main_event->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}
	return boss;
}

Entity *	   Factory::create_empty(int x, int y) {
	Entity * ent = new Entity(EMPTY, (float)x, (float)y, NO_STATUS, 0);
	if (NULL == ent) {
		main_event->w_error("create_empty:: enemy Malloc error");
		throw std::exception();
	}
	ent->model = -1;
	return ent;
}

Menu *          Factory::create_menu(Event * event) {
    Menu * new_menu = new Menu(event);
    if (NULL == new_menu) {
        main_event->w_error("Menu allocation error");
        throw std::exception();
    }
    return new_menu;
}

Joystick *      Factory::create_joystick() {
    Joystick *  new_joystick = new Joystick();
    if (NULL == new_joystick) {
        main_event->w_error("Joystick allocation error");
        throw std::exception();
    }
    return new_joystick;
}

SoundRender *   Factory::create_sound_render() {
    SoundRender *   new_sound = new SoundRender();
    if (NULL == new_sound) {
        main_event->w_error("Soundrender allocation error");
        throw std::exception();
    }
    return new_sound;
}

Ia *            Factory::create_ia() {
    Ia *    new_ia = new Ia();
    if (NULL == new_ia) {
        main_event->w_error("ia_play allocation error");
        throw std::exception();
    }
    return new_ia;
}

Event *          Factory::create_event() {
    Event *     new_event = new Event();
    if (NULL == new_event) {
        std::cerr << "Event Global allocation error" << std::endl;
        exit(EXIT_FAILURE);
    }
    return new_event;
}

Save *           Factory::create_save() {
    Save *      new_save = new Save();
    if (NULL == new_save) {
        main_event->w_error("Save() allocation error");
        throw std::exception();
    }
    return new_save;
}
