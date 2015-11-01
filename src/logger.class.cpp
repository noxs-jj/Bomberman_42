#include "logger.class.hpp"

Logger::Logger(std::string fileName) : m_fileName(fileName) {
	;
}

Logger::Logger(Logger const & rhs)
	: m_outputFileStream(std::ofstream(rhs.m_fileName)) {
	;
}

Logger & Logger::operator=(Logger const & rhs) {
	if (this != &rhs) {
		m_outputFileStream = std::ofstream(rhs.m_fileName);
	}
	return (*this);
}

Logger::~Logger() {
	;
}

void Logger::log(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char *str;
	vasprintf(&str, fmt, args);
	m_outputFileStream << "[LOG] " << str << std::endl;
	free(str);
}
