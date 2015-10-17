#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <ft42.class.hpp>

class Entity : public ft42 {
public:
	int type;
	int	id;
    int pos_x;
    int pos_y;  
    int dir;
    int status;
    int	frame;
    int	speed;

	Entity( int type, int id, int x, int y, int status );
	Entity( Entity const & src );
	Entity & operator=( Entity const & rhs );
	virtual ~Entity( void );

private:
	Entity( void );
};

#endif
