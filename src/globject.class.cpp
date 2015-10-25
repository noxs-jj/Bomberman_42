// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/25 12:36:14 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <globject.class.hpp>

globject			globject::_object[100];
SDL_Window			*globject::_displayWindow;
SDL_Renderer		*globject::_displayRenderer;
SDL_RendererInfo	globject::_displayRendererInfo;
GLuint				globject::_progid;
GLuint				globject::_modelMatID;
GLuint				globject::_viewMatID;

globject::globject(void)
{

}

globject::globject(std::string path, GLuint ID) : _ID(ID)
{
	int neg;

	neg = (ID == WALL_HP_1 || ID == FLOOR || || ID == WALL_INDESTRUCTIBLE);
	parser.parse(path, neg);
	fill_vao();
	_textNumber = parser._textNum;
	load_bmp();
}

globject::globject(std::list<std::string> paths, GLuint ID) : _ID (ID)
{

}

globject::~globject(void)
{

}

void globject::load_bmp()
{
    unsigned char   header[54];
    unsigned int    size[3];
    unsigned char   *data;
    GLuint          textid;
    int             a;
	int				fd;
	std::string		name;
	std::string		path;

	std::cout << parser._textNum << std::endl;
	for (int i = 0; i < parser._textNum; i++)
	{
		name = "texture";
		path ="textures/";
		path += parser._texture[i];
		std::cout << path << std::endl;
		if ((fd = open(path.c_str(), O_RDONLY)) < 0 ||
			strcmp(strchr(parser._texture[i].c_str(), '.'), ".bmp"))
		{
			if (strcmp(strchr(parser._texture[i].c_str(), '.'), ".bmp"))
			{
//				load_png();
				return ;
			}
			else
				exit(0);
		}
		read(fd, header, 54);
		size[0] = *(int*)&(header[0x22]);
		size[1] = *(int*)&(header[0x12]);
		size[2] = *(int*)&(header[0x16]);

		
		data = new unsigned char [sizeof(unsigned char) * size[0]];
		read(fd, data, size[0]);
		glGenTextures(1, &(_textID[i]));
		glBindTexture(GL_TEXTURE_2D, (_textID[i]));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			size[1], size[2], 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		name += std::to_string(i);
		_textLoc[i] = glGetUniformLocation(globject::_progid, name.c_str());
	}
}

void globject::resize(int x, int y)
{
	SDL_SetWindowSize(globject::_displayWindow, x, y);
}

void		globject::init(void)
{

	/* Init SDL */

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	globject::_displayWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1200, 1200, SDL_WINDOW_OPENGL);

	/* Init OpenGL */

	SDL_GLContext context = SDL_GL_CreateContext(globject::_displayWindow);
    glClearColor( 0.0f, 0.0f, 0.3f, 0.0f );
    glEnable( GL_DEPTH_TEST );
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(globject::_displayWindow);

	/* load shaders */
	globject::load_shaders();

	/* load Models */

	globject n("models/cube.obj", WALL_HP_1);
	globject::_object[n._ID] = n;
    n = globject("models/cube_floor.obj", FLOOR);
	globject::_object[n._ID] = n;
    n = globject("models/rock.obj", WALL_INDESTRUCTIBLE);
	globject::_object[n._ID] = n;

	//std::cout << "teoswag"  << std::endl;
	/* Load Uniform Variable */

	glProgramUniformMatrix4fv(_progid, 
		glGetUniformLocation(_progid, "P"),
			1, GL_FALSE, (GLfloat *)(Matrix::projection_matrix(60, 0.1, 100, 1)._matrix));
	globject::_viewMatID = glGetUniformLocation(_progid, "V");
	globject::_modelMatID = glGetUniformLocation(_progid, "M");
}

void		globject::render(int status)
{
	for (int i = 0; i < _textNumber; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textID[i]);
	}
	for (int i = 0; i < _textNumber; i++)
		glUniform1i(_textLoc[i], i);

	glBindVertexArray(_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, parser._finalVertexSize / 3);
}

void		globject::update_key()
{
	SDL_Event event;

	SDL_PollEvent(&event);
}

