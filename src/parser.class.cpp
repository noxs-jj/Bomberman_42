// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   parser.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/19 10:57:52 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include <parser.class.hpp>

parser::parser(void)
{

}

parser::parser(std::string path)
{
	parse(path);
}

parser::~parser()
{

}

void parser::parse(std::string path)
{
	_textSize = 0;
	_vertexSize = 0;
	_finalVertexSize = 0;
	_finalTextSize = 0;
	std::string line;
	std::ifstream myfile(path.c_str());

	if (myfile.is_open())
	{
		while (getline (myfile,line))
		{
			if (!line.compare(0, 2, "v "))
				add_vertex(line);
			else if (!line.compare(0, 2, "vt"))
				add_text(line);
			else if (!line.compare(0, 2, "f "))
				add_indice(line);
			std::cout << line << '\n';
		}
		myfile.close();
	}
	else
	{
		std::cout << "Error in class gl_object: unable to open "
					<< path << ". Exiting program...\n";
		exit(0);
	}
}

void parser::add_vertex(std::string str)
{
	int i;

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

void parser::add_text(std::string str)
{
	int i;

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

void parser::add_indice(std::string str)
{
	int i;
	int text[3];
	int vertex[3];

	i = 2;
	while (str[i] == ' ')
		i++;
	vertex[0] = std::atoi(str.c_str() + i) - 1;
	while (str[i] != '/')
		i++;
	i++;
	text[0] = std::atoi(str.c_str() + i) - 1;

	while (str[i] != ' ')
		i++;
	while(str[i] == ' ')
		i++;
	vertex[1] = std::atoi(str.c_str() + i) - 1;
	while(str[i] != '/')
		i++;
	i++;
	text[1] = std::atoi(str.c_str() + i) - 1;

	while (str[i] != ' ')
		i++;
	while(str[i] == ' ')
		i++;
	vertex[2] = std::atoi(str.c_str() + i) - 1;
	while(str[i] != '/')
		i++;
	i++;
	text[2] = std::atoi(str.c_str() + i) - 1;

	for (int e = 0; e < 3; e++)
	{
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
}

