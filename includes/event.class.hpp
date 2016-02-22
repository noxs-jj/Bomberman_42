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

#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>
# include <joystick.hpp>
# include <factory.class.hpp>

class Entity;
class Wall;
class Bomb;
class Bonus;
class Fire;
class Player;
class Enemy;
class Boss;
class SoundRender;
class Menu;
class globject;
class Joystick;
class Save;

class Event : public ft42 {
public:
	int						ac;
	char **					av;
	bool					run;
	Entity ***				map;
	std::list<Entity *>		char_list;
	bool					gen_level;
	bool					option_arcade;
	int						option_resolution;
	bool					option_ia_kamikaze;
	bool					coop; // false si campaign
	int 					actual_level;
	int 					save_level = 1;
	bool 					save_level_mode = false;
	int						multi; // 0 == non activer, 2 player, 3, 4, 5
	int						arena; // 0 == non activer, 2 player, 3, 4, 5
	bool					intro_map = false;
	bool					new_game; // false == continue (load fichier sauvegarde)
	int 					config[5]; // config[1](3)  == (joueur 2, config 3) (controller)
	int 					config_keyboard[5]; // config[1](3)  == (joueur 2, config 3)
	bool					general_sound; // activer son general du jeux
	bool					music; // activer musique de fond
	bool					mode_menu; // si en menu ou pas
	bool            		game_playing; // si une game en cours
	bool					game_pause; // si le jeu est en pause / fini
	int						draw_winner_multi;
	int						draw_winner_campaign;
	int						draw_lose_campaign;
	int						draw_end_campaign;
	SoundRender *			soundrender = NULL;
	Menu *					menu = NULL;
	globject *				render = NULL;
	bool					event_running = true;
	bool					to_die_entity = false;
	Joystick *				joystick = NULL;
    Save *                  save_config = NULL;
	bool					live_player[5];
    SDL_DisplayMode         sdl_display_mode_info;
    bool                    full_screen = false;
    int                     actual_resolution = RESOLUTION_NOT_SET;
		int 										game_ended = -1;

	Event( void );
	virtual ~Event( void );

	void		fill_border_map(void);
	void		gen_level_campaign(int level, int boss, bool coop);
	void		gen_level_multi(int level, int coop);
	bool		check_coord(int mode, float x, float y);
	void		gen_obstacle(int difficulty);
	void		gen_level_arena(int level, int coop);

	void		remote_detonate( int model );
	void		remote_put( int model );
	void		cheat_stats( void );
	void		player_move(int model, int dir);
	void		player_bomb(int model);
	void		ia_bomb(int id);
	void		dec_timer( void );
	void		init( int ac, char **av );
	void		exit_free( void );
	void		lauchGame( void );
	void		parse_command(int ac, char **av);
	void		print_map( void ); // DEBUGG
	void 		make_new_game( int new_level );
	void 		free_game( void );

private:
    Event( Event const & src ) = delete;
    Event & operator=( Event const & rhs ) = delete;
};

extern Event	*main_event;

#endif
