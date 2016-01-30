#include <boss.class.hpp>

Boss::~Boss( void ) {}

Boss::Boss( float x, float y, int status, int name, int model ) : Entity( BOSS, x, y, status ) {
	this->frame = 0;
	this->speed = 1;
	this->dir = DIR_BOTTOM;
	this->name = name;
	this->blast_radius = 2;
	this->zoom_m = 2;
	this->model = model;
}