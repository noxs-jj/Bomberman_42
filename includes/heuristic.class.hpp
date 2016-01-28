#ifndef Heuristic_CLASS_HPP
# define Heuristic_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>

class Heuristic : public ft42 {
public:
  Heuristic( Heuristic const & src );
	Heuristic & operator=( Heuristic const & rhs );
	virtual ~Heuristic( void );
	Heuristic( void );
  int heuristic(std::vector<int> its);
};

#endif
