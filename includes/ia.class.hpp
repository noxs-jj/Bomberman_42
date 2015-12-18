#ifndef IA_CLASS_HPP
# define IA_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>

class Ia : public ft42 {
public:
  unsigned long layer;
  int direction;

	Ia( int layer );
	Ia( Ia const & src );
	Ia & operator=( Ia const & rhs );
	virtual ~Ia( void );
	Ia( void );
	void start( int time );
  int must_move_to( Entity *it );
  bool play_enemy( Entity *it );
};

#endif
