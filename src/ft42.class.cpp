#include <ft42.class.hpp>

std::string			ft42::logFileName;
std::ofstream		ft42::lodFD;
bool				ft42::logg;

void			ft42::w_full( std::string const newEntry ) {
	if (true == ft42::logg) {
		std::cout << newEntry << std::endl;
		ft42::lodFD << ft42::logTime( newEntry ) << std::endl;
	}
}

void			ft42::w_error( std::string const newEntry ) {
	if (true == ft42::logg) {
		std::cerr << newEntry << std::endl;
		this->w_log(newEntry);
	}
}

void			ft42::w_log( std::string const newEntry ) {
	if (true == ft42::logg) {
		if ( ft42::logFileName.empty() && ft42::lodFD.is_open() == 0) {
			std::stringstream	ss;
			ss << LOG_PATH;
			ft42::lodFD.open(ss.str(), std::ofstream::out | std::ofstream::app);
			this->lodFD << std::endl << std::endl << std::endl << std::endl << std::endl;
			if (this->lodFD.fail() == 1) {
				std::cerr << "Log File Open error" << std::endl;
				throw std::exception();
			}
		}
		this->lodFD << ft42::logTime( newEntry ) << std::endl;
	}
}

std::string		ft42::logTime( std::string const & sentence ) {
	std::stringstream	ss;

	memset(&this->buffer, 0, 80);
	time(&this->timer);
	this->timeinfo = localtime (&this->timer);
	strftime (this->buffer, 80, "%Y/%m/%d %H:%M:%S ", this->timeinfo);
	ss << this->buffer;
	this->result = ss.str() + sentence;
	return (this->result);
}

bool		ft42::check_coord_exist( int x, int y ) {
	if (x >= 0 && x < MAP_X_SIZE && y >= 0 && y < MAP_Y_SIZE)
		return true;
	return false;
}

std::ofstream &	ft42::getLogFD( void ) { return ( ft42::lodFD ); }

ft42::ft42() : zoom(1) {}

ft42::~ft42() {}
