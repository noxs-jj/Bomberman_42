#include <enemy.class.hpp>

Enemy::~Enemy( void ) {}

Enemy::Enemy( int id, float x, float y, int status, int model ) : Entity( ENEMY, id, x, y, status ) {
	this->frame = 0;
	this->speed = 1;
	this->dir = DIR_BOTTOM;
	this->blast_radius = 1;
	this->model = model;
}
