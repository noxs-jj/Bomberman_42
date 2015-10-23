#include <main.hpp>
#include <list>

Event *		main_event = new Event();

int main( int ac, char **av ) {
	(void)(av);
	(void)(ac);
	try {
		


		main_event->init(ac, av);

		// event->lauchGame();


		delete main_event;
	}
	catch (std::exception & e){
		return (EXIT_FAILURE);
	}

	srand(clock());
	globject::init();
	Entity map[20][20];

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j].id = WALL;
			if (!(rand() % 2))
				map[i][j].id = 10;
		}
	}
	std::list<Player*> lol;
	int e;
	static float time = 0;
	for (int i = 0; i < 30; i++)
	{
		std::cout << globject::_object[WALL].parser._textID[i] << std::endl;
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
