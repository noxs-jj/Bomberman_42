#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>

// #ifndef BOMB_CLASS_HPP
// # define BOMB_CLASS_HPP
// # include <bomb.class.hpp>
// #endif

// #ifndef PLAYER_CLASS_HPP
// # define PLAYER_CLASS_HPP
// # include <player.class.hpp>
// #endif

// #ifndef ENEMY_CLASS_HPP
// # define ENEMY_CLASS_HPP
// # include <enemy.class.hpp>
// #endif

// #ifndef WALL_CLASS_HPP
// # define WALL_CLASS_HPP
# include <wall.class.hpp>
// #endif

// #ifndef FIRE_CLASS_HPP
// # define FIRE_CLASS_HPP
// # include <fire.class.hpp>
// #endif


// class Bomb;
// class Fire;
// class Enemy;
// class Wall;
// class Player;
// class Entity;

class Event : public ft42 {
public:
	bool				run;

	Entity ***			map;

	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	virtual ~Event( void );

	void	fill_border_map(void);
	Wall *	create_wall(int status, int x, int y);
	// Bomb *	create_bomb(int status, int x, int y);
	// Fire *	create_fire(int status, int x, int y);
	// Player *	create_player(int status, int x, int y);
	// Enemy *	create_enemy(int status, int x, int y);


	void	init( int ac, char **av );
	void	exit_free( void );

	void	lauchGame( void );
	void	parse_command(int ac, char **av);

};

#endif
