// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   globject.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
/*   Updated: 2015/10/18 20:16:38 by rcargou          ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef GLOBJECT_CLASS_HPP
# define GLOBJECT_CLASS_HPP

# include <list>
# include <Matrix.hpp>
# include <entity.class.hpp>
# include <player.class.hpp>
# include <iostream>
# include <fstream>
# include <string>

class globject {

	public :

		globject(std::string path, GLuint ID);
		globject(std::string path[5], GLuint ID);
		~globject(void);

		static void		init(void);
		void			render(GLuint ID, int status, Matrix model);
		static void		render_all(Entity map[MAP_Y_SIZE][MAP_X_SIZE], std::list<Player> players);
		GLuint			_vaoID;
		GLuint			_vertexBufferSize;
		GLuint			_textBufferSize;
		GLuint			_elemBufferID;
		GLuint			_elemBufferSize;
		const			GLuint _ID;
		static			globject _object[10];

	private :
		void fill_vao(GLfloat *vertex, GLfloat *textures, GLuint vertexSize, GLuint textSize);
		globject(void);

};

#endif
