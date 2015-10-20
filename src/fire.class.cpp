#include <fire.class.hpp>

Fire::~Fire( void ) {}

Fire::Fire( float x, float y, int status ) : Entity( FIRE, 0, x, y, status ) {
	// check if someone is here
}
