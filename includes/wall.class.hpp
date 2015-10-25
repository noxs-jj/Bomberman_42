#ifndef WALL_CLASS_HPP
# define WALL_CLASS_HPP

# include <entity.class.hpp>
// #include <event.class.hpp>

class Entity;
// class Event;
class Wall : public Entity {
public:
	Wall( float x, float y, int status, int model );
	Wall( Wall const & src );
	Wall & operator=( Wall const & rhs );
	virtual ~Wall( void );

private:
	Wall( void );
};

#endif
