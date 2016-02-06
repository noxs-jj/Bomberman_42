#include <event.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <bonus.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>
#include <soundrender.class.hpp>
#include <Menu.class.hpp>
#include <mapparser.class.hpp>
#include <globject.class.hpp> // pour la variable mapX_size

Event::Event( void ) : run(true), coop(false), actual_level(1), multi(2) {
	this->map = NULL;
	this->gen_level = false;
	this->option_arcade = false;
	this->option_resolution = RESOLUTION_NOT_SET;
	this->game_pause = false;
	this->draw_winner_multi = -1;
	this->draw_winner_campaign = -1;
	this->draw_lose_campaign = -1;
	this->draw_end_campaign = -1;
	srand(time(NULL));
}

Event::Event( Event const & src ) { *this = src; }

Event & Event::operator=( Event const & rhs ) {
	if (this != &rhs) {}
	return (*this);
}

Event::~Event( void ) {
	// delete this->soundrender;
}

void 	Event::free_game( void ) {
	int x, y = 0;

	while (y < globject::mapY_size) {
		x = 0;
		while (x < globject::mapX_size) {
			delete this->map[y][x];
			x++;
		}
		y++;
	}

	while (this->char_list.empty() == false) {
		this->char_list.pop_front();
	}
}

void	Event::make_new_game( int new_level ) {
	char map_name[64] = {0};

	this->live_player[0] = true;
	this->live_player[1] = true;
	this->live_player[2] = true;
	this->live_player[3] = true;
	this->live_player[4] = true;

	if (this->game_playing == true) {
		std::cout << "        this->game_playing == true FREE AOLD MAP DEBUGG" << std::endl;
		this->free_game();
	}
		main_event->game_pause = false;
		Entity::autoincrement = 0;
	fill_border_map();
	if (this->joystick->test == 1) {
		sprintf(map_name, "assets/map/test/test1.ntm");
		this->map = Mapparser::map_from_file(map_name);
		return ;
	}
	this->actual_level += new_level;
	if (this->actual_level > 9)
		this->actual_level = 1;
	std::cout << "new wall level " << this->actual_level << std::endl;
	if (this->multi > 0) {
		std::cout << "this->multi > 0" << std::endl;
		// gen_level_multi(this->actual_level, this->multi);
		if (this->gen_level == false) {
			sprintf(map_name, "assets/map/multiplayer/multi_%d.ntm", main_event->multi);
			this->map = Mapparser::map_from_file(map_name);
		}
		else
			gen_level_multi(this->actual_level, this->multi);
	}
	else if (this->arena > 0) {
		std::cout << "this->arena > 0" << std::endl;
		// gen_level_multi(this->actual_level, this->multi);
		if (this->gen_level == false) {
			sprintf(map_name, "assets/map/arena/arena_%d.ntm", main_event->arena);
			this->map = Mapparser::map_from_file(map_name);
		}
		else
			gen_level_arena(this->actual_level, this->multi);
	}
	else {
		std::cout << "this->multi > 0 else " << this->ac << std::endl;
		// gen_level_campaign(this->actual_level, this->actual_level % 3, this->coop);
		if (this->gen_level == false && main_event->coop > 0) {
			sprintf(map_name, "assets/map/story/story_coop_%d.ntm", main_event->actual_level);
			this->map = Mapparser::map_from_file(map_name);
		}
		else if (this->gen_level == false && main_event->coop == 0) {
			sprintf(map_name, "assets/map/story/story_%d.ntm", main_event->actual_level);
			this->map = Mapparser::map_from_file(map_name);
		}
		else {
			gen_level_campaign(this->actual_level, this->actual_level % 3, this->coop);
		}
	}
		// main_event->print_map(); // DEBUGG
}

