#include <iostream>
#include <clocale>
#include <csignal>
#include "Common/Config.h"
#include "Server/Server.h"

std::unique_ptr<serv::Server> GlobalServer;

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
	signal(SIGQUIT, SignalHandler);
#endif
}

int main(int argc, char* argv[])
{
	std::setlocale(LC_ALL, "ru_RU.UTF-8");

	Config config(80, 256, "html");
	ParseParams(config, argv, argc);
	HandleSignals();

	try {
		std::cout << "Threads limit is " << config.ThreadsLimit << std::endl;
		std::cout << "Root folder is " << std::filesystem::absolute(config.Root) << std::endl;
		GlobalServer.reset(new serv::Server(config.Port, config.ThreadsLimit, config.Root));
		std::cout << "Server started at " << config.Port << std::endl;
		GlobalServer->Run();
		std::cout << "Server stopped" << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Unknown exception: " << e.what() << "\n";
	}
	return 0;
}