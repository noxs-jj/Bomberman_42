PLATFORM := $(shell uname)

#Mac --	brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
ifeq "$(PLATFORM)" "Darwin"
	GLUT = -framework Appkit -framework OpenGL
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif

#Linux -- apt-get install libsdl2-dev libsdl2-gfx-dev freeglut3 freeglut3-dev
# libsdl2-image-dev libsdl2-mixer-dev glee-dev libgles2-mesa-dev
# freeglut3 freeglut3-dev libglew-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx
# libglfw3-dev
ifeq "$(PLATFORM)" "Linux"
	GLUT = -lGL -lGLU -lglut -lSDL2 -lSDL2main -lGLEW -lGLU -lGL -lSDL2 -lSDL2main -lGLEW -lGLU -lGL
	COMMAND = $(CXX) $(CFLAGS) $(SDL_LIB) $(GLUT) $(OBJ) -o $(NAME)
endif

CXX = 			clang++

NAME =			bomberman


CFLAGS =		-std=gnu++11 -Wall -Wextra -Werror -pedantic	

INCLUDE =		-I includes/ -I rc_lib/rc_math/

SDL_INCLUDE =	`sdl2-config --cflags` -I $(HOME)/.brew/include/SDL
SDL_LIB =			`sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

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
						includes/soundrender.class.hpp \
						includes/Menu.class.hpp \
						includes/GameLauncher.class.hpp \
						includes/mapparser.class.hpp \
						includes/ia.class.hpp \
						includes/joystick.hpp

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
						src/soundrender.class.cpp \
						src/menu/Menu.class.cpp \
						src/GameLauncher.class.cpp \
						src/map/mapparser.class.cpp \
						src/ia.class.cpp \
						src/joystick/joystick.cpp

OBJ := $(SRC:.cpp=.cpp.o)

.PHONY: all clean fclean re soundtest loggertest sdltest
.SILENT: $(CXX) $(NAME) $(CFLAGS) $(INCLUDE) $(SDL_INCLUDE) $(SDL_LIB) $(HEAD) $(SRC) $(OBJ) %.cpp.o all $(NAME) clean fclean re soundtest loggertest sdltest

default: all

%.cpp.o: %.cpp $(HEAD)
	@$(CXX) $(CFLAGS) $(INCLUDE) $(SDL_INCLUDE) $(CFLAGS) -c $< -o $@

all: $(NAME)
	@echo "./bomberman"

$(NAME): $(OBJ)
	$(COMMAND)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

soundtest:
	$(CXX) src/ft42.class.cpp src/soundrender.class.cpp $(CFLAGS) \
																											$(INCLUDE) \
																											$(SDL_INCLUDE) \
																											$(CFLAGS) `sdl2-config --libs` `sdl2-config --cflags` -lSDL2_mixer "tests/soundrender.test.cpp" -lpthread
loggertest:
	$(CXX) src/logger.class.cpp $(CFLAGS) \
															$(INCLUDE) \
															$(CFLAGS) "tests/logger.test.cpp" -lpthread

sdltest:
	$(CXX) $(CFLAGS) -stdlib=libc++ -o testsdl2 test/test_sdl2.cpp \
	-framework opengl `sdl2-config --libs` `sdl2-config --cflags`