void Event::cheat_stats( void ) {
	std::list<Entity *>::iterator it = main_event->char_list.begin();
	std::list<Entity *>::iterator end = main_event->char_list.end();

	while (it != end) {
		if ((*it)->type == PLAYER) {
				(*it)->bomb_nbr = 99;
				(*it)->blast_radius = 100;
				(*it)->remote = true;
				(*it)->remote_nbr = 99;
				(*it)->kick_bomb = true;
			}
		it++;
	}
}


void	Event::parse_command(int ac, char **av) {
	int	i = 0;

	while ( i < ac ) {
		if (strcmp(av[i], "-log") == 0)
			ft42::logg = true;
		else if (strcmp(av[i], "-gen") == 0)
			this->gen_level = true;
		else if (strcmp(av[i], "-arcade") == 0)
			this->option_arcade = true;
		else if (strcmp(av[i], "-2560") == 0)
			this->option_resolution = RESOLUTION_2560;
		else if (strcmp(av[i], "-1920") == 0)
			this->option_resolution = RESOLUTION_1920;
		else if (strcmp(av[i], "-1600") == 0)
			this->option_resolution = RESOLUTION_1600;
		i++;
	}
}

int rand_range(int min, int max) {
	float tmp;

	tmp = rand();
	tmp /= RAND_MAX;
	tmp *= max;
	return (tmp + min);
}