void		globject::render_all(Entity ***map, std::list<Player*> players)
{
	t_point		modelPos;
	t_point		modelDir;
	Matrix		Model;
    t_point     viewPos;
    t_point     viewDir;
    Matrix      view;

	static		float time = 0;
	static float o = 0;

	if ((1 / (clock() - time)) * CLOCKS_PER_SEC > 60)
		return ;

	o += 0.005;
	viewDir.x = 1.1;
	viewDir.y = 1.57;
	viewDir.z = 0;
	viewPos.x = 0;
	viewPos.y = 0;
	viewPos.z = -27;
	view = Matrix::view_matrix(viewPos, viewDir, 1);
	time = clock();
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	modelPos.z = 0;
	glUniformMatrix4fv(globject::_viewMatID, 1, GL_FALSE, view._matrix);

	for (int y = 0; y < 5; y++)
	{
	for (int i = -MAP_Y_SIZE / 2; i < MAP_Y_SIZE / 2; i++)
	{
			for (int j = -MAP_X_SIZE / 2; j < MAP_X_SIZE / 2; j++)
			{
				modelDir.x = 1;
				modelDir.z = 0;
				modelDir.y = 0;
				modelPos.x = i;
				modelPos.z = j;
				modelPos.y = -1 - y;
				Model = Matrix::model_matrix(modelPos, modelDir, 1);
				glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
				globject::_object[30].render(0);
			}
		}
		}
	for (int i = -MAP_Y_SIZE / 2; i < MAP_Y_SIZE / 2; i++)
	{
		for (int j = -MAP_X_SIZE / 2; j <MAP_X_SIZE / 2; j++)
		{
			modelDir.x = 1;
			modelDir.z = 0;
			modelDir.y = 0;
			modelPos.y = 0;
			modelPos.x = i;
			modelPos.z = j;
			Model = Matrix::model_matrix(modelPos, modelDir, 0.05);
			glUniformMatrix4fv(globject::_modelMatID, 1, GL_FALSE, Model._matrix);
			if (map[i + MAP_Y_SIZE / 2][j + MAP_X_SIZE / 2]->type == WALL)
				globject::_object[WALL].render(0);
			}
	}
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

GLuint      globject::loadshaders(char *fragshader, char *vertexshader)
{
    GLuint      vshaderid;
    GLuint      fshaderid;
    GLuint      progid;
    char        *buff;

    vshaderid = glCreateShader(GL_VERTEX_SHADER);
    fshaderid = glCreateShader(GL_FRAGMENT_SHADER);
    buff = filetobuff(vertexshader);
    glShaderSource(vshaderid, 1, (const char *const *)(&buff), NULL);
    glCompileShader(vshaderid);


	int Result;
	int InfoLogLength;
	char FragmentShaderErrorMessage[1000];

    glGetShaderiv(vshaderid, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vshaderid, GL_INFO_LOG_LENGTH, &InfoLogLength);
    glGetShaderInfoLog(vshaderid, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	std::cout << FragmentShaderErrorMessage << std::endl;

	buff = filetobuff(fragshader);
	glShaderSource(fshaderid, 1, (const char *const *)(&buff), NULL);
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
	return (progid);
}

void		globject::load_shaders()
{
	char a[] = "shaders/frag.shader";
	char b[]  = "shaders/vertex.shader";
	glUseProgram(loadshaders(a, b));
}

void		globject::fill_vao(void)
{
	GLuint vertexBufferID;
	GLuint textBufferID;
	GLuint textureBufferID;

	glGenVertexArrays(1, &(_vaoID));
	glGenBuffers(1, &(vertexBufferID));
	glGenBuffers(1, &(textBufferID));
	glGenBuffers(1, &(textureBufferID));
	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * parser._finalVertexSize, parser._finalVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, textBufferID);
	glBufferData(GL_ARRAY_BUFFER, parser._finalTextSize * sizeof(GLfloat), parser._finalText, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
    glBufferData(GL_ARRAY_BUFFER, parser._textIDSize * sizeof(GLfloat), parser._textID, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);
}

