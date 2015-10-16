#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include <main.hpp>
# include <ft42.class.hpp>
# include <entity.class.hpp>

class Event : public ft42 {
public:
	bool				run;

	Entity **			map;
	

	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	virtual ~Event( void );

	void	init( int ac, char **av );
	void	exit_free( void );

	void	lauchGame( void );
	void	parse_command(int ac, char **av);

};

#endif
