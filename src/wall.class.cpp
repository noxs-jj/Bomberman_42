#include <wall.class.hpp>

Wall::~Wall( void ) {}

Wall::Wall( int x, int y, int status ) : Entity( WALL, 0, x, y, status ) {}
