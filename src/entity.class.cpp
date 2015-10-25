#include <entity.class.hpp>
#include <main.hpp>
#include <bomb.class.hpp>

int		Entity::autoincrement = 0;


Entity::Entity(void)
{

}

Entity::~Entity( void ) {}

Entity::Entity( int type, int id, float x, float y, int status ) : type(type), pos_x(x),
															pos_y(y), status(status), zoom_m(1) {
	Entity::autoincrement++;
	this->id = Entity::autoincrement;
}

int		Entity::check_move( float x, float y ) {
	if (main_event->map[(int)y][(int)x]->type == WALL) {
		std::cout << "wall !!! " << std::endl;
		return WALL;
	}
	else if (main_event->map[(int)y][(int)x]->type == BOMB
			&& !((int)this->pos_y == (int)y && (int)this->pos_x == (int)x)) {
		std::cout << "bomb !!! " << std::endl;
		return BOMB;
	}
	else if (main_event->map[(int)y][(int)x]->type == FIRE) {
		std::cout << "fire !!! " << std::endl;
		return FIRE;
	}
	return EMPTY;
}

void	Entity::move( int dir ) {
	float	x = this->pos_x;
	float	y = this->pos_y;
	int		ret = EMPTY;

	if (dir == DIR_UP)
		y += -0.2f;
	else if (dir == DIR_BOTTOM)
		y += 0.2f;
	else if (dir == DIR_LEFT)
		x += -0.2f;
	else if (dir == DIR_RIGHT)
		x += 0.2f;
	ret = check_move(x, y);
	std::cout << "pos real " << this->pos_x << " " << this->pos_y << std::endl;
	std::cout << "pos real " << x << " " << y << std::endl;
	if (ret == EMPTY) {
		this->dir = dir;
		this->pos_x = x;
		this->pos_y = y;
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

void	Entity::put_bomb(int status, float x, float y, int model) {
	delete main_event->map[(int)y][(int)x];
	// main_event->map[(int)y][(int)x] = main_event->create_empty((int)x, (int)y);
	main_event->map[(int)y][(int)x] = main_event->create_bomb(status, x, y, model);
}