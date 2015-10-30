#include <event.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>
#include <soundrender.class.hpp>

Event::Event( void ) : run(true) {
	this->map = NULL;
	this->load_sounds();
	srand(time(NULL));
}

Event::Event( Event const & src ) { *this = src; }

Event & Event::operator=( Event const & rhs ) {
	if (this != &rhs) {}
	return (*this);
}

Event::~Event( void ) {
	delete this->soundrender;
}

void	Event::parse_command(int ac, char **av) {
	int i = 0;

	while ( i < ac ) {
		if ( 0 == strcmp(av[i], "-log") )
			ft42::logg = true;
		i++;
	}
}

int rand_range(int min, int max)
{
	float tmp;

	tmp = rand();
	tmp /= RAND_MAX;
	tmp *= max;
	return (tmp + min);
}

void	Event::gen_obstacle(int difficulty) {
	std::cout << difficulty << std::endl;
	int block = ((MAP_X_SIZE - 2) * (MAP_Y_SIZE - 2));
	int tmpx = 0, tmpy = 0;

	while (block >= 0) {
		tmpx = 1 + (rand() % (MAP_X_SIZE - 2));
		tmpy = 1 + (rand() % (MAP_Y_SIZE - 2));
		if (check_coord(1, (float)tmpx, (float)tmpy) == true) {
			delete this->map[tmpy][tmpx];
			if (rand() % 20 <= 2)
				this->map[tmpy][tmpx] = create_wall(WALL_INDESTRUCTIBLE, (float)tmpx, (float)tmpy, WALL_INDESTRUCTIBLE);
			else
				this->map[tmpy][tmpx] = create_wall(rand_range(WALL_HP_1, 1 + difficulty), (float)tmpx, (float)tmpy, WALL_HP_1);
		}
		block--;
	}
}

bool	Event::check_coord(int mode, float x, float y) {
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if (mode == 0 && (int)(*it)->pos_x == (int)x && (int)(*it)->pos_y == (int)y)
			return false;
		else if (mode == 1) {
			if ((int)x >= (int)(*it)->pos_x - 1 && (int)x <= (int)(*it)->pos_x + 1
				&& (int)y >= (int)(*it)->pos_y - 1 && (int)y <= (int)(*it)->pos_y + 1)
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

	this->char_list.push_back(create_player(0, (float)p_x, (float)p_y, PLAYER1)); // change model
	// delete this->map[p_y][p_x];

	int i = 0;
	while (i < (level % 3) + boss) {
		tmpx = 2 + (rand() % (MAP_X_SIZE - 4));
		tmpy = 2 + (rand() % (MAP_Y_SIZE - 4));
		if (check_coord(0, (float)tmpx, (float)tmpy) == true) {
			if (boss == 1)
				this->char_list.push_back(create_boss(0, (float)tmpx, (float)tmpy, BOSS_A, BOSS_A)); // change model
			else
				this->char_list.push_back(create_enemy(0, (float)tmpx, (float)tmpy, ENEMY1)); // change model
			i++;
		}
	}
	gen_obstacle((level / 3));
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
	gen_level(6, 1);
	main_event->print_map(); // DEBUGG
}

void	Event::exit_free( void ) {	// free here

	this->w_log("Event::exit_free ==> End of free gomoku");

}

void	Event::lauchGame( void ) {
	// Loop Game
	while (this->run == true) {

	}
}

Wall *	Event::create_wall(int status, float x, float y, int model) {
	Wall * wall = new Wall(x, y, status, model);
	if (wall == NULL) {
		this->w_error("create_wall:: wall Malloc error");
		throw std::exception();
	}

	return wall;
}

Bomb *	Event::create_bomb(int status, float x, float y, int model) {
	Bomb * bomb = new Bomb(x, y, status, model);
	if (bomb == NULL) {
		this->w_error("create_bomb:: bomb Malloc error");
		throw std::exception();
	}

	return bomb;
}

Fire *	Event::create_fire(int status, float x, float y, int model) {
	Fire * fire = new Fire(x, y, status, model);
	if (fire == NULL) {
		this->w_error("create_fire:: fire Malloc error");
		throw std::exception();
	}

	return fire;
}

Player *	Event::create_player(int status, float x, float y, int model) {
	Player * player = new Player(x, y, status, model);
	if (player == NULL) {
		this->w_error("create_player:: player Malloc error");
		throw std::exception();
	}

	return player;
}

Enemy *	Event::create_enemy(int status, float x, float y, int model) {
	Enemy * enemy = new Enemy(x, y, status, model);
	if (enemy == NULL) {
		this->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}

	return enemy;
}

Boss *	Event::create_boss(int status, float x, float y, int name, int model) {
	Boss * boss = new Boss(x, y, status, name, model);
	if (boss == NULL) {
		this->w_error("create_enemy:: enemy Malloc error");
		throw std::exception();
	}

	return boss;
}

Entity * Event::create_empty(int x, int y) {
	Entity * ent = new Entity(EMPTY, (float)x, (float)y, NO_STATUS);
	ent->model = -1;
	if (ent == NULL) {
		this->w_error("create_empty:: enemy Malloc error");
		throw std::exception();
	}

	return ent;
}

void	Event::player_move(int id, int dir) {
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();
	(void)id;

	while (it != end) {
		if ((*it)->type == PLAYER && (*it)->model == PLAYER1) {
			(*it)->move(dir);
		}
		else if ((*it)->type == PLAYER && (*it)->model == PLAYER2) {
			(*it)->move(dir);
		}
		else if ((*it)->type == PLAYER && (*it)->model == PLAYER3) {
			(*it)->move(dir);
		}
		else if ((*it)->type == PLAYER && (*it)->model == PLAYER4) {
			(*it)->move(dir);
		}
		it++;
	}
}

void	Event::player_bomb(int id) {
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();
	(void)id;

	while (it != end) {
		if ((*it)->type == PLAYER && (*it)->model == PLAYER1) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
				return ;
			}
		}
		if ((*it)->type == PLAYER && (*it)->model == PLAYER2) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
				return ;
			}
		}
		if ((*it)->type == PLAYER && (*it)->model == PLAYER3) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
				return ;
			}
		}
		if ((*it)->type == PLAYER && (*it)->model == PLAYER4) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
				return ;
			}
		}
		it++;
	}
}

void	Event::dec_timer( void ) {
	int x, y = 0;

	while (y < MAP_Y_SIZE) {
		x = 0;
		while (x < MAP_X_SIZE) {
			if (this->map[y][x]->type == BOMB)
				static_cast<Bomb*>(main_event->map[y][x])->bomb_timer();
			if (this->map[y][x]->type == FIRE)
				static_cast<Fire*>(main_event->map[y][x])->fire_timer();
			x++;
		}
		y++;
	}
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
				this->map[y][x] = create_wall(WALL_INDESTRUCTIBLE, (float)x, (float)y, WALL_INDESTRUCTIBLE);
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

void	Event::load_sounds(void) {
	this->soundrender = new SoundRender();
	if (this->soundrender != NULL) {
		if (!this->soundrender->loadSound("blast", "sound/blast.wav")) {
			std::cout << "loadsound error" << std::endl;
		}
		std::cout << "sounds loaded" << std::endl;
	} else {
		std::cout << "soundrender == NULL" << std::endl;
	}
}

void    Event::play_sound(std::string soundName) {
	if (this->soundrender != NULL) {
		this->soundrender->playSound(soundName);
		std::cout << "sound " << soundName << " played" << std::endl;
	} else {
		std::cout << "soundrender == NULL" << std::endl;
	}
}
