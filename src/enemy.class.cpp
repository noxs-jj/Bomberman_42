#include <enemy.class.hpp>
#include <main.hpp>

Enemy::~Enemy( void ) {}

Enemy::Enemy( void ) {}

Enemy( int id, int x, int y, int status ) : id(id), type(ENEMY), pos_x(x), pos_y(y), dir(2), status(status), frame(0), speed(1) {}
