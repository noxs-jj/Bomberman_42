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

# include "rc_math.h"

# define LOG_PATH	"log/debugg.log"

# define SIZE 19

typedef std::vector< std::vector<int> > Map;


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
