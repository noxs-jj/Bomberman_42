#include <main.hpp>

int main( int ac, char **av ) {
	try {
		Event *		event = new Event();


		delete event;
	}
	catch (std::exception & e){
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
