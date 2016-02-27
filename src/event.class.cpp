// ************************************************************************** //
//   24 Bomb                                                                  //
//   By: rcargou <rcargou@student.42.fr>                  :::      ::::::::   //
//   By: nmohamed <nmohamed@student.42.fr>              :+:      :+:    :+:   //
//   By: adjivas <adjivas@student.42.fr>              +:+ +:+         +:+     //
//   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        //
//   By: jmoiroux <jmoiroux@student.42.fr>        +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/27 14:00:02 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <event.class.hpp>
#include <wall.class.hpp>
#include <bomb.class.hpp>
#include <bonus.class.hpp>
#include <fire.class.hpp>
#include <player.class.hpp>
#include <save.class.hpp>
#include <enemy.class.hpp>
#include <boss.class.hpp>
#include <soundrender.class.hpp>
#include <map_event.class.hpp>
#include <Menu.class.hpp>
#include <mapparser.class.hpp>
#include <globject.class.hpp> // pour la variable mapX_size

Event::Event( void ) : run(true), coop(false), actual_level(1), multi(2) {
    this->map = NULL;
    this->gen_level = false;
    this->option_arcade = false;
    this->option_resolution = RESOLUTION_NOT_SET;
    this->actual_resolution = RESOLUTION_NOT_SET;
    this->full_screen = false;
    this->option_ia_kamikaze = false;
    this->game_pause = false;
    this->draw_winner_multi = -1;
    this->draw_winner_campaign = -1;
    this->draw_lose_campaign = -1;
    this->draw_end_campaign = -1;
    srand(time(NULL));
}

Event::~Event( void ) {}

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

// FUITE START
    std::list<Entity *>::iterator it = main_event->char_list.begin();
    std::list<Entity *>::iterator end = main_event->char_list.end();
    while (it != end) {
        delete *it;
        main_event->char_list.erase(it); // delete this ?
        it = main_event->char_list.begin();
        end = main_event->char_list.end();
    }
    main_event->char_list.clear();
// FUITE END
}

void	Event::make_new_game( int new_level ) {
	char map_name[64] = {0};


	this->joystick->reset_key_pressed();
	this->live_player[0] = true;
	this->live_player[1] = true;
	this->live_player[2] = true;
	this->live_player[3] = true;
	this->live_player[4] = true;

	if (this->game_playing == true) {
		this->free_game();
	}
		main_event->game_pause = false;
		Entity::autoincrement = 0;
	// fill_border_map();
	if (this->joystick->test == 1) {
		sprintf(map_name, "assets/map/test/test1.ntm");
		this->map = Mapparser::map_from_file(map_name);
		return ;
	}
	if (this->intro_map == true) {
		sprintf(map_name, "assets/map/intro/intro_launch.ntm");
		this->map = Mapparser::map_from_file(map_name);
		return ;
	}

	if (this->multi > 0) {
		if (this->gen_level == false) {
			sprintf(map_name, "assets/map/multiplayer/multi_%d.ntm", main_event->multi);
			this->map = Mapparser::map_from_file(map_name);
		}
		else
			gen_level_multi(this->actual_level, this->multi);
	}
	else if (this->arena > 0) {
		if (this->gen_level == false) {
			sprintf(map_name, "assets/map/arena/arena_%d.ntm", main_event->arena);
			this->map = Mapparser::map_from_file(map_name);
		}
		else
			gen_level_arena(this->actual_level, main_event->arena);
	}
	else {
		this->actual_level += new_level;
		if (this->actual_level > 9)
			this->actual_level = 1;
		main_event->save_config->save_level(this->actual_level);
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
        if (1 == this->actual_level || 4 == this->actual_level || 7 == this->actual_level)
            main_event->soundrender->playMusic("music");
        else if (2 == this->actual_level || 5 == this->actual_level || 8 == this->actual_level)
            main_event->soundrender->playMusic("music_2");
        else if (3 == this->actual_level || 6 == this->actual_level || 9 == this->actual_level)
            main_event->soundrender->playMusic("music_boss");
	}
    Map_event::init_clock_at_game_start();
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
		else if (strcmp(av[i], "-kamikaze") == 0)
			this->option_ia_kamikaze = true;
		else if (strcmp(av[i], "-2560") == 0) {
			this->option_resolution = RESOLUTION_2560;
            this->actual_resolution = RESOLUTION_2560;
        }
		else if (strcmp(av[i], "-1920") == 0) {
			this->option_resolution = RESOLUTION_1920;
            this->actual_resolution = RESOLUTION_1920;
        }
		else if (strcmp(av[i], "-1600") == 0) {
			this->option_resolution = RESOLUTION_1600;
            this->actual_resolution = RESOLUTION_1600;
        }
        else if (strcmp(av[i], "-1280") == 0) {
            this->option_resolution = RESOLUTION_1280;
            this->actual_resolution = RESOLUTION_1280;
        }
		else if (strcmp(av[i], "-800") == 0) {
			this->option_resolution = RESOLUTION_800;
            this->actual_resolution = RESOLUTION_800;
        }
		i++;
	}
    if (this->option_resolution == RESOLUTION_NOT_SET) {
        this->option_resolution = main_event->save_config->global_config.windowed_width;
        this->actual_resolution = this->option_resolution;
    }
    main_event->full_screen = main_event->save_config->global_config.video_fullscreen;
}

