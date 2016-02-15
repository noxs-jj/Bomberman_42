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

#include <globject.class.hpp>
#include <bomb.class.hpp>
#include <fire.class.hpp>

globject            globject::_object[100];
SDL_Window          *globject::_displayWindow;
SDL_Renderer        *globject::_displayRenderer;
SDL_RendererInfo    globject::_displayRendererInfo;
GLuint              globject::_progid;
GLuint              globject::_modelMatID;
GLuint              globject::_viewMatID;
GLuint              globject::_keyFrameID;
GLuint              globject::_legPos;
GLfloat             globject::spinx;
GLfloat             globject::spinz;
int                 globject::doIspin;
int                 globject::space = 0; //Change the graphical envirronnement.
int                 globject::mapX_size = 20;
int                 globject::mapY_size = 20;

globject::globject(void) {}

globject::globject(std::string path, GLuint ID, GLfloat zoom) : _ID(ID), _zoom(zoom) {
	int	neg;

	neg = (ID == WALL_HP_1 || ID == FLOOR || ID == WALL_INDESTRUCTIBLE);
	neg = 0;
	parser.parse(path, neg);
	fill_vao();
	_textNumber = parser._textNum;
	load_bmp();
	globject::_object[ID] = *this;
}

globject::~globject(void) {}

void globject::reinit_level(int env) {
	env = env - 1;
	doIspin = 0;
}

void globject::load_bmp() {
    std::string     name;
    std::string     path;
    for (size_t i = 0; i < parser._textNum; i++)
    {
        name = "texture";
        path ="assets/render/textures/";
        if (globject::space)
            path = "assets/render/spacestextures/";
        path += parser._texture[i];
        SDL_Surface *imp = IMG_Load(path.c_str());
        if (imp == NULL) 		{
            std::cerr << "FAILFAIL" << std::endl;
            throw std::exception() ;
        }
        glGenTextures(1, &(_textID[i]));
        glBindTexture(GL_TEXTURE_2D, (_textID[i]));
        if (((_ID >= BOSS_A && _ID <= BOSS_D) \
            || (_ID >= PLAYER && _ID <= PLAYER4) \
            || (_ID >= BOMB_DEFAULT && _ID <= BOMB_WIND) \
            || (_ID >= ENEMY && _ID <= ENEMY5) \
            || _ID == MENU \
            || (globject::space && _ID == MAX_ENUM))) {
            # ifdef linux
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imp->w, imp->h, \
                    0, GL_BGRA,  GL_UNSIGNED_BYTE, imp->pixels);
            # endif
            # ifdef __APPLE__
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imp->w, imp->h, \
                    0, GL_BGRA, GL_UNSIGNED_BYTE, imp->pixels);
            # endif
            }
            else if (_ID == PLAYER5) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imp->w, imp->h, \
                    0, GL_BGRA, GL_UNSIGNED_BYTE, imp->pixels);
            }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imp->w, imp->h, \
                0, GL_BGR, GL_UNSIGNED_BYTE, imp->pixels);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        name += std::to_string(i);
        _textLoc[i] = glGetUniformLocation(globject::_progid, name.c_str());
    }
}

void        globject::resize(int x, int y) {
	SDL_SetWindowSize(globject::_displayWindow, x, y);
	glViewport(0, 0, x, y);
}

void        globject::get_sdl_information() {
    if (SDL_GetCurrentDisplayMode(0, &main_event->sdl_display_mode_info) < 0) {
        main_event->w_full("globject::get_sdl_information() SDL_GetCurrentDisplayMode() failed");
        throw std::exception();
    }
    std::cout << "nativWidth = " << main_event->sdl_display_mode_info.w;
    std::cout << " nativHeight = " << main_event->sdl_display_mode_info.h;
    std::cout << " nativRefreshRate = " << main_event->sdl_display_mode_info.refresh_rate << std::endl;
}

