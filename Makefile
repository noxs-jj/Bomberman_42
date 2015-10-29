# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noxsnono <noxsnono@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/29 14:06:15 by vjacquie          #+#    #+#              #
#    Updated: 2015/10/29 17:37:51 by noxsnono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PLATFORM := $(shell uname)

#Mac --	brew install sdl2 sdl2_image sdl2_mixer
ifeq "$(PLATFORM)" "Darwin"
	GLUT = -framework Appkit -framework OpenGL
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif
#Linux -- apt-get install libsdl2-dev libsdl2-gfx-dev freeglut3 freeglut3-dev
# libsdl2-image-dev libsdl2-mixer-dev glee-dev libgles2-mesa-dev
# freeglut3 freeglut3-dev libglew-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx
ifeq "$(PLATFORM)" "Linux"
	GLUT = -lGL -lGLU -lglut -lGLEW -lm
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif

CXX = 			clang++

NAME =			bomberman

CFLAGS =		-std=gnu++11 -Wall -Wextra -Werror
# CFLAGS =		-std=gnu++11

INCLUDE =		-I includes/ -I rc_lib/rc_math/

SDL_INCLUDE =	`sdl2-config --cflags` -I $HOME/.brew/include/SDL

SDL_LIB =		`sdl2-config --libs` -lSDL2_image -lSDL2_mixer

HEAD = 			includes/ft42.class.hpp \
				includes/entity.class.hpp \
				includes/event.class.hpp \
	 			includes/main.hpp \
				includes/wall.class.hpp \
				includes/fire.class.hpp \
				includes/bomb.class.hpp \
				includes/player.class.hpp \
				includes/enemy.class.hpp \
				includes/boss.class.hpp \
				includes/globject.class.hpp \
				includes/Matrix.hpp \
				includes/parser.class.hpp \
				includes/soundrender.class.hpp

SRC = 			src/ft42.class.cpp \
				src/entity.class.cpp \
				src/event.class.cpp \
				src/main.cpp \
				src/wall.class.cpp \
				src/bomb.class.cpp \
				src/fire.class.cpp \
				src/player.class.cpp \
				src/enemy.class.cpp \
				src/boss.class.cpp \
				src/globject.class.cpp \
				src/Matrix.cpp \
				src/parser.class.cpp \
				src/soundrender.class.cpp

OBJ = 			$(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp $(HEAD)
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

soundtest: all
	$(CXX) src/soundrender.class.cpp $(CFLAGS) $(INCLUDE) $(SDL_INCLUDE) $(CFLAGS) `sdl2-config --libs` `sdl2-config --cflags` -lSDL2_mixer "tests/soundrender.test.cpp"

sdltest:
	$(CXX) $(CFLAGS) -stdlib=libc++ -o testsdl2 test/test_sdl2.cpp \
	-framework opengl `sdl2-config --libs` `sdl2-config --cflags`

.PHONY: all clean fclean re
