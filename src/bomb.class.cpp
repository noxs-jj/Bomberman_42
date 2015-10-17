#include <bomb.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( int x, int y, int status ) : Entity( BOMB, 0, x, y, status ) {}
