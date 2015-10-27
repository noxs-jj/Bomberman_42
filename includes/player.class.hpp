#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include <entity.class.hpp>

class Entity;
class Player : public Entity {
public:
	Player( float x, float y, int status, int model );
	Player( Player const & src );
	Player & operator=( Player const & rhs );
	virtual ~Player( void );

private:
	Player( void );
};

#endif
