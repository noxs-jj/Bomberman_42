#include <event.class.hpp>
#include <main.hpp>

Event::Event( void ) : run(true) {

}

Event::Event( Event const & src ) { *this = src; }

Event & Event::operator=( Event const & rhs ) {
	if (this != &rhs) {}
	return (*this);
}

Event::~Event( void ) {}

void	Event::parse_command(int ac, char **av) {
	int i = 0;


	while ( i < ac ) {
		if ( 0 == strcmp(av[i], "-log") )
			ft42::logg = true;

		i++;
	}
}

void	Event::init( int ac, char **av ) {
	this->parse_command(ac, av);

}


void	Event::exit_free( void ) {	// free here

	this->w_log("Event::exit_free ==> End of free gomoku");

}


void	Event::lauchGame( void ) {
	// Loop Game
	while (this->run == true) {

	}

}
