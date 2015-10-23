#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include <entity.class.hpp>

class Entity;
class Player : public Entity {
public:
	Player( int id, float x, float y, int status );
	Player( Player const & src );
	Player & operator=( Player const & rhs );
	virtual ~Player( void );

private:
	Player( void );
};

#endif
