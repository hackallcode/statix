#include <iostream>
#include <clocale>
#include "Server/Server.h"

struct Params{
	short Port;
	size_t ThreadsLimit;
	std::string Root;
};

Params ParseParams(char* argv[], int argc)
{
	Params res{
		8000,
		256,
		"."
	};
	if (argc > 1) {
		res.Port = std::stoi(argv[1]);
	}
	if (argc > 2) {
		res.ThreadsLimit = std::stoi(argv[2]);
	}
	if (argc > 3) {
		res.Root = argv[3];
	}
	return res;
}

int main(int argc, char* argv[])
{
	Params params = ParseParams(argv, argc);
	std::setlocale(LC_ALL, "ru_RU.UTF-8");
	try	{
		std::cout << "Server started at " << params.Port << std::endl;
		std::cout << "Threads limit is " << params.ThreadsLimit << std::endl;
		std::cout << "Root folder is " << std::filesystem::absolute(params.Root) << std::endl;
		serv::Server server(params.Port, params.ThreadsLimit, params.Root);
		server.Run();
	}
	catch (std::exception& e) {
		std::cerr << "Unknown exception: " << e.what() << "\n";
	}
	return 0;
}