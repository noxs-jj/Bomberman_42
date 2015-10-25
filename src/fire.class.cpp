#include <fire.class.hpp>

Fire::~Fire( void ) {}

Fire::Fire( float x, float y, int status, int model ) : Entity( FIRE, 0, x, y, status ) {
	this->model = model;
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((int)(*it)->pos_x == (int)x && (int)(*it)->pos_y == (int)y
			&& ((*it)->type == ENEMY || (*it)->type == BOSS || (*it)->type == PLAYER))
			(*it)->take_damage();	
		it++;
	}
}