void        globject::set_float_width_height(float *width, float *height) {
    if (RESOLUTION_800 == main_event->option_resolution
            &&main_event->sdl_display_mode_info.w >= 800
            && main_event->sdl_display_mode_info.w >= 600) {
        *width = 800;
        *height = 600;
    }
    else if (RESOLUTION_1280 == main_event->option_resolution \
            && main_event->sdl_display_mode_info.w >= 1280 \
            && main_event->sdl_display_mode_info.w >= 720) {
        *width = 1280;
        *height = 720;
    }
    else if (RESOLUTION_1600 == main_event->option_resolution \
            && main_event->sdl_display_mode_info.w >= 1600 \
            && main_event->sdl_display_mode_info.w >= 900) {
        *width = 1600;
        *height = 900;
    }
    else if (RESOLUTION_1920 == main_event->option_resolution \
            && main_event->sdl_display_mode_info.w >= 1920 \
            && main_event->sdl_display_mode_info.w >= 1080) {
        *width = 1920;
        *height = 1080;
    }
    else if (RESOLUTION_2560 == main_event->option_resolution \
            && main_event->sdl_display_mode_info.w >= 2560 \
            && main_event->sdl_display_mode_info.w >= 1440) {
        *width = 2560;
        *height = 1440;
    }
    else {
        *width = main_event->sdl_display_mode_info.w;
        *height = main_event->sdl_display_mode_info.h;
    }
}

