#include <wall.class.hpp>
#include <main.hpp>

Wall::~Wall( void ) {}

Wall::Wall( void ) {}

Wall( int x, int y, int status ) : type(WALL), pos_x(x), pos_y(y), status(status) {}
