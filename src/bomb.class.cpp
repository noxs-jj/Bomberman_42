#include <bomb.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( float x, float y, int status ) : Entity( BOMB, 0, x, y, status ) {}

