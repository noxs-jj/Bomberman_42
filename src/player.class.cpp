#include <player.class.hpp>
#include <main.hpp>

Player::~Player( void ) {}

Player::Player( void ) {}

Player( int id, int x, int y, int status ) : id(id), type(PLAYER), pos_x(x), pos_y(y), dir(2), status(status), frame(0), speed(1) {}
