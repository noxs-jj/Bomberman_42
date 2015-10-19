// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/19 12:10:17 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <globject.class.hpp>

globject			globject::_object[100];
SDL_Window			*_displayWindow;
SDL_Renderer		*_displayRenderer;
SDL_RendererInfo	_displayRendererInfo;

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
	/* load Models */

	globject n("models/cube.obj", WALL);
	globject::_object[n._ID] = n;

	/* Init SDL */

	SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(1200, 900, SDL_WINDOW_OPENGL, &globject::_displayWindow, &globject::_displayRenderer);
    SDL_GetRendererInfo(globject::_displayRenderer, &globject::_displayRendererInfo);

	/* Init OpenGL */

    glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
    glEnable( GL_DEPTH_TEST );
	glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(globject::_displayWindow);
	sleep(100);

}

void		globject::render(GLuint ID, int status, Matrix model)
{

}
void		globject::render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player> players)
{

}

void		globject::fill_vao(void)
{

}