void        globject::init(float sizeX, float sizeY) {
    float   size_x = sizeX;
    float   size_y = sizeY;

	/* Init SDL */
	if (SDL_Init(SDL_INIT_VIDEO \
			| SDL_INIT_AUDIO \
			| SDL_INIT_JOYSTICK \
		) < 0) {
		std::cerr << "globject::init SDL_Init() error = " << SDL_GetError() << std::endl;
		throw std::exception();
	}

    // Added Jean-Jacques get params for Start screen size
    globject::get_sdl_information(); // main_event->sdl_display_mode_info store the information SDL_DisplayMode;
    globject::set_float_width_height(&size_x, &size_y); // modify Width & Height with paramaters or NOT

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    # ifdef linux
        globject::_displayWindow = SDL_CreateWindow( "Bomberman", \
            0, 0, \
            size_x, size_y, \
            SDL_WINDOW_OPENGL \
            | SDL_WINDOW_FULLSCREEN
        );
	# endif
	# ifdef __APPLE__
        if (main_event->full_screen == true) {
            globject::_displayWindow = SDL_CreateWindow( "Bomberman", \
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
                size_x, size_y, \
                SDL_WINDOW_OPENGL \
                | SDL_WINDOW_FULLSCREEN
            );
        }
        else {
            globject::_displayWindow = SDL_CreateWindow( "Bomberman", \
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
                size_x, size_y, \
                SDL_WINDOW_OPENGL \
                | SDL_WINDOW_BORDERLESS
            );
        }
    # endif

	/* Init OpenGL */
	SDL_GLContext glcontext = SDL_GL_CreateContext(globject::_displayWindow);
	if(NULL == glcontext) {
		std::cerr << "SDL_GLContext failed " <<  SDL_GetError() << std::endl;
		throw std::exception();
	}

	# ifdef linux
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if(err != GLEW_OK) {
			std::cerr << "glew failed" << glewGetErrorString(err) << std::endl;
			throw std::exception();
		}
	# endif
    // glClearColor( 0.0f, 0.0f, 0.3f, 0.0f );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glEnable(GL_DEPTH_TEST);
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(globject::_displayWindow);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/* load shaders */
	globject::load_shaders();

	/* load Models */
	globject("assets/render/models/cube.obj", WALL_HP_1, 1);
	globject("assets/render/models/cube1.obj", WALL_HP_2, 1);
	globject("assets/render/models/cube2.obj", WALL_HP_3, 1);
	globject("assets/render/models/cube_floor.obj", FLOOR, 1);
	globject("assets/render/bonus_item/bomb_fire_up.obj", BONUS_POWER_UP, 1); // BONUS_POWER_UP
	globject("assets/render/bonus_item/bomb_plus_one.obj", BONUS_PLUS_ONE, 1); // BONUS_PLUS_ONE
	globject("assets/render/bonus_item/bomb_kick.obj", BONUS_KICK, 1); // BONUS_KICK
	globject("assets/render/bonus_item/bomb_change.obj", BONUS_CHANGE, 1); // BONUS_CHANGE
	globject("assets/render/bonus_item/bomb_remote.obj", BONUS_REMOTE_BOMB, 1); // BONUS_REMOTE_BOMB
	globject("assets/render/bonus_item/move_speed_up.obj", BONUS_SPEED_UP, 1); // BONUS_SPEED_UP
	globject("assets/render/models/rock.obj", WALL_INDESTRUCTIBLE, 1);
    // globject("assets/render/models/Bomberman/Bomberman1.obj", PLAYER, 0.03);
	globject("assets/render/models/Bomberman/Bomberman1.obj", PLAYER1, 0.03);
	globject("assets/render/models/Bomberman/Bomberman2.obj", PLAYER2, 0.03);
	globject("assets/render/models/Bomberman/Bomberman3.obj", PLAYER3, 0.03);
	globject("assets/render/models/Bomberman/Bomberman4.obj", PLAYER4, 0.03);
	globject("assets/render/models/Bomberman/Bomberman5.obj", PLAYER5, 0.03);
	globject("assets/render/enemy/BearGrizzly/ENEMY_Bear_Grizzly1.obj", ENEMY1, 0.3);
	globject("assets/render/enemy/Andlar/Andlar.obj", ENEMY2, 0.04);
	globject("assets/render/enemy/Angol/Angol.obj", ENEMY3, 0.04);
	globject("assets/render/enemy/Boo/boo.obj", ENEMY4, 0.15);
	globject("assets/render/enemy/FlyGuy/flyguy.obj", ENEMY5, 0.1);
	globject("assets/render/boss/BossTitan/BOSS_Titan.obj", BOSS_A, 1); //test
	globject("assets/render/boss/AssaultBomber/AssaultBomber.obj", BOSS_B, 0.06);
	globject("assets/render/boss/BomberElite/BomberElite.obj", BOSS_C, 0.06);
	globject("assets/render/boss/EagleBomber/EagleBomber.obj", BOSS_D, 0.06);
	globject("assets/render/bombs/MegaBomb/MegaBomb.obj", BOMB_DEFAULT, 0.1);
	globject("assets/render/bombs/AquaBomb/AquaBomb.obj", BOMB_WATER, 0.1);
	globject("assets/render/bombs/LightBomb/LightBomb.obj", BOMB_LIGHT, 0.1);
	globject("assets/render/bombs/WindBomb/WindBomb.obj", BOMB_WIND, 0.1);
	globject("assets/render/bombs/RemoteBomb/RemoteBomb.obj", BOMB_REMOTE, 0.1);
	globject("assets/render/models/icosphere.obj", MAX_ENUM, 1);
	globject("assets/render/models/FireBurst/FireBurst2.obj", FIRE_2, 0.5);
	globject("assets/render/models/menu.obj", MENU, 1);
	//std::cout << "teoswag"  << std::endl;
	/* Load Uniform Variable */

	glProgramUniformMatrix4fv(_progid, \
		glGetUniformLocation(_progid, "P"), 1, GL_FALSE, \
		(GLfloat *)(Matrix::projection_matrix(60, 0.1, 100, size_x / size_y)._matrix));
	globject::_viewMatID = glGetUniformLocation(_progid, "V");
	globject::_modelMatID = glGetUniformLocation(_progid, "M");
	globject::_keyFrameID = glGetUniformLocation(_progid, "keyframe");
	globject::_legPos = glGetUniformLocation(_progid, "leg_pos");
}

