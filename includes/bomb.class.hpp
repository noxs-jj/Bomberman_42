#ifndef BOMB_CLASS_HPP
# define BOMB_CLASS_HPP

# include <entity.class.hpp>

class entity;
class Bomb : public Entity {
public:
	
	Bomb( float x, float y, int status, int model );
	Bomb( Bomb const & src );
	Bomb & operator=( Bomb const & rhs );
	virtual ~Bomb( void );
	void	detonate( void );
	void	blast_case(int x, int y);

private:
	Bomb( void );
};

#endif
