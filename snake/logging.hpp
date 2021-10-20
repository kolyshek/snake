#ifndef LOGGING_H
#define LOGGING_H

#include<iostream>

enum class LogType
{
	DISPLAY,
	WARNING,
	ERROR
};

#define KP_LOG(msg) \
	std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl;

#endif // !LOGGING_H