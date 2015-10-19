// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/19 13:30:46 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <globject.class.hpp>

globject			globject::_object[100];
SDL_Window			*globject::_displayWindow;
SDL_Renderer		*globject::_displayRenderer;
SDL_RendererInfo	globject::_displayRendererInfo;

globject::globject(void)
{

}

globject::globject(std::string path, GLuint ID) : _ID(ID)
{
	parser.parse(path);
	fill_vao();
}

globject::globject(std::list<std::string> paths, GLuint ID) : _ID (ID)
{

}

globject::~globject(void)
{

}

void		globject::init(void)
{
	/* Init SDL */

	SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(1200, 900, SDL_WINDOW_OPENGL, &globject::_displayWindow, &globject::_displayRenderer);
    SDL_GetRendererInfo(globject::_displayRenderer, &globject::_displayRendererInfo);

	/* Init OpenGL */

    glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
    glEnable( GL_DEPTH_TEST );
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(globject::_displayWindow);

	/* load Models */

    globject n("models/cube.obj", WALL);
	globject::_object[n._ID] = n;
}

void		globject::render(GLuint ID, int status, Matrix model)
{

}

void		globject::render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player*> players)
{

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
	return (progid);
}

void		globject::load_shaders()
{
	glUseProgram(loadshaders("shaders/frag.shader", "shaders/vertex.shader"));
}

void		globject::fill_vao(void)
{
	GLuint vertexBufferID;
	GLuint textBufferID;

	glGenVertexArrays(1, &(_vaoID));
	glGenBuffers(1, &(vertexBufferID));
	glGenBuffers(1, &(textBufferID));

	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * parser._finalVertexSize, parser._finalVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, textBufferID);
	glBufferData(GL_ARRAY_BUFFER, parser._finalTextSize, parser._finalText, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

