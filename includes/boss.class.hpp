#ifndef BOSS_CLASS_HPP
# define BOSS_CLASS_HPP

# include <entity.class.hpp>
class Entity;

class Boss : public Entity {
public:

	int name;

	Boss( float x, float y, int status, int name );
	Boss( Boss const & src );
	Boss & operator=( Boss const & rhs );
	virtual ~Boss( void );

private:
	Boss( void );
};

#endif