void	Event::gen_obstacle(int difficulty) {
	std::cout << difficulty << std::endl;
	int block = ((globject::mapX_size - 2) * (globject::mapY_size - 2));
	int tmpx = 0, tmpy = 0;

	while (block >= 0) {
		tmpx = 1 + (rand() % (globject::mapX_size - 2));
		tmpy = 1 + (rand() % (globject::mapY_size - 2));
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

void	Event::gen_level_campaign(int level, int boss, bool coop) {
	std::cout << "gen_level_campaign " << std::endl;
	int tmpx = 0, tmpy = 0;
	int p_x = 2 + (rand() % (globject::mapX_size - 4));
	int p_y = 2 + (rand() % (globject::mapY_size - 4));
	boss = (boss > 0) ? 0 : 1;

	this->char_list.push_back(create_player(0, (float)p_x, (float)p_y, PLAYER1)); // change model
	std::cout << "new bomberman in " << p_x << ":" << p_y << std::endl;
	if (coop == true) {
		p_x = 2 + (rand() % (globject::mapX_size - 4));
		p_y = 2 + (rand() % (globject::mapY_size - 4));
		while (check_coord(0, (float)p_x, (float)p_y) != true) {
			p_x = 2 + (rand() % (globject::mapX_size - 4));
			p_y = 2 + (rand() % (globject::mapY_size - 4));
			}
			this->char_list.push_back(create_player(0, (float)p_x, (float)p_y, PLAYER2)); // change model
			std::cout << "new bomberman in " << p_x << ":" << p_y << std::endl;
	}

	// delete this->map[p_y][p_x];

	int i = 0;
	while (i < (level % 3) + boss) {
		tmpx = 2 + (rand() % (globject::mapX_size - 4));
		tmpy = 2 + (rand() % (globject::mapY_size - 4));
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

void	Event::gen_level_multi(int level, int coop) {
	int i = 0;

	while (i < coop) {
		int p_x = 2 + (rand() % (globject::mapX_size - 4));
		int p_y = 2 + (rand() % (globject::mapY_size - 4));
		if (check_coord(0, (float)p_x, (float)p_y) == true) {
			this->char_list.push_back(create_player(0, (float)p_x, (float)p_y, PLAYER1 + i)); // change model
			i++;
		}
	}
	gen_obstacle((level / 3));
}

void	Event::gen_level_arena(int level, int coop) {
	int i = 0, tmpx = 0, tmpy = 0;

	while (i < coop) {
		int p_x = 2 + (rand() % (globject::mapX_size - 4));
		int p_y = 2 + (rand() % (globject::mapY_size - 4));
		if (check_coord(0, (float)p_x, (float)p_y) == true) {
			this->char_list.push_back(create_player(0, (float)p_x, (float)p_y, PLAYER1 + i));
			i++;
		}
	}
	tmpx = 2 + (rand() % (globject::mapX_size - 4));
	tmpy = 2 + (rand() % (globject::mapY_size - 4));
	while (check_coord(0, (float)tmpx, (float)tmpy) != true) {
		tmpx = 2 + (rand() % (globject::mapX_size - 4));
		tmpy = 2 + (rand() % (globject::mapY_size - 4));
	}
	this->char_list.push_back(create_boss(0, (float)tmpx, (float)tmpy, BOSS_A, BOSS_A));
	gen_obstacle((level / 3));
}

void	Event::print_map( void ) {
	int y = 0, x;
	std::cout << "print_map" << std::endl;
	while (y < globject::mapY_size) {
		x = 0;
		while (x < globject::mapX_size) {
			std::cout << this->map[y][x]->type << " ";
			x++;
		}
		std::cout << std::endl;
		y++;
	}
	std::cout << "print_map END" << std::endl;
}

void	Event::init( int ac, char **av ) {
	this->ac = ac;
	this->av = av;

	parse_command(ac, av);
}

void	Event::exit_free( void ) {	// free here
	this->event_running = false;
	// FREE menu
	if (NULL != this->menu) {
		this->w_full("Delete menu");
		delete this->menu;
	}
	if (NULL != this->soundrender) {
		this->w_full("Delete soundrender");
		delete this->soundrender;
	}

	this->w_log("Event::exit_free ==> End of free Bomberman");
	this->event_running = false;
	this->mode_menu = false;

	if (this->game_playing == true)
		this->free_game();
}

void	Event::lauchGame( void ) {
	// Loop Game
	while (this->run == true) {

	}
}

Wall *	Event::create_wall(int status, float x, float y, int model) {
	Wall * wall = new Wall(x, y, status, model);
	if (wall == NULL) {
		this->w_full("create_wall:: wall Malloc error");
		throw std::exception();
	}

	return wall;
}

Bonus *	Event::create_bonus(int status, float x, float y, int model) {
	Bonus * bonus = new Bonus(x, y, status, model);
	if (bonus == NULL) {
		this->w_full("create_bonus:: bonus Malloc error");
		throw std::exception();
	}

	return bonus;
}

Bomb *	Event::create_bomb(int status, float x, float y, int model, int id) {
	Bomb * bomb = new Bomb(x, y, status, model, id);
	if (bomb == NULL) {
		this->w_full("create_bomb:: bomb Malloc error");
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

void	Event::player_move(int model, int dir) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if ((*it)->model == model)
			(*it)->move(dir);
		it++;
	}
}

void Event::remote_detonate( int model ) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if ((*it)->model == model) {
			if ((*it)->remote == false)
				return ;

			std::list<Entity *>::iterator it_lst = (*it)->remote_lst.begin();
			std::list<Entity *>::iterator end_lst = (*it)->remote_lst.end();

			while (it_lst != end_lst) {
				if (this->map[(int)(*it_lst)->pos_y][(int)(*it_lst)->pos_x]->model == BOMB_REMOTE) {
					static_cast<Bomb*>(this->map[(int)(*it_lst)->pos_y][(int)(*it_lst)->pos_x])->detonate();
					if (this->live_player[model - PLAYER1] == false)
						return ;
					it_lst = (*it)->remote_lst.begin();
					end_lst = (*it)->remote_lst.end();
				}
				else
					it_lst++;
				if ((*it)->remote_lst.empty() || (*it)->remote_lst.size() <= 0) {
					return ;

				}
			}
			(*it)->remote_lst.clear();
			return ;
		}
		it++;
	}
}

void Event::remote_put( int model ) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if ((*it)->model == model) {
			if ((*it)->remote == false)
				return ;

			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY && (*it)->remote_nbr > 0) {
				(*it)->remote_nbr--;
				(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB_REMOTE, (*it)->blast_radius, (*it)->id);
				(*it)->remote_lst.push_back(this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]);
				// (*it)->remote_lst.push_back(create_bomb(BOMB_SEC_3, (int)(*it)->pos_x + 0.5, (int)(*it)->pos_y + 0.5, BOMB_REMOTE, (*it)->id));
			}
			return ;
		}
		it++;
	}
}

