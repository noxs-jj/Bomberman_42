#include <main.hpp>
#include <list>
int main( int ac, char **av ) {
	(void)(av);
	(void)(ac);
	try {
		Event *		event = new Event();

		event->init(ac, av);
		// event->lauchGame();


		delete event;
	}
	catch (std::exception & e){
		return (EXIT_FAILURE);
	}
	globject::init();
	return (EXIT_SUCCESS);
}
