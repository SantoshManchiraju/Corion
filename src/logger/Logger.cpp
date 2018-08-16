/*
 * Logger.cpp
 *
 *  Created on: Aug 2, 2017
 *      Author: bob
 */

#include "Logger.h"

Logger::Logger() {
}

Logger::~Logger() {
}

void Logger::INFO(std::string text) {
	std::cout << "\033[32m" << text << "\033[0m\n" << std::endl;
}

void Logger::DEBUG(std::string text) {
	std::cout << "\033[1;32m" << text << "\033[0m\n" << std::endl;
}

void Logger::WARNING(std::string text) {
	std::cout << "\033[33m" << text << "\033[0m\n" << std::endl;
}

void Logger::ERR(std::string text) {
	std::cout << "\033[1;31m" << text << "\033[0m\n" << std::endl;
}

void Logger::INFO(std::string file, long line, std::string text) {
	std::cout << file << "(" << line << "): " << "\033[32m" << text
			<< "\033[0m\n" << std::endl;
}

void Logger::DEBUG(std::string file, long line, std::string text) {
	std::cout << file << "(" << line << "): " << "\033[1;32m" << text
			<< "\033[0m\n" << std::endl;
}

void Logger::WARNING(std::string file, long line, std::string text) {
	std::cout << file << "(" << line << "): " << "\033[33m" << text
			<< "\033[0m\n" << std::endl;
}

void Logger::ERR(std::string file, long line, std::string text) {
	std::cout << file << "(" << line << "): " << "\033[1;31m" << text
			<< "\033[0m\n" << std::endl;
}