void	Event::player_bomb(int model) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if ((*it)->model == model) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				if ((*it)->bomb_nbr > 0) {
					(*it)->bomb_nbr--;
					(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, (*it)->bomb_model, (*it)->blast_radius, (*it)->id);
				}
				return ;
			}
		}
		it++;
	}
}

void	Event::ia_bomb(int id) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if ((*it)->id == id) {
			if (this->map[(int)(*it)->pos_y][(int)(*it)->pos_x]->type == EMPTY) {
				if ((*it)->bomb_nbr > 0) {
					(*it)->bomb_nbr--;
					(*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, (*it)->bomb_model, (*it)->blast_radius, id);
				}
				return ;
			}
		}
		it++;
	}
}

void	Event::dec_timer( void ) {
	int x, y = 0;
	std::cout << "dec_timer 00" << std::endl;

	while (y < globject::mapY_size) {
		x = 0;
		while (x < globject::mapX_size) {
			if (this->map[y][x]->type == BOMB)
				static_cast<Bomb*>(main_event->map[y][x])->bomb_timer();
			if (this->map[y][x]->type == FIRE)
				static_cast<Fire*>(main_event->map[y][x])->fire_timer();
			x++;
		}
		y++;
	}
	std::cout << "dec_timer 01" << std::endl;
}

void	Event::fill_border_map(void) {
	int 	y = 0,
			x = 0;

	this->map = (Entity ***)std::malloc(sizeof(Entity **) * globject::mapY_size);
	if (this->map == NULL) {
		this->w_error("fill_border_map:: this->map Malloc error");
		throw std::exception();
	}

	while (y < globject::mapY_size) {
		this->map[y] = NULL;
		this->map[y] = (Entity **)std::malloc(sizeof(Entity *) * globject::mapX_size);
		if (this->map[y] == NULL) {
			this->w_error("fill_border_map:: this->map[y] Malloc error");
			throw std::exception();
		}
		x = 0;
		while (x < globject::mapX_size) {
			if (y == 0 || y == globject::mapY_size - 1 || x == 0 || x == globject::mapX_size - 1) {
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
		if (!(
				   this->soundrender->loadSound("blast", "assets/sound/blast.wav")
				&& this->soundrender->loadSound("startup", "assets/sound/pause.wav")
				&& this->soundrender->loadSound("die", "assets/sound/PLAYER_OUT.wav")
				&& this->soundrender->loadSound("ready", "assets/sound/readymegaman.wav")
				&& this->soundrender->loadSound("menu2", "assets/sound/megamenu2.wav")
				&& this->soundrender->loadSound("menu1", "assets/sound/menu1.wav")
				&& this->soundrender->loadSound("timebomb", "assets/sound/timebomb.wav")
				&& this->soundrender->loadSound("bombmove", "assets/sound/bombmove.wav")
				&& this->soundrender->loadSound("pause", "assets/sound/pause.wav")
				// music
				&& this->soundrender->loadMusic("victory", "assets/sound/victory.wav")
				&& this->soundrender->loadMusic("victory_multiplayer", "assets/sound/victory_multiplayer.wav")
				&& this->soundrender->loadMusic("victory_final", "assets/sound/victory_finalfantasy.wav")
				&& this->soundrender->loadMusic("music", "assets/sound/bgm.wav")
			)) {
			w_full("loadsound error");
			throw std::exception();
		}
		w_full("sounds loaded");
	} else {
		w_full("soundrender = NULL");
		throw std::exception();
	}
}
