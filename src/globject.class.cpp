#include <globject.class.hpp>
#include <bomb.class.hpp>
#include <fire.class.hpp>

globject				globject::_object[100];
SDL_Window			*globject::_displayWindow;
SDL_Renderer		*globject::_displayRenderer;
SDL_RendererInfo	globject::_displayRendererInfo;
GLuint				globject::_progid;
GLuint				globject::_modelMatID;
GLuint				globject::_viewMatID;
GLuint				globject::_keyFrameID;
GLuint				globject::_legPos;
GLfloat				globject::spinx;
GLfloat				globject::spinz;
int					globject::doIspin;
int					globject::space = 1;
int					globject::mapX_size = 20;
int					globject::mapY_size = 20;

globject::globject(void)
{

}

globject::globject(std::string path, GLuint ID, GLfloat zoom) : _ID(ID), _zoom(zoom)
{
	std::cout << "AAA" << std::endl;
	int neg;

	neg = (ID == WALL_HP_1 || ID == FLOOR || ID == WALL_INDESTRUCTIBLE);
	neg = 0;
	std::cout << "parsing" << std::endl;
	parser.parse(path, neg);
	std::cout << "parsed" << std::endl;
	std::cout << "filling" << std::endl;
	fill_vao();
	std::cout << "filled" << std::endl;
	_textNumber = parser._textNum;
	std::cout << "loading bmp" << std::endl;
	load_bmp();
	std::cout << "loaded bmp" << std::endl;
	std::cout << "copying into array" << std::endl;
	globject::_object[ID] = *this;
	std::cout << "copy success" << std::endl;
}

globject::~globject(void) {}

void globject::reinit_level(int env)
{
	env = env - 1;
	doIspin = 0;
}

void globject::load_bmp()
{
	std::string     name;
	std::string     path;
	std::cout << parser._textNum << std::endl;
    for (size_t i = 0; i < parser._textNum; i++)
    {
        name = "texture";
        path ="render/textures/";
		if (globject::space)
			path = "render/spacestextures/";
		path += parser._texture[i];
		std::cout << path.c_str() << std::endl;
		std::cout << "LOL1" << std::endl;
        SDL_Surface *imp = IMG_Load(path.c_str());
		if (imp == NULL)
		{
			std::cerr << "FAILFAIL" << std::endl;
			throw std::exception() ;
		}
		std::cout << "LOL2" << std::endl;
		glGenTextures(1, &(_textID[i]));
		std::cout << "LOL3" << std::endl;
		glBindTexture(GL_TEXTURE_2D, (_textID[i]));
		std::cout << "LOL4" << std::endl;
		if ((_ID >= BOSS_A && _ID <= BOSS_C)
			|| (_ID >= PLAYER && _ID <= PLAYER4)
			|| _ID == BOMB
			|| (_ID >= ENEMY && _ID <= ENEMY4)
			|| _ID == MENU
			|| (globject::space && _ID == MAX_ENUM))
			{
				std::cout << "LOL4.1" << std::endl;

				// GLenum err = glGetError();
				// if (err != GL_NO_ERROR)
				// {
				// 	std::cerr << err << std::endl;
				// }

				// XXX XXX XXX
				# ifdef linux
					glTexImage2D(GL_TEXTURE_2D, 0,
												GL_RGB,
												imp->w, imp->h, 0,
												GL_BGR, // GL_RED, GL_RED_INTEGER, GL_RG, GL_RG_INTEGER, GL_RGB, GL_RGB_INTEGER, GL_RGBA, GL_RGBA_INTEGER, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, GL_LUMINANCE_ALPHA, GL_LUMINANCE, GL_ALPHA
												GL_UNSIGNED_BYTE, imp->pixels);
				# endif
				# ifdef __APPLE__
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						imp->w, imp->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imp->pixels);
				# endif
				// XXX XXX XXX
				std::cout << "LOL4.2" << std::endl;
			}
		else
		{
			std::cout << "LOL4.3" << std::endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				imp->w, imp->h, 0, GL_BGR, GL_UNSIGNED_BYTE, imp->pixels);
				std::cout << "LOL4.5" << std::endl;
		}
			std::cout << "LOL5" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		std::cout << "LOL6" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		std::cout << "LOL7" << std::endl;
		name += std::to_string(i);
		std::cout << "LOL8" << std::endl;
		_textLoc[i] = glGetUniformLocation(globject::_progid, name.c_str());
	}
}

void globject::resize(int x, int y)
{
	SDL_SetWindowSize(globject::_displayWindow, x, y);
	glViewport(0, 0, x, y);
}

