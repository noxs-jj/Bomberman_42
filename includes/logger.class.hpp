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

/* *************************************** */
/* Easy logging class for the average noob */
/*        somewhat log4j compatible        */
/* *************************************** */

#ifndef LOGGER_CLASS_HPP
# define LOGGER_CLASS_HPP
# include <stdarg.h>
# include <iostream>
# include <fstream>
# include <time.h>
# include <sstream>
# include <iomanip>
# include <mutex>

# include <time.h>
# include <sys/time.h>

# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif

class Logger {
	public:

		Logger() = delete;
		Logger(std::string fileName);
		Logger(Logger const & rhs);
		Logger & operator=(Logger const & rhs);
		~Logger();

		void fatal(const char *fmt, ...);
		void error(const char *fmt, ...);
		void warning(const char *fmt, ...);
		void info(const char *fmt, ...);
		void debug(const char *fmt, ...);
		void trace(const char *fmt, ...);

	private:

		void log(std::string prefix, const char *fmt, va_list args);

		static std::string _getTimestamp();

		std::string const m_fileName;
		std::ofstream m_outputFileStream = std::ofstream(m_fileName);
		std::mutex * m_mutex;
};

#endif // LOGGER_CLASS_HPP
