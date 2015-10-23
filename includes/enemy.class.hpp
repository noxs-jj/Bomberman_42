#ifndef ENEMY_CLASS_HPP
# define ENEMY_CLASS_HPP

# include <entity.class.hpp>

class Entity;
class Enemy : public Entity {
public:
	
	Enemy( int id, float x, float y, int status );
	Enemy( Enemy const & src );
	Enemy & operator=( Enemy const & rhs );
	virtual ~Enemy( void );

private:
	Enemy( void );
};

#endif
