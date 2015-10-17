#include <event.class.hpp>

Event::Event( void ) : run(true) {
	this->map = NULL;
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

Wall *	Event::create_wall(int status, int x, int y) {
	Wall * wall = new Wall(x, y, status);
	if (wall == NULL) {
		this->w_error("create_wall:: wall Malloc error");
		throw std::exception();
	}

	return wall;
}

Bomb *	Event::create_bomb(int status, int x, int y) {
	Bomb * bomb = new Bomb(x, y, status);
	if (bomb == NULL) {
		this->w_error("create_bomb:: bomb Malloc error");
		throw std::exception();
	}

	return bomb;
}

Fire *	Event::create_fire(int status, int x, int y) {
	Fire * fire = new Fire(x, y, status);
	if (fire == NULL) {
		this->w_error("create_fire:: fire Malloc error");
		throw std::exception();
	}

	return fire;
}

Player *	Event::create_player(int id, int status, int x, int y) {
	Player * player = new Player(id, x, y, status);
	if (player == NULL) {
		this->w_error("create_player:: player Malloc error");
		throw std::exception();
	}

	return player;
}

Enemy *	Event::create_enemy(int id, int status, int x, int y) {
	Enemy * enemy = new Enemy(id, x, y, status);
	if (enemy == NULL) {
		this->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}

	return enemy;
}

void	Event::fill_border_map(void) {
	int 	y = 0,
			x = 0;

	this->map = (Entity ***)std::malloc(sizeof(Entity **) * MAP_Y_SIZE);
	if (this->map == NULL) {
		this->w_error("fill_border_map:: this->map Malloc error");
		throw std::exception();
	}

	while (y < MAP_Y_SIZE) {
		this->map[y] = NULL;
		this->map[y] = (Entity **)std::malloc(sizeof(Entity *) * MAP_X_SIZE);
		if (this->map[y] == NULL) {
			this->w_error("fill_border_map:: this->map[y] Malloc error");
			throw std::exception();
		}
		x = 0;
		while (x < MAP_X_SIZE) {
			if (y == 0 || y == MAP_Y_SIZE - 1 || x == 0 || x == MAP_X_SIZE - 1) {
				this->map[y][x] = new Entity(WALL, 0, x, y, WALL_INDESTRUCTIBLE);
				if (this->map[y][x] == NULL) {
					this->w_error("fill_border_map:: this->map[y][x] Malloc error");
					throw std::exception();
				}
			}
			x++;
		}
		y++;
	}
}
