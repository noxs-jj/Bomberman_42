#ifndef LOGGER_CLASS_HPP
# define LOGGER_CLASS_HPP
# include <stdarg.h>
# include <iostream>
# include <fstream>

class Logger {
	public:

		Logger() = delete;
		Logger(std::string fileName);
		Logger(Logger const & rhs);
		Logger & operator=(Logger const & rhs);
		~Logger();

		void log(const char *fmt, ...);

	private:

		std::string const m_fileName;
		std::ofstream m_outputFileStream = std::ofstream(m_fileName);
};

#endif // LOGGER_CLASS_HPP
