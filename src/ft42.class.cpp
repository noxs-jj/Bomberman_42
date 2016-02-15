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

#include <ft42.class.hpp>
#include <globject.class.hpp>

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

void 			ft42::w_exception( std::string const newEntry ) {
	if (true == ft42::logg)
		this->w_log(newEntry);
	std::cout << newEntry << std::endl;
	ft42::lodFD << ft42::logTime( newEntry ) << std::endl;
	throw std::exception();
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

	memset(&this->ft_42_buffer, 0, 80);
	time(&this->ft_42_timer);
	this->ft_42_timeinfo = localtime (&this->ft_42_timer);
	strftime (this->ft_42_buffer, 80, "%Y/%m/%d %H:%M:%S ", this->ft_42_timeinfo);
	ss << this->ft_42_buffer;
	this->ft_42_result = ss.str() + sentence;
	return (this->ft_42_result);
}

bool		ft42::check_coord_exist( int x, int y ) {
	if (x >= 0 && x < globject::mapX_size && y >= 0 && y < globject::mapY_size)
		return true;
	return false;
}

std::ofstream &	ft42::getLogFD( void ) { return ( ft42::lodFD ); }

ft42::ft42() : zoom(1) {}

ft42::~ft42() {}
