// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
/*   Updated: 2015/10/18 20:22:36 by rcargou          ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include <globject.class.hpp>

globject::globject(std::string path, GLuint ID) : _ID(ID)
{

}

globject::globject(std::string path[5], GLuint ID) : _ID (ID)
{

}

globject::~globject(void)
{

}

void		globject::init(void)
{

}

void		globject::render(GLuint ID, int status, Matrix model)
{

}
void		globject::render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player> players)
{

}

void		globject::fill_vao(GLfloat *vertex, GLfloat *textures, GLuint vertexSize, GLuint textSize)
{

}

