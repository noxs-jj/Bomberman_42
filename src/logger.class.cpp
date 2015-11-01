/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 15:55:13 by nmohamed          #+#    #+#             */
/*   Updated: 2015/11/01 15:55:14 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.class.hpp"

Logger::Logger(std::string fileName) : m_fileName(fileName), m_mutex(new std::mutex) {
	;
}

Logger::Logger(Logger const & rhs)
	: m_outputFileStream(std::ofstream(rhs.m_fileName))
	, m_mutex(rhs.m_mutex) {
	;
}

Logger & Logger::operator=(Logger const & rhs) {
	if (this != &rhs) {
		m_outputFileStream = std::ofstream(rhs.m_fileName);
		m_mutex = rhs.m_mutex;
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

	m_mutex->lock();
	m_outputFileStream << "[ LOG ] [" << _getTimestamp() << "] " << str << std::endl;
	m_mutex->unlock();
	free(str);
}

std::string Logger::_getTimestamp() {
	std::stringstream ss;
	timespec ts;
	clock_gettime(0, &ts);
	ss << ' ' << ts.tv_sec << "." << std::setfill(' ') << std::setw(10) << std::left << ts.tv_nsec;
	return ss.str();
}
