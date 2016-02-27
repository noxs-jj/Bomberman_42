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

# include <parser.class.hpp>

Parser::Parser(void) {
    // FUITE START
	_vertex = new GLfloat[500000];
	_text = new GLfloat[500000];
	_finalVertex = new GLfloat[500000];
	_finalText = new GLfloat[500000];
	_textID = new GLfloat[500000];
	_texture = new std::string[100];
    // std::cout << "Parser::Parser(void)" << std::endl;
    // FUITE END
	_textSize = 0;
	_textIDSize = 0;
	_vertexSize = 0;
	_finalVertexSize = 0;
	_finalTextSize = 0;
	_textNum  = 0;
	foundText = 0;
}

Parser::Parser(std::string path) {
	parse(path, 0);
}

Parser::~Parser() {
    // std::cout << "Parser::~Parser() DESTRUCT" << std::endl;
}

void	Parser::parse(std::string path, int neg) {
	/*
	_vertex = new GLfloat[100000];
	_text = new GLfloat[100000];
	_finalVertex = new GLfloat[100000];
	_finalText = new GLfloat[100000];
	_textID = new GLfloat[100000];
	_texture = new std::string[100];
    */
	_textSize = 0;
	_textIDSize = 0;
	_vertexSize = 0;
	_finalVertexSize = 0;
	_finalTextSize = 0;
	_textNum  = 0;
	foundText = 0;
	std::string line;
	std::ifstream myfile(path.c_str());

	if (myfile.is_open()) 	{
		while (getline (myfile,line)) 		{
			if (!line.compare(0, 2, "v "))
				add_vertex(line);
			else if (!line.compare(0, 2, "vt"))
				add_text(line);
			else if (!line.compare(0, 2, "f "))
				add_indice(line, neg);
			else if (!line.compare(0, 6, "usemtl"))
				add_texture(line);
		}
		myfile.close();
	}
	else 	{
		std::cout << "Error in class gl_object: unable to open " \
			<< path << ". Exiting program...\n";
		exit(0);
	}
}

int		strcmp(char *a, char *b) {
	for (int i = 0; b[i]; i++)
		if (a[i] != b[i])
			return (-1);
	return (0);
}

int		Parser::foundTexture(std::string s) {
	std::string	str;
	int			e;

	str = s;
	for (e = 0; str[e] && str[e] != ' '; e++)
		;
	str[e] = 0;
	for (size_t i = 0; i < _textNum; i++) 	{
		if (!strcmp(str.c_str(), _texture[i].c_str()))
			return (i);
		// else
		// 	std::cout << str << "" << _texture[i] << "e" << std::endl;
	}
	return (-1);
}

void	Parser::add_texture(std::string str) {
	int	i;

	i = 1;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	str = &str[i];
	if (foundTexture(str) == -1) 	{
		_texture[_textNum] = str;
		_textNum++;
		foundText = _textNum - 1;
	}
	else
		foundText = foundTexture(str);
}

void	Parser::add_vertex(std::string str) {
	int	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	_vertex[_vertexSize] = std::atof(str.c_str() + i);
	_vertexSize++;
	while(str[i] != ' ')
		i++;
	while(str[i] == ' ')
		i++;
	_vertex[_vertexSize] = std::atof(str.c_str() + i);
	_vertexSize++;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	_vertex[_vertexSize] = std::atof(str.c_str() + i);
	_vertexSize++;
}

void Parser::add_text(std::string str) {
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	_text[_textSize] = std::atof(str.c_str() + i);
	_textSize++;
	while(str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	_text[_textSize] = std::atof(str.c_str() + i);
	_textSize++;
}

void Parser::add_indice(std::string str, float neg) {
	int	i;
	int	text[3];
	int	vertex[3];

	neg = neg * 42;
	i = 1;
	while (str[i] == ' ')
		i++;
	vertex[0] = std::atof(str.c_str() + i) - 1;
	while (str[i] != '/')
		i++;
	i++;
	text[0] = std::atof(str.c_str() + i) - 1;

	while (str[i] != ' ')
		i++;
	while(str[i] == ' ')
		i++;
	vertex[1] = std::atof(str.c_str() + i) - 1;
	while(str[i] != '/')
		i++;
	i++;
	text[1] = std::atof(str.c_str() + i) - 1;

	while (str[i] != ' ')
		i++;
	while(str[i] == ' ')
		i++;
	vertex[2] = std::atof(str.c_str() + i) - 1;
	while(str[i] != '/')
		i++;
	i++;
	text[2] = std::atof(str.c_str() + i) - 1;
	for (int e = 0; e < 3; e++) 	{
		_finalVertex[_finalVertexSize] = _vertex[3 * vertex[e]];
		_finalVertexSize++;
		_finalVertex[_finalVertexSize] = _vertex[3 * vertex[e] + 1];
		_finalVertexSize++;
		_finalVertex[_finalVertexSize] = _vertex[3 * vertex[e] + 2];
		_finalVertexSize++;

		_finalText[_finalTextSize] = _text[2 * text[e]];
		_finalTextSize++;
		_finalText[_finalTextSize] = _text[2 * text[e] + 1];
		_finalTextSize++;
	}
	_textID[_textIDSize] = foundText;
	_textIDSize++;
	_textID[_textIDSize] = foundText;
	_textIDSize++;
	_textID[_textIDSize] = foundText;
	_textIDSize++;
}
