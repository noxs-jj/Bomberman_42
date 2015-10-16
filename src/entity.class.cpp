#include <entity.class.hpp>
#include <main.hpp>

Entity::~Entity( void ) {}

Entity::Entity( void ) {}

Entity( int type, int id, int x, int y, int status ) : type(type), id(id), pos_x(x),
														pos_y(y), status(status) {}
