#ifndef WALL_CLASS_HPP
# define WALL_CLASS_HPP

# include <entity.class.hpp>

class Wall : public Entity {
public:
	
	Wall( int x, int y, int status );
	Wall( Wall const & src );
	Wall & operator=( Wall const & rhs );
	virtual ~Wall( void );

private:
	Wall( void );
};

#endif
