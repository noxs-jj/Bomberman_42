#ifndef FT42_CLASS_HPP
# define FT42_CLASS_HPP

# include <cstdlib>
# include <cstring>
# include <exception>
# include <fstream>
# include <iostream>
# include <istream>
# include <sstream>
# include <string>
# include <vector>
# include <regex>
# include <unistd.h>
# include <stdlib.h>
# include <set>
# include <algorithm>
# include <list>
# include <stdexcept>
# include <time.h>


# ifdef linux
#		include <GL/gl3.h>
# endif
# ifdef __APPLE__
# 	include <OpenGL/gl3.h>
# endif

# include <SDL.h>
# include <SDL_image.h>

# define LOG_PATH	"log/debugg.log"

# define SIZE 19
# define MAP_Y_SIZE 20
# define MAP_X_SIZE 20

typedef struct	s_point {
	float x;
	float y;
	float z;
}				t_point;

typedef struct  s_key {
	int key_right;
	int key_left;
	int key_up;
	int key_down;
}	t_key;

enum STATUS {
	////
	//// TYPE
	////
	WALL = 0,
	BOMB,
	FIRE,
	PLAYER,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	BOSS,
	ENEMY,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	BONUS,
	EMPTY,

	////
	//// BOSS NAME
	////
	BOSS_A,
	BOSS_B,
	BOSS_C,

	////
	//// STATUS
	////

	NO_STATUS,
	FIRE_1,			// avant Disparition
	FIRE_2, 		// Grosse flamme

	// Uniquement pour le moteur de jeu
	BOMB_SEC_0, 	// Bombe disparition
	BOMB_SEC_1,		// Avant Explosion
	BOMB_SEC_2,		// Avant Explosion
	BOMB_SEC_3,		// Avant Explosion

	WALL_INDESTRUCTIBLE,
	WALL_HP_1,		// va tombe prochaine explosion
	WALL_HP_2,
	WALL_HP_3,
	WALL_HP_4,

	FLOOR,
	//
	/// Direction
	//
	DIR_UP,
	DIR_BOTTOM,
	DIR_LEFT,
	DIR_RIGHT,
	MAX_ENUM
};


class ft42 {
public:
	static bool					logg;
	float						zoom;

	ft42();
	virtual ~ft42();

	void					w_log( std::string const newEntry );
	void					w_full( std::string const newEntry );
	void					w_error( std::string const newEntry );
	std::string				logTime( std::string const & sentence );
	bool					check_coord_exist( int x, int y );

	std::ofstream &			getLogFD( void );


private:
	static std::string		logFileName;
	static std::ofstream	lodFD;

	std::string				result;
	time_t					timer;
	struct tm *				timeinfo;
	char					buffer[80];
};

#endif
