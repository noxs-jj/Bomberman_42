/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 15:55:04 by nmohamed          #+#    #+#             */
/*   Updated: 2015/11/01 16:36:30 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
