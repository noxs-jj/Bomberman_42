#include <bonus.class.hpp>
#include <entity.class.hpp>

Bonus::~Bonus( void ) {}

Bonus::Bonus( float x, float y, int status, int model ) : Entity( BONUS, x, y, status ) {
	this->model = model;
}

void	Bonus::affect(Entity *ent) {
	if (this->model == BONUS_POWER_UP)
		ent->blast_radius++;
	else if (this->model == BONUS_PLUS_ONE)
		ent->bomb_nbr++;
	else if (this->model == BONUS_KICK) {
		ent->kick_bomb = true;
		std::cout << "kick bomb get" << std::endl;
	}

	else if (this->model == BONUS_CHANGE)
		ent->bomb_model = BOMB;
}
