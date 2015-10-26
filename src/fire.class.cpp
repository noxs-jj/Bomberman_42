#include <fire.class.hpp>

Fire::~Fire( void ) {}

Fire::Fire( float x, float y, int status, int model ) : Entity( FIRE, 0, x, y, status ) {
	this->model = model;
	this->timer = 40;
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((int)(*it)->pos_x == (int)x && (int)(*it)->pos_y == (int)y
			&& ((*it)->type == ENEMY || (*it)->type == BOSS || (*it)->type == PLAYER))
			(*it)->take_damage();
		it++;
	}
}

void	Fire::fire_timer( void ) {
	if (this->timer - 1 > 0) {
		if (this->timer % 2 == 0)
			this->frame++;
		this->timer--;
	}
	else {
		delete main_event->map[(int)this->pos_y][(int)this->pos_x];
		main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
	}
}