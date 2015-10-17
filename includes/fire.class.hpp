#ifndef FIRE_CLASS_HPP
# define FIRE_CLASS_HPP

# include <entity.class.hpp>

class fire : public Entity {
public:
	
	fire( int x, int y, int status );
	fire( fire const & src );
	fire & operator=( fire const & rhs );
	virtual ~fire( void );

private:
	fire( void );
};

#endif
