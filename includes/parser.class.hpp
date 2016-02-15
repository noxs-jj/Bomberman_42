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

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include <ft42.class.hpp>

class Parser {

public :

	Parser(void);
	Parser(std::string path);
	~Parser(void);

	void parse(std::string path, int Neg);

	GLfloat			*_vertex;
	GLfloat			*_text;
	GLfloat			*_finalVertex;
	GLfloat			*_finalText;
	GLuint			_textSize;
	GLuint			_vertexSize;
	GLuint			_finalVertexSize;
	GLuint			_finalTextSize;
	GLuint			_textNum;
	GLfloat			*_textID;
	GLuint			_textIDSize;
	std::string		*_texture;

private :

	int		foundText;
	int		foundTexture(std::string str);
	void	add_texture(std::string str);
	void	add_indice(std::string str, float neg);
	void	add_vertex(std::string str);
	void	add_text(std::string str);

    Parser( Parser const & src ) = delete;
};

#endif
