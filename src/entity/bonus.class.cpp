#include <bonus.class.hpp>

Bonus::~Bonus( void ) {}

Bonus::Bonus( float x, float y, int status, int model ) : Entity( BONUS, x, y, status ) {
	this->model = model;
}