void		globject::init(void)
{

	/* Init SDL */
	if (SDL_Init(SDL_INIT_VIDEO
			| SDL_INIT_AUDIO
			| SDL_INIT_GAMECONTROLLER
			| SDL_INIT_JOYSTICK
		) < 0) {
		std::cerr << "globject::init SDL_Init() error = " << SDL_GetError() << std::endl;
		throw std::exception();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	# ifdef linux
		globject::_displayWindow = SDL_CreateWindow("Bomberman",
									700,
									0,
									800, 800,
									SDL_WINDOW_OPENGL
								//	| SDL_WINDOW_BORDERLESS
								//	| SDL_WINDOW_RESIZABLE
								//	| SDL_WINDOW_FULLSCREEN
						);
	# endif
	# ifdef __APPLE__
		globject::_displayWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED, 1400, 1400,
						SDL_WINDOW_OPENGL
						| SDL_WINDOW_RESIZABLE
						// | SDL_WINDOW_BORDERLESS
					);
	# endif

	/* Init OpenGL */
	std::cout << "deb -997" << std::endl;

	SDL_GLContext glcontext = SDL_GL_CreateContext(globject::_displayWindow);
	if(NULL == glcontext) {
		std::cerr << "SDL_GLContext failed " <<  SDL_GetError() << std::endl;
		_exit(0);
	}

	# ifdef linux
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if(err != GLEW_OK) {
			std::cerr << "glew failed" << glewGetErrorString(err) << std::endl;
			_exit(0);
		}
	# endif

	std::cout << "deb -996" << std::endl;
    glClearColor( 0.0f, 0.0f, 0.3f, 0.0f );
    glEnable(GL_DEPTH_TEST);
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(globject::_displayWindow);
	glEnable(GL_BLEND);
	std::cout << "deb -995" << std::endl;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/* load shaders */
	std::cout << "deb -994" << std::endl;
	globject::load_shaders();
	std::cout << "deb -998" << std::endl;

	/* load Models */

	std::cout << "yhnm 2" << std::endl;
	globject("render/models/cube.obj", WALL_HP_1, 1);
	std::cout << "yhnm 2.1" << std::endl;
	globject("render/models/cube1.obj", WALL_HP_2, 1);
	globject("render/models/cube2.obj", WALL_HP_3, 1);
    globject("render/models/cube_floor.obj", FLOOR, 1);
	globject("render/models/rock.obj", WALL_INDESTRUCTIBLE, 1);
	globject("render/models/Bomberman/Bomberman.obj", PLAYER, 0.03);
	globject("render/models/Bomberman/Bomberman.obj", PLAYER1, 0.03);
	globject("render/models/Bomberman/Bomberman2.obj", PLAYER2, 0.03);
	globject("render/models/Bomberman/Bomberman3.obj", PLAYER3, 0.03);
	globject("render/models/Bomberman/Bomberman4.obj", PLAYER4, 0.03);
	globject("render/models/ENEMY_Bear_Grizzly/ENEMY_Bear_Grizzly1.obj", ENEMY1, 0.3);
	globject("render/models/ENEMY_Bear_Grizzly/ENEMY_Bear_Grizzly1.obj", ENEMY2, 0.3);
	globject("render/models/ENEMY_Bear_Grizzly/ENEMY_Bear_Grizzly1.obj", ENEMY3, 0.3);
	globject("render/models/ENEMY_Bear_Grizzly/ENEMY_Bear_Grizzly1.obj", ENEMY4, 0.3);
	globject("render/models/BOSS_Titan/BOSS_Titan.obj", BOSS_A, 1); //test
	globject("render/models/BOSS_Titan/BOSS_Titan.obj", BOSS_B, 1);
	globject("render/models/BOSS_Titan/BOSS_Titan.obj", BOSS_C, 1);
	globject("render/models/GameCube - Bomberman Generation - Bombs/MegaBomb/MegaBomb.obj", BOMB, 0.1);
	globject("render/models/icosphere.obj", MAX_ENUM, 1);
	globject("render/models/FireBurst/FireBurst2.obj", FIRE_2, 0.5);
	globject("render/models/menu.obj", MENU, 1);
	//std::cout << "teoswag"  << std::endl;
	/* Load Uniform Variable */

	glProgramUniformMatrix4fv(_progid,
		glGetUniformLocation(_progid, "P"),
			1, GL_FALSE, (GLfloat *)(Matrix::projection_matrix(60, 0.1, 100, 1)._matrix));
	globject::_viewMatID = glGetUniformLocation(_progid, "V");
	globject::_modelMatID = glGetUniformLocation(_progid, "M");
	globject::_keyFrameID = glGetUniformLocation(_progid, "keyframe");
	globject::_legPos = glGetUniformLocation(_progid, "leg_pos");
}

