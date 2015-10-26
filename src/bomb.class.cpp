#include <bomb.class.hpp>
#include <fire.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( float x, float y, int status, int model ) : Entity( BOMB, 0, x, y, status ) {
	this->model = model;
	this->timer = 180;
}

void	Bomb::damage_entity(int x, int y ) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((int)(*it)->pos_x == (int)x && (int)(*it)->pos_y == (int)y
			&& ((*it)->type == ENEMY || (*it)->type == BOSS || (*it)->type == PLAYER))
			(*it)->take_damage();
		it++;
	}
}

void	Bomb::blast_case(int y, int x) {
	std::cout << "blast_case " << x << " " << y << std::endl;
	if (main_event->map[y][x]->type == WALL) {
		if (main_event->map[y][x]->status == WALL_HP_4)
			main_event->map[y][x]->status = WALL_HP_3;
		else if (main_event->map[y][x]->status == WALL_HP_3)
			main_event->map[y][x]->status = WALL_HP_2;
		else if (main_event->map[y][x]->status == WALL_HP_2)
			main_event->map[y][x]->status = WALL_HP_1;
		else if (main_event->map[y][x]->status == WALL_HP_1) {
			delete main_event->map[y][x];
			// main_event->map[y][x] = main_event->create_empty(x, y);
			main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x + 0.5, (float)y + 0.5, FIRE_2);
			damage_entity(x, y);
		}
	}
	else if (main_event->map[y][x]->type == BOMB)
		static_cast<Bomb*>(main_event->map[y][x])->detonate();
	else if (main_event->map[y][x]->type == EMPTY) {
		delete main_event->map[y][x];
		main_event->map[y][x] = main_event->create_fire(FIRE_2, (float)x + 0.5, (float)y + 0.5, FIRE_2);
		damage_entity(x, y);
	}
	else if (main_event->map[y][x]->type == FIRE)
		main_event->map[y][x]->status = FIRE_2;
		damage_entity(x, y);
}

void	Bomb::detonate( void ) {
	int i = 0;
	std::cout << "bomb explode in " << (int)this->pos_x << " " << (int)this->pos_y << std::endl;
	delete main_event->map[(int)this->pos_y][(int)this->pos_x];
	main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
	damage_entity((int)this->pos_x ,(int)this->pos_y);
	// main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_fire(FIRE_2, (int)this->pos_x - 0.5, (int)this->pos_y - 0.5, FIRE_2);

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

void	Bomb::bomb_timer( void ) {
	if (this->timer - 1 > 0) {
		if (this->timer % 9 == 0)
			this->frame++;
		this->timer--;
	}
	else
		detonate();
}
