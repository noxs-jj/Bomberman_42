// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/25 10:17:30 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GLOBJECT_CLASS_HPP
# define GLOBJECT_CLASS_HPP

# include <list>
# include <Matrix.hpp>
# include <entity.class.hpp>
# include <player.class.hpp>
# include <ft42.class.hpp>
# include <iostream>
# include <fstream>
# include <string>
# include <parser.class.hpp>
# include <fcntl.h>
# include <cstring>

class globject {

	public :

		globject(void);
		globject(std::string path, GLuint ID);
		globject(std::list<std::string> paths, GLuint ID);
		~globject(void);

		static void		init(void);
		void			render (int status);
		static void		render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player*> players);
		static void		resize(int x, int y);
		GLuint						_textID[1000];
		GLuint						_textLoc[100];
		GLuint						_textNumber;
		GLuint						_vaoID;
		GLuint						_vertexBufferSize;
		GLuint						_textBufferSize;
		GLuint						_elemBufferID;
		GLuint						_elemBufferSize;
		GLuint						_ID;
		static GLuint				_modelMatID;
		static GLuint				_viewMatID;
		static GLuint				_progid;
		static SDL_Window			*_displayWindow;
		static SDL_Renderer			*_displayRenderer;
		static SDL_RendererInfo		_displayRendererInfo;
		static						globject _object[100];
		static	char				tab[120];
		parser						parser;
	
	private :
		static char *filetobuff(char *path);
		static GLuint loadshaders(char *a, char *b);
		static void load_shaders();
		static void update_key();
		void		load_bmp();
		void		fill_vao(void);

};

#endif
