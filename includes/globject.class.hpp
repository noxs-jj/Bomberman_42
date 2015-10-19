// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/19 12:09:01 by rcargou          ###   ########.fr       //
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

class globject {

	public :

		globject(void);
		globject(std::string path, GLuint ID);
		globject(std::list<std::string> paths, GLuint ID);
		~globject(void);

		static void		init(void);
		void			render(GLuint ID, int status, Matrix model);
		static void		render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player> players);
		GLuint						_vaoID;
		GLuint						_vertexBufferSize;
		GLuint						_textBufferSize;
		GLuint						_elemBufferID;
		GLuint						_elemBufferSize;
		GLuint						_ID;
		static SDL_Window			*_displayWindow;
		static SDL_Renderer			*_displayRenderer;
		static SDL_RendererInfo		_displayRendererInfo;
		static						globject _object[100];
		parser						parser;
	
	private :
		void fill_vao(void);

};

#endif
