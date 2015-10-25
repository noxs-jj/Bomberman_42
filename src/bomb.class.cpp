#include <bomb.class.hpp>
#include <fire.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( float x, float y, int status, int model ) : Entity( BOMB, 0, x, y, status ) {
	this->model = model;
}

void	Bomb::blast_case(int x, int y) {
	if (main_event->map[y][x]->type == WALL) {
		if (main_event->map[y][x]->status == WALL_HP_4)
			main_event->map[y][x]->status = WALL_HP_3;
		else if (main_event->map[y][x]->status == WALL_HP_3)
			main_event->map[y][x]->status = WALL_HP_2;
		else if (main_event->map[y][x]->status == WALL_HP_2)
			main_event->map[y][x]->status = WALL_HP_1;
		else if (main_event->map[y][x]->status == WALL_HP_1) {
			delete main_event->map[y][x];
			main_event->map[y][x] = main_event->create_empty(x, y);
		}
	}
	else if (main_event->map[y][x]->type == BOMB)
		static_cast<Bomb*>(main_event->map[y][x])->detonate();
	else if (main_event->map[y][x]->type == EMPTY) {
		delete main_event->map[y][x];
		main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x, (float)y, FIRE_2);
	}
	else if (main_event->map[y][x]->type == FIRE)
		main_event->map[y][x]->status = FIRE_2;
}

void	Bomb::detonate( void ) {
	int i = 1;

	delete main_event->map[(int)this->pos_y][(int)this->pos_x];
	main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_fire(FIRE_2, this->pos_x, this->pos_y, FIRE_2);

	while (i <= this->blast_radius) {
		if (check_coord_exist((int)(this->pos_y - i), (int)(this->pos_x)) == true)
			blast_case((int)(this->pos_y - i), (int)this->pos_x);

		if (check_coord_exist((int)(this->pos_y + i), (int)(this->pos_x)) == true)
			blast_case((int)(this->pos_y + i), (int)this->pos_x);

		if (check_coord_exist((int)(this->pos_x - i), (int)(this->pos_y)) == true)
			blast_case((int)this->pos_y, (int)(this->pos_x - i));

		if (check_coord_exist((int)(this->pos_x + i), (int)(this->pos_y)) == true)
			blast_case((int)this->pos_y, (int)(this->pos_x + i));

		i++;
	}
}