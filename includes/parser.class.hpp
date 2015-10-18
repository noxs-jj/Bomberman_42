#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include <ft42.class.hpp>

class parser {

public :

	parser(std::string path);
	~parser(void);

	GLfloat _vertex[1000];
	GLfloat _text[1000];
	GLfloat _finalVertex[1000];
	GLfloat _finalText[1000];
	GLuint  _textSize;
	GLuint  _vertexSize;
	GLuint  _finalVertexSize;
	GLuint  _finalTextSize;
private :

	void add_indice(std::string str);
	void add_vertex(std::string str);
	void add_text(std::string str);
	parser(void);
};

#endif
