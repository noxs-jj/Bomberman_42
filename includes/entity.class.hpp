#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <ft42.class.hpp>
# include <event.class.hpp>
// # include <wall.class.hpp>


class Entity : public ft42 {
public:
	int		type;
	int		id;
    float	pos_x;
    float	pos_y;  
    int 	dir;
    int 	status;
    int		frame;
    int		speed;
    int		blast_radius;
    float	zoom_m;

	Entity( int type, int id, float x, float y, int status );
	Entity( Entity const & src );
	Entity & operator=( Entity const & rhs );
	virtual ~Entity( void );
	Entity( void );
	void	move( int dir );
	int		check_move( float x, float y );
	void	die( void );
	void	take_damage( void );
};

#endif