t_point		set_dir(int d)
{
	t_point dir;

	dir.y = 0;
	if (d == DIR_UP)
	{
		dir.x = 0;
		dir.z = 1;
	}
	if (d == DIR_BOTTOM)
	{
		dir.x = 0;
		dir.z = -1;
	}
	if (d == DIR_LEFT)
	{
		dir.x = -1;
		dir.z = 0;
	}
	if (d == DIR_RIGHT)
	{
		dir.x = 1;
		dir.z = 0;
	}
	return (dir);
}

void		globject::display_menu(SDL_Surface *imp)
{
	GLuint _textID;
	GLuint loc;
	Matrix a;

	if (!imp)
		return ;
	glGenTextures(1, &_textID);
	globject::_object[MENU]._textNumber = 1;
	glBindTexture(GL_TEXTURE_2D, _textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
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
	glDrawArrays(GL_TRIANGLES, 0, globject::_object[MENU].parser._finalVertexSize / 3);
}

void		globject::render(int status)
{
	status = status * 42;
	for (size_t i = 0; i < _textNumber; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textID[i]);
	}
	for (size_t i = 0; i < _textNumber; i++)
		glUniform1i(_textLoc[i], i);

	glBindVertexArray(_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, parser._finalVertexSize / 3);
}

void		globject::update_key()
{
	SDL_Event event;

	SDL_PollEvent(&event);
}

GLfloat globject::get_leg_pos(int model)
{
	if (model >= PLAYER && model <= PLAYER4)
		return (10);
	if (model == ENEMY1)
		return (1);
	return (-100);
}

