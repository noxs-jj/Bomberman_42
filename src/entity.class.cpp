#include <entity.class.hpp>
#include <main.hpp>

Entity::Entity(void)
{

}

Entity::~Entity( void ) {}

Entity::Entity( int type, int id, float x, float y, int status ) : type(type), id(id), pos_x(x),
															pos_y(y), status(status), zoom_m(1) {}

int		Entity::check_move( float x, float y ) {
	if (main_event->map[(int)y][(int)x]->type == WALL)
		return WALL;
	else if (main_event->map[(int)y][(int)x]->type == BOMB
			&& !(this->pos_y == y && this->pos_x == x))
		return BOMB;
	else if (main_event->map[(int)y][(int)x]->type == FIRE)
		return FIRE;
	return EMPTY;
}

void	Entity::move( int dir ) {
	float	x = 0, y = 0;
	int		ret = EMPTY;

	if (dir == DIR_UP)
		y = -.1f;
	else if (dir == DIR_BOTTOM)
		y = .1f;
	else if (dir == DIR_LEFT)
		x = -.1f;
	else if (dir == DIR_RIGHT)
		x = .1f;
	ret = check_move(x, y);
	if (ret == EMPTY) {
		this->pos_x += x;
		this->pos_y += y;
		// change frame here
	}
	else if (ret == FIRE) {
		take_damage();
	}
}

void	Entity::take_damage( void ) {
	// dec health
	// if health <= 0
	die();
}

void	Entity::die( void ) {
	std::cout << "Someone died" << std::endl;
}