int rand_range(int min, int max) {
	float tmp;

	tmp = rand();
	tmp /= RAND_MAX;
	tmp *= max;
	return (tmp + min);
}

void	Event::gen_obstacle(int difficulty) {
	int block = ((globject::mapX_size - 2) * (globject::mapY_size - 2));
	int tmpx = 0, tmpy = 0;

	while (block >= 0) {
		tmpx = 1 + (rand() % (globject::mapX_size - 2));
		tmpy = 1 + (rand() % (globject::mapY_size - 2));
		if (check_coord(1, (float)tmpx, (float)tmpy) == true) {
			delete this->map[tmpy][tmpx];
            this->map[tmpy][tmpx] = NULL;
			if (rand() % 20 <= 2)
				this->map[tmpy][tmpx] = Factory::create_wall(WALL_INDESTRUCTIBLE, (float)tmpx, (float)tmpy, WALL_INDESTRUCTIBLE);
			else
				this->map[tmpy][tmpx] = Factory::create_wall(rand_range(WALL_HP_1, 1 + difficulty), (float)tmpx, (float)tmpy, WALL_HP_1);
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
	int tmpx = 0, tmpy = 0;
	int p_x = 2 + (rand() % (globject::mapX_size - 4));
	int p_y = 2 + (rand() % (globject::mapY_size - 4));
	boss = (boss > 0) ? 0 : 1;
	fill_border_map();
	this->char_list.push_back(Factory::create_player(0, (float)p_x, (float)p_y, PLAYER1)); // change model
	if (coop == true) {
		p_x = 2 + (rand() % (globject::mapX_size - 4));
		p_y = 2 + (rand() % (globject::mapY_size - 4));
		while (check_coord(0, (float)p_x, (float)p_y) != true) {
			p_x = 2 + (rand() % (globject::mapX_size - 4));
			p_y = 2 + (rand() % (globject::mapY_size - 4));
			}
			this->char_list.push_back(Factory::create_player(0, (float)p_x, (float)p_y, PLAYER2)); // change model
	}

	int i = 0;
	while (i < (level % 3) + boss) {
		tmpx = 2 + (rand() % (globject::mapX_size - 4));
		tmpy = 2 + (rand() % (globject::mapY_size - 4));
		if (check_coord(0, (float)tmpx, (float)tmpy) == true) {
			printf("yes\n");
			if (boss == 1)
				this->char_list.push_back(Factory::create_boss(0, (float)tmpx, (float)tmpy, BOSS_A, BOSS_A)); // change model
			else
				this->char_list.push_back(Factory::create_enemy(0, (float)tmpx, (float)tmpy, ENEMY1)); // change model
			i++;
		}
	}
	gen_obstacle((level / 3));
}

void	Event::gen_level_multi(int level, int coop) {
	int i = 0;

	fill_border_map();
	while (i < coop) {
		int p_x = 2 + (rand() % (globject::mapX_size - 4));
		int p_y = 2 + (rand() % (globject::mapY_size - 4));
		if (check_coord(0, (float)p_x, (float)p_y) == true) {
			this->char_list.push_back(Factory::create_player(0, (float)p_x, (float)p_y, PLAYER1 + i)); // change model
			i++;
		}
	}
	gen_obstacle((level / 3));
}

void	Event::gen_level_arena(int level, int coop) {
	int i = 0, tmpx = 0, tmpy = 0;

	fill_border_map();
	while (i < coop) {
		int p_x = 2 + (rand() % (globject::mapX_size - 4));
		int p_y = 2 + (rand() % (globject::mapY_size - 4));
		if (check_coord(0, (float)p_x, (float)p_y) == true) {
			this->char_list.push_back(Factory::create_player(0, (float)p_x, (float)p_y, PLAYER1 + i));
			i++;
		}
	}
	tmpx = 2 + (rand() % (globject::mapX_size - 4));
	tmpy = 2 + (rand() % (globject::mapY_size - 4));
	while (check_coord(0, (float)tmpx, (float)tmpy) != true) {
		tmpx = 2 + (rand() % (globject::mapX_size - 4));
		tmpy = 2 + (rand() % (globject::mapY_size - 4));
	}
	this->char_list.push_back(Factory::create_boss(0, (float)tmpx, (float)tmpy, BOSS_A, BOSS_A));
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
    main_event->w_log("Event Init");
	this->ac = ac;
	this->av = av;
	parse_command(ac, av);
    srand(clock());
    globject::init(800, 600);
    if (TTF_Init() != 0){
        main_event->w_error("TTF_init initialization error ");
        throw std::exception();
    }
    main_event->joystick->load_config();
    main_event->save_config->load_level();
    main_event->mode_menu = true;
    main_event->menu->init();
    main_event->menu->introstart = false;
    main_event->soundrender->load_files();
    main_event->soundrender->playSound("startup");
    main_event->menu->main_loop();
}

void	Event::exit_free( void ) {	// free here
	this->event_running = false;
	// FREE menu
	if (NULL != this->menu) {
		this->w_log("Delete menu");
		delete this->menu;
        this->menu = NULL;
	}
	if (NULL != this->soundrender) {
		this->w_log("Delete soundrender");
		delete this->soundrender;
        this->soundrender = NULL;
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

void	Event::player_move(int model, int dir) {
	if (this->game_pause == true)
		return ;
	std::list<Entity *>::iterator it = this->char_list.begin();
	std::list<Entity *>::iterator end = this->char_list.end();

	while (it != end) {
		if (this->live_player[model - PLAYER1] == false)
			return ;
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

	while (y < globject::mapY_size) {
		x = 0;
		while (x < globject::mapX_size) {
            if (this->map[y][x] == NULL) {
                x++;
                continue;
            }
            else {
    			if (this->map[y][x]->type == BOMB)
    				static_cast<Bomb*>(main_event->map[y][x])->bomb_timer();
    			if (this->map[y][x]->type == FIRE)
    				static_cast<Fire*>(main_event->map[y][x])->fire_timer();
    			x++;
            }
		}
		y++;
	}
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
				this->map[y][x] = Factory::create_wall(WALL_INDESTRUCTIBLE, (float)x, (float)y, WALL_INDESTRUCTIBLE);
				if (this->map[y][x] == NULL) {
					this->w_error("fill_border_map:: this->map[y][x] Malloc error");
					throw std::exception();
				}
			}
			else
				this->map[y][x] = Factory::create_empty((int)x, (int)y);
			x++;
		}
		y++;
	}
}
