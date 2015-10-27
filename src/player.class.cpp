#include <player.class.hpp>

Player::~Player( void ) {}

Player::Player( float x, float y, int status, int model ) : Entity( PLAYER, id, x, y, status ) {
	this->speed = 1;
	this->frame = 0;
	this->blast_radius = 1;
	this->model = model;
}
