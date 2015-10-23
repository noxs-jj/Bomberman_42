#include <event.class.hpp>

Event::Event( void ) : run(true) {
	this->map = NULL;
	srand(time(NULL));
}

Event::Event( Event const & src ) { *this = src; }

Event & Event::operator=( Event const & rhs ) {
	if (this != &rhs) {}
	return (*this);
}

Event::~Event( void ) {}

void	Event::parse_command(int ac, char **av) {
	int i = 0;

	while ( i < ac ) {
		if ( 0 == strcmp(av[i], "-log") )
			ft42::logg = true;
		i++;
	}
}

void	Event::gen_obstacle(int difficulty) {
	int block = ((MAP_X_SIZE - 2) * (MAP_Y_SIZE - 2));
	int tmpx = 0, tmpy = 0;

	while (block >= 0) {
		tmpx = 2 + (rand() % (MAP_X_SIZE - 4));
		tmpy = 2 + (rand() % (MAP_Y_SIZE - 4));
		if (check_coord(1, (float)tmpx, (float)tmpy) == true) {
			delete this->map[tmpy][tmpx];
			this->map[tmpy][tmpx] = create_wall(WALL_HP_1 + difficulty, (float)tmpx, (float)tmpy);
		}
		block--;
	}
}

bool	Event::check_coord(int mode, float x, float y) {
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if (mode == 0 && (*it)->pos_x == x && (*it)->pos_y == y)
			return false;
		else if (mode == 1) {
			if (x >= (*it)->pos_x - 1 && x <= (*it)->pos_x + 1
				&& y >= (*it)->pos_y - 1 && y <= (*it)->pos_y + 1)
				return false;
		}
		it++;
	}
	if (this->map[(int)y][(int)x]->type != EMPTY)
		return false;
	return true;
}

void	Event::gen_level(int level, int boss) {
	int tmpx = 0, tmpy = 0;
	int p_x = 2 + (rand() % (MAP_X_SIZE - 4));
	int p_y = 2 + (rand() % (MAP_Y_SIZE - 4));

	this->char_list.push_back(create_player(0, 0, (float)p_x, (float)p_y));
	// delete this->map[p_y][p_x];

	int i = 0;
	while (i != level % 3) {
		tmpx = 2 + (rand() % (MAP_X_SIZE - 4));
		tmpy = 2 + (rand() % (MAP_Y_SIZE - 4));
		if (check_coord(0, (float)tmpx, (float)tmpy) == true) {
			if (boss == 1)
				this->char_list.push_back(create_boss(0, (float)tmpx, (float)tmpy, BOSS_A));
			else
				this->char_list.push_back(create_enemy(i, 0, (float)tmpx, (float)tmpy));
			i++;
		}
	}
	gen_obstacle((level % 3));
}

void	Event::print_map( void ) {
	int y = 0, x;
	std::cout << "print_map" << std::endl;
	while (y < MAP_Y_SIZE) {
		x = 0;
		while (x < MAP_X_SIZE) {
			std::cout << this->map[y][x]->type << " ";
			x++;
		}
		std::cout << std::endl;
		y++;
	}
}

void	Event::init( int ac, char **av ) {
	this->parse_command(ac, av);
	fill_border_map();
	gen_level(1, 0);
	// print_map(); // DEBUGG
}

void	Event::exit_free( void ) {	// free here

	this->w_log("Event::exit_free ==> End of free gomoku");

}

void	Event::lauchGame( void ) {
	// Loop Game
	while (this->run == true) {

	}
}

Wall *	Event::create_wall(int status, float x, float y) {
	Wall * wall = new Wall(x, y, status);
	if (wall == NULL) {
		this->w_error("create_wall:: wall Malloc error");
		throw std::exception();
	}

	return wall;
}

Bomb *	Event::create_bomb(int status, float x, float y) {
	Bomb * bomb = new Bomb(x, y, status);
	if (bomb == NULL) {
		this->w_error("create_bomb:: bomb Malloc error");
		throw std::exception();
	}

	return bomb;
}

Fire *	Event::create_fire(int status, float x, float y) {
	Fire * fire = new Fire(x, y, status);
	if (fire == NULL) {
		this->w_error("create_fire:: fire Malloc error");
		throw std::exception();
	}

	return fire;
}

Player *	Event::create_player(int id, int status, float x, float y) {
	Player * player = new Player(id, x, y, status);
	if (player == NULL) {
		this->w_error("create_player:: player Malloc error");
		throw std::exception();
	}

	return player;
}

Enemy *	Event::create_enemy(int id, int status, float x, float y) {
	Enemy * enemy = new Enemy(id, x, y, status);
	if (enemy == NULL) {
		this->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}

	return enemy;
}

Boss *	Event::create_boss(int status, float x, float y, int name) {
	Boss * boss = new Boss(x, y, status, name);
	if (boss == NULL) {
		this->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}

	return boss;
}

Entity * Event::create_empty(int x, int y) {
	Entity * ent = new Entity(EMPTY, 0, (float)x, (float)y, NO_STATUS);
	if (ent == NULL) {
		this->w_error("create_empty:: enemy Malloc error");
		throw std::exception();
	}

	return ent;
}

void	Event::fill_border_map(void) {
	int 	y = 0,
			x = 0;

	this->map = (Entity ***)std::malloc(sizeof(Entity **) * MAP_Y_SIZE);
	if (this->map == NULL) {
		this->w_error("fill_border_map:: this->map Malloc error");
		throw std::exception();
	}

	while (y < MAP_Y_SIZE) {
		this->map[y] = NULL;
		this->map[y] = (Entity **)std::malloc(sizeof(Entity *) * MAP_X_SIZE);
		if (this->map[y] == NULL) {
			this->w_error("fill_border_map:: this->map[y] Malloc error");
			throw std::exception();
		}
		x = 0;
		while (x < MAP_X_SIZE) {
			if (y == 0 || y == MAP_Y_SIZE - 1 || x == 0 || x == MAP_X_SIZE - 1) {
				this->map[y][x] = create_wall(WALL_INDESTRUCTIBLE, (float)x, (float)y);
				if (this->map[y][x] == NULL) {
					this->w_error("fill_border_map:: this->map[y][x] Malloc error");
					throw std::exception();
				}
			}
			else
				this->map[y][x] = create_empty((int)x, (int)y);
			x++;
		}
		y++;
	}
}
