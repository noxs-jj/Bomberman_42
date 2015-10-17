#include <bomb.class.hpp>
#include <main.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( void ) {}

Bomb( int x, int y, int status ) : type(BOMB), pos_x(x), pos_y(y), status(status) {}
