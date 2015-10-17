#include <fire.class.hpp>
#include <main.hpp>

Fire::~Fire( void ) {}

Fire::Fire( void ) {}

Fire( int x, int y, int status ) : type(FIRE), pos_x(x), pos_y(y), status(status) {}
