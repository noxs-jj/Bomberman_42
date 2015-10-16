#include <event.class.hpp>
#include <main.hpp>

Event::Event( void ) : run(true) {
	this->map == NULL;
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

void	Event::fill_border_map(void) {
	int 	y = 0,
			x = 0;

	this->map = (Entity **)std::malloc(sizeof(Entity *) * MAP_Y_SIZE);
	if (this-map == NULL) {
		this->w_error("fill_border_map:: this->map Malloc error");
		throw std::exception();
	}

	while (y < MAP_Y_SIZE) {
		this->map[y] == NULL;
		this->map[y] = (Entity *)std::malloc(sizeof(Entity) * MAP_X_SIZE);
		if (this-map[y] == NULL) {
			this->w_error("fill_border_map:: this->map[y] Malloc error");
			throw std::exception();
		}
		x = 0;
		while (x < MAP_X_SIZE) {
			if (y == 0 || y == MAP_Y_SIZE - 1 || x == 0 || x == MAP_X_SIZE - 1) {
				this->map[y][x] = new Entity(WALL, 0, x, y, WALL_INDESTRUCTIBLE)
				if (this-map[y][x] == NULL) {
					this->w_error("fill_border_map:: this->map[y][x] Malloc error");
					throw std::exception();
				}
			}
			x++;
		}
		y++;
	}
}