void globject::skybox(t_point viewDir)
{
    t_point     modelPos;
    t_point     modelDir;
    Matrix      Model;
    t_point     viewPos;
    Matrix      view;
	static float degueu = 0;

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

void		globject::render_all(Entity ***map, std::list<Entity*> players, SDL_Surface *menu)
{
	t_point		modelPos;
	t_point		modelDir;
	Matrix		Model;
	t_point		viewPos;
	t_point		viewDir;
	Matrix		view;
	float		zoomMul;
	float		zoom;
	static size_t	a = 0;
	// static float	time = 0;
	static float	o = 0;
	static float	prog = 0.01;
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

	//test
	//display_menu(NULL);
	//SDL_GL_SwapWindow(globject::_displayWindow);
	//return ;
	//test
	viewDir.x = 1.1;
	viewDir.y = 1.57;
	viewDir.z = 0;
	skybox(viewDir);
	if (space)
	{
		viewDir.x += cos(30 * o) / 30;
		viewDir.y +=  sin(30 * o) / 30;
		viewDir.z = 0;
	}
    viewPos.x = 0;
    viewPos.y = 0;
    viewPos.z = -28;
	if (doIspin)
	{
		viewDir.x = 1.57;
		viewDir.y += prog;
		viewPos.x -= spinx;
		viewPos.y -= spinz;
		viewPos.z += prog;
		if (prog < 25)
		{
			prog+= 0.36;
		}
	}
	else
		prog = 0;
	view = Matrix::view_matrix(viewPos, viewDir, zoom);
	glUniformMatrix4fv(globject::_viewMatID, 1, GL_FALSE, view._matrix);
	for (int y = 0; y < 1; y++)
	{
	for (int i = -mapY_size / 2; i < mapY_size / 2; i++)
	{
			for (int j = -mapX_size / 2; j < mapX_size / 2; j++)
			{
				if (!(j == -mapX_size / 2 || j == mapX_size / 2 - 1)
					&& !(i == -mapY_size / 2 || i == mapY_size / 2 - 1) && !(y == 0))
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

	for (int i = -mapY_size / 2; i <  mapY_size / 2; i++)
	{
		for (int j = -mapX_size / 2; j < mapX_size / 2; j++)
		{
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
			if (map[i + mapY_size / 2][j + mapX_size / 2]->model >= WALL_HP_1 &&
				map[i + mapY_size / 2][j + mapX_size / 2]->model <= WALL_HP_4)
				map[i + mapY_size / 2][j + mapX_size / 2]->model =
				map[i + mapY_size / 2][j + mapX_size / 2]->status;
			if (map[i + mapY_size / 2][j + mapX_size / 2]->model == BOMB)
				if (!(a % (1 + (dynamic_cast<Bomb*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer) / 2)))
				{
					zoomMul *= 1 + 3.0f / (static_cast<float>
					((dynamic_cast<Bomb*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer)));
				}
            if (map[i + mapY_size / 2][j + mapX_size / 2]->model == FIRE_2)
			{
				zoomMul *= 1.0f - (1.0f / (static_cast<float>
									 ((dynamic_cast<Fire*>(map[i + mapY_size / 2][j + mapX_size / 2])->timer))));
			}
			Model = Matrix::model_matrix(modelPos, modelDir,
				globject::_object[map[i + mapY_size / 2][j + mapX_size / 2]->model]._zoom * zoomMul);
			glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
			globject::_object[map[i + mapY_size / 2][j + mapX_size / 2]->model].render(0);
		}
	}

	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator ite;
	it = players.begin();
	ite = players.end();
	while (it != ite)
	{
		modelDir.x = -1;
		modelDir.z = 0;
		modelDir.y = 0;
		modelDir = set_dir((*it)->dir);
		modelPos.y = 0;
		modelPos.x = ((*it)->pos_y - 10);
		modelPos.z = (((*it)->pos_x - 10));
		Model = Matrix::model_matrix(modelPos, modelDir,
					globject::_object[(*it)->model]._zoom);
		glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
		glUniform1f(globject::_keyFrameID, (*it)->frame);
		glUniform1f(globject::_legPos, get_leg_pos((*it)->model));
		globject::_object[(*it)->model].render(0);
		it++;
	}
	display_menu(menu);
	SDL_GL_SwapWindow(globject::_displayWindow);
}

char        *globject::filetobuff(char *path)
{
    int     fd;
    int     len;
    char    *n;

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

void		globject::spin(float x, float y)
{
	doIspin = 1;
	spinx = x - 10;
	spinz = y - 10;
}

GLuint      globject::loadshaders(char *fragshader, char *vertexshader)
{
    GLuint      vshaderid;
    GLuint      fshaderid;
    GLuint      progid;
    char        *buff;

		// GLenum err = glewInit();
    // if(err != GLEW_OK) {
		// 	std::cerr << "glew failed" << std::endl;
		// 	std::cerr << glewGetErrorString(err) << std::endl;
		// 	_exit(0);
		// }

		std::cout << "fgh 0" << std::endl;
    vshaderid = glCreateShader(GL_VERTEX_SHADER);
		std::cout << "fgh 3" << std::endl;
    fshaderid = glCreateShader(GL_FRAGMENT_SHADER);
		std::cout << "fgh 2" << std::endl;
    buff = filetobuff(vertexshader);
		// glShaderSource(vshaderid, 1, (const char *const *)(&buff), NULL);
    glShaderSource(vshaderid, 1, (const char **)(&buff), NULL);
    glCompileShader(vshaderid);

		std::cout << "fgh 1" << std::endl;

	int Result;
	int InfoLogLength;
	char FragmentShaderErrorMessage[1000];

    glGetShaderiv(vshaderid, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vshaderid, GL_INFO_LOG_LENGTH, &InfoLogLength);
    glGetShaderInfoLog(vshaderid, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	std::cout << FragmentShaderErrorMessage << std::endl;

	buff = filetobuff(fragshader);
	// glShaderSource(fshaderid, 1, (const char *const *)(&buff), NULL);
	glShaderSource(fshaderid, 1, (const char **)(&buff), NULL);
	glCompileShader(fshaderid);

	glGetShaderiv(fshaderid, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fshaderid, GL_INFO_LOG_LENGTH, &InfoLogLength);
	glGetShaderInfoLog(fshaderid, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	std::cout << FragmentShaderErrorMessage << std::endl;

	progid = glCreateProgram();
	glAttachShader(progid, vshaderid);
	glAttachShader(progid, fshaderid);
	glLinkProgram(progid);
	globject::_progid = progid;
	std::cout << "yhnm 0" << std::endl;
	return (progid);
}

void		globject::load_shaders()
{

	char a[] = "render/shaders/frag.shader";
	char b[]  = "render/shaders/vertex.shader";
	glUseProgram(loadshaders(a, b));
	std::cout << "try 3" << std::endl;
}

void		globject::fill_vao(void)
{
	GLuint vertexBufferID;
	GLuint textBufferID;
	GLuint textureBufferID;

	std::cout << "111" << std::endl;

	glGenVertexArrays(1, &(_vaoID));
		std::cout << "qwe" << std::endl;

	glGenBuffers(1, &(vertexBufferID));

		std::cout << "asd" << std::endl;
	glGenBuffers(1, &(textBufferID));

		std::cout << "zxc" << std::endl;
	glGenBuffers(1, &(textureBufferID));

		std::cout << "jkl" << std::endl;
	glBindVertexArray(_vaoID);

		std::cout << "222" << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * parser._finalVertexSize, parser._finalVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

		std::cout << "333" << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, textBufferID);
	glBufferData(GL_ARRAY_BUFFER, parser._finalTextSize * sizeof(GLfloat), parser._finalText, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
    glBufferData(GL_ARRAY_BUFFER, parser._textIDSize * sizeof(GLfloat), parser._textID, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);
}
