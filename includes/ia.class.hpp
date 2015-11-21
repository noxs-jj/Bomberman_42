#ifndef IA_CLASS_HPP
# define IA_CLASS_HPP

# include <ft42.class.hpp>

class Ia : public ft42 {
public:
  unsigned long layer;

	Ia( int layer );
	Ia( Ia const & src );
	Ia & operator=( Ia const & rhs );
	virtual ~Ia( void );
	Ia( void );
	void	start( int time );
};

#endif
