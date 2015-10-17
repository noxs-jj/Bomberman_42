#ifndef BOMB_CLASS_HPP
# define BOMB_CLASS_HPP

# include <entity.class.hpp>
# include <ft42.class.hpp>

// class Entity;

class Bomb : public Entity {
public:
	
	Bomb( int x, int y, int status );
	Bomb( Bomb const & src );
	Bomb & operator=( Bomb const & rhs );
	virtual ~Bomb( void );

private:
	Bomb( void );
};

#endif
