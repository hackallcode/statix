#ifndef __COMMON_CONFIG_INCLUDED__
#define __COMMON_CONFIG_INCLUDED__

#include <string>

struct Config {
	short Port;
	size_t ThreadsLimit;
	std::string Root;

	Config(short _port, size_t _threadsLimit, std::string _root)
		: Port(_port)
		, ThreadsLimit(_threadsLimit)
		, Root(_root)
	{}
};

void ParseParams(Config& params, char* argv[], int argc);

#endif // !__COMMON_CONFIG_INCLUDED__
