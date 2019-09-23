#include "Config.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool IsSpaceChar(char ch)
{
	return ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t';
}

void ParseConfig(Config& params, std::vector<fs::path> const& filenames)
{
	fs::path filename;
	for (auto& f : filenames) {
		// File found
		if (fs::exists(f)) {
			filename = f;
			break;
		}
	}

	// File not found
	if (filename.empty()) {
		std::cout << "Config file not found!" << std::endl;
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

		// Get key
		std::string key;
		for (; i < line.size() && !IsSpaceChar(line[i]); ++i) {
			key += line[i];
		}

		// Skip spaces
		for (; i < line.size() && IsSpaceChar(line[i]); ++i) {}

		// Get value
		std::string value;
		for (; i < line.size() && !IsSpaceChar(line[i]); ++i) {
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

void ParseParams(Config& params, char* argv[], int argc)
{
	std::vector<fs::path> filenames;
	if (argc > 1) {
		filenames.push_back(argv[1]);
	}
	filenames.push_back("/etc/httpd.conf");
	filenames.push_back("statix.conf");
	ParseConfig(params, filenames);
}
