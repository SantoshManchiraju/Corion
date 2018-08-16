/*
 * Logger.h
 *
 *  Created on: Aug 2, 2017
 *      Author: bob
 */

#ifndef SRC_LOGGER_LOGGER_H_
#define SRC_LOGGER_LOGGER_H_

#include <iostream>
#include <string.h>

class Logger {

public:

	Logger();
	~Logger();

	static void INFO(std::string text);
	static void DEBUG(std::string text);
	static void WARNING(std::string text);
	static void ERR(std::string text);

	static void INFO(std::string file, long line, std::string text);
	static void DEBUG(std::string file, long line, std::string text);
	static void WARNING(std::string file, long line, std::string text);
	static void ERR(std::string file, long line, std::string text);
};


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_INFO(...) Logger::INFO(__FILENAME__, __LINE__,__VA_ARGS__);
#define LOG_DEBUG(...) Logger::DEBUG(__FILENAME__, __LINE__,__VA_ARGS__);
#define LOG_WARN(...) Logger::WARNING(__FILENAME__, __LINE__,__VA_ARGS__);
#define LOG_ERR(...) Logger::ERR(__FILENAME__, __LINE__,__VA_ARGS__);

#endif /* SRC_LOGGER_LOGGER_H_ */