t_point		set_dir(int d) {
	t_point	dir;

	dir.y = 0;
	if (d == DIR_UP) {
		dir.x = 0;
		dir.z = 1;
	}
	if (d == DIR_BOTTOM) {
		dir.x = 0;
		dir.z = -1;
	}
	if (d == DIR_LEFT) {
		dir.x = -1;
		dir.z = 0;
	}
	if (d == DIR_RIGHT) {
		dir.x = 1;
		dir.z = 0;
	}
	return (dir);
}

void		globject::display_menu(SDL_Surface *imp) {
	GLuint	_textID;
	GLuint	loc;
	Matrix	a;

	if (!imp)
		return ;
	glUniform1f(globject::_keyFrameID, 0);
	glGenTextures(1, &_textID);
	globject::_object[MENU]._textNumber = 1;
	glBindTexture(GL_TEXTURE_2D, _textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, \
			imp->w, imp->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imp->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	loc = glGetUniformLocation(globject::_progid, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textID);
	glUniform1i(loc, 0);
	a.scale_matrix(1);

	glUniformMatrix4fv(globject::_viewMatID, 1, GL_FALSE, a._matrix);
	a.scale_matrix(1 / 1);
	a.trans_matrix(0, 0, -1.75);

	glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, a._matrix);
	glBindVertexArray(globject::_object[MENU]._vaoID);
	glDrawArrays(GL_TRIANGLES, \
			0, globject::_object[MENU].parser._finalVertexSize / 3);
}

void        globject::render(int status) {
	status = status * 42;
	for (size_t i = 0; i < _textNumber; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textID[i]);
	}
	for (size_t i = 0; i < _textNumber; i++)
		glUniform1i(_textLoc[i], i);

	glBindVertexArray(_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, parser._finalVertexSize / 3);
}

void        globject::update_key() {
	SDL_Event event;

	SDL_PollEvent(&event);
}

GLfloat     globject::get_leg_pos(int model) {
	if (model >= PLAYER && model <= PLAYER4)
		return (10);
	if (model == ENEMY1)
		return (1);
	return (-100);
}

void        globject::skybox(t_point viewDir) {
	t_point			modelPos;
	t_point			modelDir;
	Matrix			Model;
	t_point			viewPos;
	Matrix			view;
	static float	degueu = 0;

	degueu += 0.004;
	if (!space)
		degueu -= 0.003;
	viewPos.x = 0;
	viewPos.y = 0;
	viewPos.z = 0;
	//viewDir.x += 1.5;
	viewDir.y += 2 + degueu;
	viewDir.x = 1 + degueu;
	view = Matrix::view_matrix(viewPos, viewDir, 1);
	//glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	modelPos.z = 0;
	modelPos.y = 0;
	modelPos.x = 0;
	glUniformMatrix4fv(globject::_viewMatID, 1, GL_FALSE, view._matrix);
	glUniform1f(globject::_keyFrameID, 0);
	modelDir.x = 1;
	modelDir.z = 0;
	modelDir.y = 0;

	Model = Matrix::model_matrix(modelPos, modelDir, 50);
	glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
	globject::_object[MAX_ENUM].render(0);
}

