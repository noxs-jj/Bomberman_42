#include <player.class.hpp>

Player::~Player( void ) {}

Player::Player( int id, int x, int y, int status ) : Entity( PLAYER, id, x, y, status ) {
	this->speed = 1;
	this->frame = 0;
}
