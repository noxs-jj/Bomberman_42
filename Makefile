# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinz <vinz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/29 14:06:15 by vjacquie          #+#    #+#              #
#    Updated: 2015/10/20 17:10:26 by vinz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PLATFORM := $(shell uname)

#Mac --	brew install sdl2
ifeq "$(PLATFORM)" "Darwin"
	GLUT = -framework Appkit -framework OpenGL
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif
#Linux -- apt-get install libsdl2-dev libsdl2-gfx-dev freeglut3 freeglut3-dev
ifeq "$(PLATFORM)" "Linux"
	GLUT = -lGL -lGLU -lglut
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif

CXX = 			g++

NAME =			binaire

CFLAGS =		-std=gnu++11

INCLUDE =		-I includes/ -I rc_lib/rc_math/

SDL_INCLUDE =	`sdl2-config --cflags`

SDL_LIB =		`sdl2-config --libs`

HEAD = 			includes/ft42.class.hpp \
				includes/entity.class.hpp \
				includes/event.class.hpp \
	 			includes/main.hpp \
				includes/wall.class.hpp \
				includes/fire.class.hpp \
				includes/bomb.class.hpp \
				includes/player.class.hpp \
				includes/enemy.class.hpp \
				includes/boss.class.hpp
				# includes/globject.class.hpp \
				# includes/Matrix.hpp \
				# includes/parser.class.hpp

SRC = 			src/ft42.class.cpp \
				src/entity.class.cpp \
				src/event.class.cpp \
				src/main.cpp \
				src/wall.class.cpp \
				src/bomb.class.cpp \
				src/fire.class.cpp \
				src/player.class.cpp \
				src/enemy.class.cpp \
				src/boss.class.cpp
				# src/globject.class.cpp \
				# src/Matrix.cpp \
				# src/parser.class.cpp

OBJ = 			$(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp $(HEAD)
	clear
	@$(CXX) $(CFLAGS)  $(INCLUDE) $(SDL_INCLUDE) $(CFLAGS) -c $< -o $@

all: $(NAME)
	@echo "./gomoku -iathink -log -depth=[1-10]"

$(NAME): $(OBJ)
	$(COMMAND)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

sdltest:
	clear
	$(CXX) $(CFLAGS) -stdlib=libc++ -o testsdl2 test/test_sdl2.cpp \
	-framework opengl `sdl2-config --libs` `sdl2-config --cflags`

.PHONY: all clean fclean re