void		globject::render_all(Entity ***map, std::list<Entity*> players, SDL_Surface *menu) {
	t_point							modelPos;
	t_point							modelDir;
	Matrix							Model;
	t_point							viewPos;
	t_point							viewDir;
	Matrix							view;
	float							zoomMul;
	float							zoom;
	static size_t					a = 0;
	// static float					time = 0;
	static float					o = 0;
	static float					prog = 0.01;
	std::list<Entity*>::iterator	it;
	std::list<Entity*>::iterator	ite;

	zoom = 1;
	//if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
	//return ;
	o += 0.003;
	zoomMul = 1;
	a++;
	a = a % 10;
	view = Matrix::view_matrix(viewPos, viewDir, 1);
	// time = clock();
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	modelPos.z = 0;
	glUniform1f(globject::_keyFrameID, 0);
	modelDir.x = 1;
	modelDir.z = 0;
	modelDir.y = 0;
	std::cout << "deb 01" << std::endl;
	//test
	//display_menu(NULL);
	//SDL_GL_SwapWindow(globject::_displayWindow);
	//return ;
	//test
	display_menu(menu);
	std::cout << "deb 02" << std::endl;

	viewDir.x = 1.1;
	viewDir.y = 1.57;
	viewDir.z = 0;
	skybox(viewDir);
	if (space) {
		viewDir.x += cos(30 * o) / 30;
		viewDir.y +=  sin(30 * o) / 30;
		viewDir.z = 0;
	}
	viewPos.x = 0;
	viewPos.y = 0;
	viewPos.z = -38;
	if (doIspin) {
		viewDir.x = 1.57;
		viewDir.y += prog;
		viewPos.x -= spinx;
		viewPos.y -= spinz;
		viewPos.z += prog;
		if (prog < 25)
			prog+= 0.36;
	}
	else
		prog = 0;
		std::cout << "deb 03" << std::endl;
	view = Matrix::view_matrix(viewPos, viewDir, zoom);
	glUniformMatrix4fv(globject::_viewMatID, 1, GL_FALSE, view._matrix);
	for (int y = 0; y < 1; y++) {
		for (int i = -mapY_size / 2; i < mapY_size / 2; i++) {
			for (int j = -mapX_size / 2; j < mapX_size / 2; j++) {
				if (!(j == -mapX_size / 2 || j == mapX_size / 2 - 1) \
					&& !(i == -mapY_size / 2 || i == mapY_size / 2 - 1) \
					&& !(y == 0))
				continue ;
				modelDir.x = 1;
				modelDir.z = 0;
				modelDir.y = 0;
				modelPos.x = i;
				modelPos.z = j;
				modelPos.y = -1 - y;
				Model = Matrix::model_matrix(modelPos, modelDir, globject::_object[FLOOR]._zoom);
				glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
				globject::_object[FLOOR].render(0);
			}
		}
	}
	std::cout << "deb 04" << std::endl;

	for (int i = -mapY_size / 2; i <  mapY_size / 2; i++) {
		for (int j = -mapX_size / 2; j < mapX_size / 2; j++) {
			zoomMul = 1;
			modelDir.x = 1;
			modelDir.z = 0;
			modelDir.y = 0;
			modelPos.y = 0;
			modelPos.x = i;
			modelPos.z = j;
			modelPos.x = map[i + mapY_size / 2][j + mapX_size / 2]->pos_y - 10;
			modelPos.z = map[i + mapY_size / 2][j + mapX_size / 2]->pos_x - 10;
			if (map[i + mapY_size / 2][j + mapX_size / 2]->model == -1)
				continue ;

			if (map[i + mapY_size / 2][j + mapX_size / 2]->model >= WALL_HP_1 \
					&& map[i + mapY_size / 2][j + mapX_size / 2]->model <= WALL_HP_4)
				map[i + mapY_size / 2][j + mapX_size / 2]->model = \
				map[i + mapY_size / 2][j + mapX_size / 2]->status;

			if (map[i + mapY_size / 2][j + mapX_size / 2]->model == BOMB) {
				if (!(a % (1 + (dynamic_cast<Bomb*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer) / 2))) {
					zoomMul *= 1 + 3.0f / (static_cast<float> \
						((dynamic_cast<Bomb*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer)));
				}
			}

			if (map[i + mapY_size / 2][j + mapX_size / 2]->model == FIRE_2) {
				zoomMul *= 1.0f - (1.0f / (static_cast<float> \
					((dynamic_cast<Fire*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer))));
			}
			// SEGV multi / arena random
			//  globject::render_all (map=0xeb0e830, players=std::list = {...}, menu=0x0)
			// globject::_object[map[i + mapY_size / 2][j + mapX_size / 2]->model]._zoom * zoomMul);
			Model = Matrix::model_matrix(modelPos, modelDir, \
				globject::_object[map[i + mapY_size / 2][j + mapX_size / 2]->model]._zoom * zoomMul);
			glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
			globject::_object[map[i + mapY_size / 2][j + mapX_size / 2]->model].render(0);
		}
	}
	std::cout << "deb 05" << std::endl;

	it = players.begin();
	ite = players.end();
	while (it != ite) {
		modelDir.x = -1;
		modelDir.z = 0;
		modelDir.y = 0;
		modelDir = set_dir((*it)->dir);
		modelPos.y = 0;
		modelPos.x = ((*it)->pos_y - 10);
		modelPos.z = (((*it)->pos_x - 10));
		if ((*it)->model == ENEMY1)
			modelPos.z += 0.5;
		Model = Matrix::model_matrix(modelPos, modelDir, \
			globject::_object[(*it)->model]._zoom);
		glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
		glUniform1f(globject::_keyFrameID, (*it)->frame);
		glUniform1f(globject::_legPos, get_leg_pos((*it)->model));
		globject::_object[(*it)->model].render(0);
		it++;
	}
	std::cout << "deb 06" << std::endl;

	SDL_GL_SwapWindow(globject::_displayWindow);
}

