#include <wall.class.hpp>

Wall::~Wall( void ) {}

Wall::Wall( float x, float y, int status ) : Entity( WALL, 0, x, y, status ) {}
