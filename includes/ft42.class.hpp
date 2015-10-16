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

# define LOG_PATH	"log/debugg.log"

# define SIZE 19

enum ID {
	WALL,
	BOMB,
	FIRE,
	PLAYER,
	BOSS,
	BONUS
}

enum STATUS {

	FIRE_1,			// avant Disparition
	FIRE_2, 		// Grosse flamme

	BOMB_SEC_0, 	// Bombe disparition
	BOMB_SEC_1,		// Avant Explosion
	BOMB_SEC_2,
	BOMB_SEC_3,		// Premiere pose

	WALL_INDESTRUCTIBLE,
	WALL_HP_1,		// va tombe prochaine explosion
	WALL_HP_3,
	WALL_HP_4,		// solide

	PLAYER_NUM_1,
	PLAYER_NUM_2,
	PLAYER_NUM_3,
	PLAYER_NUM_4,
	PLAYER_NUM_5,

	BOSS_1,
	BOSS_2,
	BOSS_3,

	MOB_1,
	MOB_2,
	MOB_3,
	MOB_4,
	MOB_5,

}


class ft42 {
public:
	static bool					logg;

	ft42();
	virtual ~ft42();

	void					w_log( std::string const newEntry );
	void					w_full( std::string const newEntry );
	void					w_error( std::string const newEntry );
	std::string				logTime( std::string const & sentence );

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
