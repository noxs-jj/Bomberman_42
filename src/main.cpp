#include <main.hpp>

int main( int ac, char **av ) {
	(void)(av);
	(void)(ac);
	try {
//		Event *		event = new Event();


		//delete event;
	}
	catch (std::exception & e){
		return (EXIT_FAILURE);
	}
	rcm_rotmat(0, 0, 0);
	return (EXIT_SUCCESS);
}
