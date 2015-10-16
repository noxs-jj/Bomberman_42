#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <main.hpp>
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


	Entity( void );
	Entity( Entity const & src );
	Entity & operator=( Entity const & rhs );
	virtual ~Entity( void );
};

#endif
