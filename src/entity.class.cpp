#include <entity.class.hpp>
#include <main.hpp>

Entity::Entity(void)
{

}

Entity::~Entity( void ) {}

Entity::Entity( int type, int id, float x, float y, int status ) : type(type), id(id), pos_x(x),
															pos_y(y), status(status),
															blast_radius(1), zoom_m(1) {}

bool	Entity::check_move( float x, float y) {
	if (main_event->map[(int)y][(int)x]->type == WALL
		|| (main_event->map[(int)y][(int)x]->type == BOMB
			&& !(this->pos_y == y && this->pos_x == x)))
		return false;
	return true;
}

void	Entity::move( int dir ) {
	float x = 0, y = 0;

	if (dir == DIR_UP)
		y = -.1f;
	else if (dir == DIR_BOTTOM)
		y = .1f;
	else if (dir == DIR_LEFT)
		x = -.1f;
	else if (dir == DIR_RIGHT)
		x = .1f;
	if (check_move(x, y) == true) {
		this->pos_x += x;
		this->pos_y += y;
	}
}