# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/29 14:06:15 by vjacquie          #+#    #+#              #
#    Updated: 2015/10/16 16:38:02 by rcargou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PLATFORM := $(shell uname)

#Mac --	brew install sdl2
ifeq "$(PLATFORM)" "Darwin"
	GLUT = -framework GLUT -framework OpenGL -framework Cocoa
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) $(LIBRC_MATH) -o $(NAME)
endif
#Linux -- apt-get install libsdl2-dev libsdl2-gfx-dev freeglut3 freeglut3-dev
ifeq "$(PLATFORM)" "Linux"
	GLUT = -lGL -lGLU -lglut
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) $(LIBRC_MATH) -o $(NAME)
endif

CXX = 			clang++

NAME =			binaire

CFLAGS =		-Wall -Werror -Wextra -std=gnu++11

INCLUDE =		-I includes/ -I rc_lib/rc_math/

LIBRC_MATH =	rc_lib/rc_math/librcmath.a

SDL_INCLUDE =	`sdl2-config --cflags`

SDL_LIB =		`sdl2-config --libs`

HEAD = 			includes/ft42.class.hpp \
	 			includes/main.hpp

SRC = 			src/ft42.class.cpp \
				src/main.cpp

OBJ = 			$(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp $(HEAD)
	clear
	@$(CXX) $(CFLAGS)  $(INCLUDE) $(SDL_INCLUDE) $(CFLAGS) $(LIBRC_MATH) -c $< -o $@

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
