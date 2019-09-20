#include <iostream>
#include <clocale>
#include <csignal>
#include <fstream>
#include "Server/Server.h"

namespace fs = std::filesystem;

std::unique_ptr<serv::Server> GlobalServer;

struct Params {
	short Port;
	size_t ThreadsLimit;
	std::string Root;
};

void ParseConfig(Params& params, fs::path const& filename)
{
	// File not found
	if (!fs::exists(filename)) {
		return;
	}

	// Read data of file
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		return;
	}

	std::string line;
	while (std::getline(fin, line)) {
		size_t i = 0;
		std::string key;
		for (; i < line.size() && line[i] != ' '; ++i) {
			key += line[i];
		}
		std::string value;
		for (++i; i < line.size() && line[i] != ' '; ++i) {
			value += line[i];
		}

		if (key == "port") {
			params.Port = std::stoi(value);
		}
		else if (key == "thread_limit") {
			params.ThreadsLimit = std::stoi(value);
		}
		else if (key == "document_root") {
			params.Root = value;
		}
	}

	fin.close();
}

void ParseParams(Params& params, char* argv[], int argc)
{
	std::string filename = "statix.conf";
	if (argc > 1) {
		filename = argv[1];
	}
	ParseConfig(params, filename);
}

void SignalHandler(int signum)
{
	if (GlobalServer) {
		GlobalServer->Stop();
	}
}

void HandleSignals()
{
	signal(SIGINT, SignalHandler);
	signal(SIGTERM, SignalHandler);
#if defined(SIGQUIT)
	signal(SIGQUIT, signalHandler);
#endif
}

int main(int argc, char* argv[])
{
	std::setlocale(LC_ALL, "ru_RU.UTF-8");

	Params params{
		80,
		256,
		"src"
	};
	ParseParams(params, argv, argc);
	HandleSignals();

	try {
		GlobalServer.reset(new serv::Server(params.Port, params.ThreadsLimit, params.Root));
		std::cout << "Server started at " << params.Port << std::endl;
		std::cout << "Threads limit is " << params.ThreadsLimit << std::endl;
		std::cout << "Root folder is " << fs::absolute(params.Root) << std::endl;
		GlobalServer->Run();
		std::cout << "Server stopped" << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Unknown exception: " << e.what() << "\n";
	}
	return 0;
}