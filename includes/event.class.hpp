#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>
# include <bomb.class.hpp>
# include <player.class.hpp>
# include <enemy.class.hpp>
# include <wall.class.hpp>
# include <fire.class.hpp>
# include <boss.class.hpp>


class Event : public ft42 {
public:
	bool					run;
	Entity ***				map;
	std::list<Entity *>		char_list;

	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	virtual ~Event( void );

	void		fill_border_map(void);
	void		gen_level(int level, int boss);
	bool		check_coord(int mode, float x, float y);
	void		gen_obstacle(int difficulty);
	Wall *		create_wall(int status, float x, float y);
	Bomb *		create_bomb(int status, float x, float y);
	Fire *		create_fire(int status, float x, float y);
	Player *	create_player(int id, int status, float x, float y);
	Enemy *		create_enemy(int id, int status, float x, float y);
	Boss *		create_boss(int status, float x, float y, int name);
	Entity *	create_empty(int x, int y);


	void	init( int ac, char **av );
	void	exit_free( void );

	void	lauchGame( void );
	void	parse_command(int ac, char **av);

	void	print_map( void ); // DEBUGG
};

extern Event	*main_event;

#endif
