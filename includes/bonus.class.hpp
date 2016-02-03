#ifndef BONUS_CLASS_HPP
# define BONUS_CLASS_HPP

# include <entity.class.hpp>

class entity;
class Bonus : public Entity {
public:
	int		timer;

	Bonus( float x, float y, int status, int model );
	Bonus( Bonus const & src );
	Bonus & operator=( Bonus const & rhs );
	virtual ~Bonus( void );
private:
	Bonus( void );
};

#endif
