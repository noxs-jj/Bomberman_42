#include <enemy.class.hpp>

Enemy::~Enemy( void ) {}

Enemy::Enemy( float x, float y, int status, int model ) : Entity( ENEMY, x, y, status ) {
	this->frame = 0;
	this->speed = 1;
	this->dir = DIR_UP;
	this->blast_radius = 1;
	this->model = model;
}
