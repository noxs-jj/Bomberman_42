#ifndef BOMB_CLASS_HPP
# define BOMB_CLASS_HPP

# include <entity.class.hpp>

class Bomb : public Entity {
public:
	
	Bomb( float x, float y, int status );
	Bomb( Bomb const & src );
	Bomb & operator=( Bomb const & rhs );
	virtual ~Bomb( void );

private:
	Bomb( void );
};

#endif
