#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include <ft42.class.hpp>

class parser {

public :

	parser(void);
	parser(std::string path);
	~parser(void);

	void parse(std::string path, int Neg);

	GLfloat			_vertex[10000];
	GLfloat			_text[10000];
	GLfloat			_finalVertex[10000];
	GLfloat			_finalText[10000];
	GLuint			_textSize;
	GLuint			_vertexSize;
	GLuint			_finalVertexSize;
	GLuint			_finalTextSize;
	GLuint			_textNum;
	GLfloat			_textID[10000];
	GLuint			_textIDSize;
	std::string		_texture[100];

private :

	int		foundText;
	int		foundTexture(std::string str);
	void	add_texture(std::string str);
	void	add_indice(std::string str, float neg);
	void	add_vertex(std::string str);
	void	add_text(std::string str);
};

#endif
