#ifndef FIRE_CLASS_HPP
# define FIRE_CLASS_HPP

# include <entity.class.hpp>

class Entity;
class Fire : public Entity {
public:
	int		timer;

	Fire( float x, float y, int status, int model );
	Fire( Fire const & src );
	Fire & operator=( Fire const & rhs );
	virtual ~Fire( void );

	void	fire_timer( void );

private:
	Fire( void );
};

#endif
