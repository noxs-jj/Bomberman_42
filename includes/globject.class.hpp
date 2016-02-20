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
# include <algorithm>
# include <vector>

class globject {

	public :

		globject(void);
		globject(std::string path, GLuint ID, float zoom);
		~globject(void);

		static void               init(float sizeX, float sizeY);
		void                      render (int status);
		static void               render_all(Entity ***map, std::list<Entity*> players, SDL_Surface *menu);
		static void               resize(int x, int y);
		static void               spin(float x, float y);
		static void               reinit_level(int env);
		GLuint                    _textID[1000];
		GLuint                    _textLoc[100];
		GLuint                    _textNumber;
		GLuint                    _vaoID;
		GLuint                    _vertexBufferSize;
		GLuint                    _textBufferSize;
		GLuint                    _elemBufferID;
		GLuint                    _elemBufferSize;
		GLuint                    _ID;
		GLfloat                   _zoom;
		static int                space;
		static GLfloat            spinx;
		static GLfloat            spinz;
		static int                doIspin;
		static GLuint             _modelMatID;
		static GLuint             _viewMatID;
		static GLuint             _progid;
		static GLuint             _keyFrameID;
		static GLuint             _legPos;
		static SDL_Window         *_displayWindow;
		static SDL_Renderer       *_displayRenderer;
		static SDL_RendererInfo   _displayRendererInfo;
		static globject           _object[100];
		Parser                    parser;
		static int                mapX_size;
		static int                mapY_size;

		// Jean-Jacques modification pour affichage mise en public pour acces
		static void               display_menu(SDL_Surface *menu);
        static void               get_sdl_information();
        static void               set_float_width_height(float *width, float *height);
        static void               resize_from_actual_resolution();

	private :
		static GLfloat            get_leg_pos(int model);
		static char               *filetobuff(char *path);
		static GLuint             loadshaders(char *a, char *b);
		static void               load_shaders();
		static void               skybox(t_point e);
		static void               update_key();
		void                      load_bmp();
		void                      load_png();
		void                      fill_vao(void);

};

#endif
