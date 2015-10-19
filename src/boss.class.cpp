#include <boss.class.hpp>

Boss::~Boss( void ) {}

Boss::Boss( float x, float y, int status, int name ) : Entity( BOSS, 0, x, y, status ) {
	this->frame = 0;
	this->speed = 1;
	this->dir = DIR_BOTTOM;
	this->name = name;
	this->zoom_m = 2;
}
