#include <wall.class.hpp>

Wall::~Wall( void ) {}

Wall::Wall( float x, float y, int status, int model ) : Entity( WALL, x, y, status ) {
	this->model = model;
}
