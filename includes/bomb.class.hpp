#ifndef BOMB_CLASS_HPP
# define BOMB_CLASS_HPP

# include <entity.class.hpp>

class entity;
class Bomb : public Entity {
public:
	int		timer;
	int		creator_id;

	Bomb( float x, float y, int status, int model, int id );
	Bomb( Bomb const & src );
	Bomb & operator=( Bomb const & rhs );
	virtual ~Bomb( void );
	void	detonate( void );
	int		blast_case(int y, int x);
	void	bomb_timer( void );
	void	damage_entity(int x, int y );
	void	add_bomb_nbr(int id);
private:
	Bomb( void );
};

#endif
