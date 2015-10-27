#include <bomb.class.hpp>
#include <fire.class.hpp>

Bomb::~Bomb( void ) {}

Bomb::Bomb( float x, float y, int status, int model ) : Entity( BOMB, x, y, status ) {
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

int		Bomb::blast_case(int y, int x) {
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
		return (0);
	}
	else if (main_event->map[y][x]->type == FIRE) {
		main_event->map[y][x]->status = FIRE_2;
		damage_entity(x, y);
		return (0);
	}
	return (1);
}

void	Bomb::detonate( void ) {
	int i = 0;
	int dir[4] = {0};
	delete main_event->map[(int)this->pos_y][(int)this->pos_x];
	main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_empty((int)this->pos_x, (int)this->pos_y);
	damage_entity((int)this->pos_x ,(int)this->pos_y);
	// main_event->map[(int)this->pos_y][(int)this->pos_x] = main_event->create_fire(FIRE_2, (int)this->pos_x - 0.5, (int)this->pos_y - 0.5, FIRE_2);

	while (i <= this->blast_radius) {
		if (dir[0] == 0 && check_coord_exist((int)(this->pos_y - i), (int)(this->pos_x)) == true)
			dir[0] = blast_case((int)(this->pos_y - i), (int)this->pos_x);

		if (dir[1] == 0 && check_coord_exist((int)(this->pos_y + i), (int)(this->pos_x)) == true)
			dir[1] = blast_case((int)(this->pos_y + i), (int)this->pos_x);

		if (dir[2] == 0 && check_coord_exist((int)(this->pos_x - i), (int)(this->pos_y)) == true)
			dir[2] = blast_case((int)this->pos_y, (int)(this->pos_x - i));

		if (dir[3] == 0 && check_coord_exist((int)(this->pos_x + i), (int)(this->pos_y)) == true)
			dir[3] = blast_case((int)this->pos_y, (int)(this->pos_x + i));

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
