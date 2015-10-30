#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>
// # include <bomb.class.hpp>
// # include <player.class.hpp>
// # include <enemy.class.hpp>
// # include <wall.class.hpp>
// # include <fire.class.hpp>
// # include <boss.class.hpp>

class Entity;
class Wall;
class Bomb;
class Fire;
class Player;
class Enemy;
class Boss;
class SoundRender;

class Event : public ft42 {
public:
	bool									run;
	Entity ***						map;
	std::list<Entity *>		char_list;
	bool									coop; // false si campaign
	int										multi; // 0 == non activer, 2 player, 3, 4, 5
	bool									new_game; // false == continue (load fichier sauvegarde)
	int 									config[4]; // config[1](3)  == (joueur 2, config 3)
	bool									general_sound; // activer son general du jeux
	bool									music; // activer musique de fond


	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	virtual ~Event( void );

	void		fill_border_map(void);
	void		gen_level_campaign(int level, int boss, bool coop);
	void		gen_level_multi(int level, int coop);
	bool		check_coord(int mode, float x, float y);
	void		gen_obstacle(int difficulty);
	Wall *		create_wall(int status, float x, float y, int model);
	Bomb *		create_bomb(int status, float x, float y, int model);
	Fire *		create_fire(int status, float x, float y, int model);
	Player *	create_player(int status, float x, float y, int model);
	Enemy *		create_enemy(int status, float x, float y, int model);
	Boss *		create_boss(int status, float x, float y, int name, int model);
	Entity *	create_empty(int x, int y);
	void        load_sounds(void);
	void        play_sound(std::string soundName);

	void		player_move(int id, int dir);
	void		player_bomb(int id);
	void		dec_timer( void );


	void	init( int ac, char **av );
	void	exit_free( void );

	void	lauchGame( void );
	void	parse_command(int ac, char **av);

	void	print_map( void ); // DEBUGG

private:
	SoundRender *	soundrender = NULL;
};

extern Event	*main_event;

#endif
