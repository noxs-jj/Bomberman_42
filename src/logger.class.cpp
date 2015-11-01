/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 15:55:13 by nmohamed          #+#    #+#             */
/*   Updated: 2015/11/01 16:53:45 by nmohamed         ###   ########.fr       */
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
	m_outputFileStream << "\033[00m" << std::endl;
}

void Logger::log(std::string prefix, const char *fmt, va_list args) {
	char *str;
	vasprintf(&str, fmt, args);
	m_outputFileStream << prefix << "\t-- " << _getTimestamp() << "\t-- " << str;
	free(str);
}

void Logger::fatal(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("\033[41;01m" "[fatal]", fmt, args);
	m_outputFileStream << "\033[00m" << std::endl;
	m_mutex->unlock();
}

void Logger::error(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("\033[31;01m" "[error]", fmt, args);
	m_outputFileStream << "\033[00m" << std::endl;
	m_mutex->unlock();
}

void Logger::warning(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("\033[43;01m" "[warn]", fmt, args);
	m_outputFileStream << "\033[00m" << std::endl;
	m_mutex->unlock();
}

void Logger::info(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("\033[34;01m" "[info]", fmt, args);
	m_outputFileStream << "\033[00m" << std::endl;
	m_mutex->unlock();
}

void Logger::debug(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("\033[37;01m" "[debug]", fmt, args);
	m_outputFileStream << "\033[00m" << std::endl;
	m_mutex->unlock();
}

void Logger::trace(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	m_mutex->lock();
	log("trace", fmt, args);
	m_outputFileStream << std::endl;
	m_mutex->unlock();
}

std::string Logger::_getTimestamp() {
	std::stringstream ss;
	timespec ts;
	clock_gettime(0, &ts);
	ss << ts.tv_sec << "." << ts.tv_nsec;
	return ss.str();
}
