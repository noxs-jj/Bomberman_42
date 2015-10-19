#include <entity.class.hpp>
#include <main.hpp>

Entity::Entity(void)
{

}

Entity::~Entity( void ) {}

Entity::Entity( int type, int id, float x, float y, int status ) : type(type), id(id), pos_x(x),
															pos_y(y), status(status), zoom_m(1) {}
