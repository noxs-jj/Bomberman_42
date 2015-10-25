#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include <ft42.class.hpp>

class parser {

public :

	parser(void);
	parser(std::string path);
	~parser(void);

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
};

#endif
