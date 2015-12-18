#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <ft42.class.hpp>
# include <event.class.hpp>
// # include <wall.class.hpp>


class Entity : public ft42 {
public:
	int		type;
	int		id;
	int		model;
  float	pos_x;
  float	pos_y;
  int 	dir;
  int 	status;
  float	frame;
  int		speed;
  int		blast_radius;
  float	zoom_m;
	static int		autoincrement;

	Entity( int type, float x, float y, int status );
	Entity( Entity const & src );
	Entity & operator=( Entity const & rhs );
	virtual ~Entity( void );
	Entity( void );
	int	pretest_move( int dir );
	std::vector<int>	pretest_moves(int dir);
	void	move( int dir );
	int		check_move( float x, float y );
	void	die( void );
	void	take_damage( void );
	void	put_bomb(int status, float x, float y, int model, int blast);
	bool position_is_player( float x, float y );
	int		count_entity(int type);
};

#endif
