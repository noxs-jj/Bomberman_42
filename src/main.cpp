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
	Entity map[20][20];
	std::list<Player*> lol;
	int e;
	static float time = 0;
	for (int i = 0; i < globject::_object[WALL].parser._finalTextSize; i++)
	{
		std::cout << globject::_object[WALL].parser._finalText[i] << std::endl;
	}
	while (1)
	{
//		std::cout << (1 / (clock() - time)) * CLOCKS_PER_SEC << std::endl;
		time = clock();
		SDL_PumpEvents();
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RETURN]) {
			exit(0);
			globject::resize(1000, 1000);
		}
		globject::render_all(map, lol);
	}
    //Test graphique...
	return (EXIT_SUCCESS);
}