char        *globject::filetobuff(char *path)
{
	int		fd;
	int		len;
	char	*n;

	len = 0;
	n = new char[10000];
	if ((fd = open(path, O_RDONLY)) < 0)
		exit(0);
	while (read(fd, n, 1))
		len++;
	close(fd);
	fd = open(path, O_RDONLY);
	read(fd, n, len);
	n[len] = 0;
	return (n);
}

void		globject::spin(float x, float y) {
	doIspin = 1;
	spinx = x - 10;
	spinz = y - 10;
}

GLuint      globject::loadshaders(char *fragshader, char *vertexshader) {
	GLuint	vshaderid;
	GLuint	fshaderid;
	GLuint	progid;
	char	*buff;
	int		Result;
	int		InfoLogLength;
	char	FragmentShaderErrorMessage[1000];

	vshaderid = glCreateShader(GL_VERTEX_SHADER);
	fshaderid = glCreateShader(GL_FRAGMENT_SHADER);
	buff = filetobuff(vertexshader);
	// glShaderSource(vshaderid, 1, (const char *const *)(&buff), NULL);
	glShaderSource(vshaderid, 1, (const char **)(&buff), NULL);
	glCompileShader(vshaderid);

	glGetShaderiv(vshaderid, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vshaderid, GL_INFO_LOG_LENGTH, &InfoLogLength);
	glGetShaderInfoLog(vshaderid, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

	buff = filetobuff(fragshader);
	// glShaderSource(fshaderid, 1, (const char *const *)(&buff), NULL);
	glShaderSource(fshaderid, 1, (const char **)(&buff), NULL);
	glCompileShader(fshaderid);

	glGetShaderiv(fshaderid, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fshaderid, GL_INFO_LOG_LENGTH, &InfoLogLength);
	glGetShaderInfoLog(fshaderid, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

	progid = glCreateProgram();
	glAttachShader(progid, vshaderid);
	glAttachShader(progid, fshaderid);
	glLinkProgram(progid);
	globject::_progid = progid;
	return (progid);
}

void		globject::load_shaders() {
	char	a[] = "assets/render/shaders/frag.shader";
	char	b[] = "assets/render/shaders/vertex.shader";

	glUseProgram(loadshaders(a, b));
}

void		globject::fill_vao(void) {
	GLuint	vertexBufferID;
	GLuint	textBufferID;
	GLuint	textureBufferID;

	glGenVertexArrays(1, &(_vaoID));
	glGenBuffers(1, &(vertexBufferID));
	glGenBuffers(1, &(textBufferID));
	glGenBuffers(1, &(textureBufferID));
	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * parser._finalVertexSize, \
			parser._finalVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textBufferID);
	glBufferData(GL_ARRAY_BUFFER, parser._finalTextSize * sizeof(GLfloat), \
			parser._finalText, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
	glBufferData(GL_ARRAY_BUFFER, parser._textIDSize * sizeof(GLfloat), \
			parser._textID, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);
}
