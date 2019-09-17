#include "Cache.h"
#include <iostream>
#include <fstream>
#include <utility>

namespace fs = std::filesystem;

files::Cache::Cache()
	: files_()
{}

bool files::Cache::CacheFolder(fs::path const& root, std::vector<std::string> const& indexes)
{
	if (!fs::is_directory(root)) {
		return false;
	}

	for (auto& p : fs::recursive_directory_iterator(root)) {
		RememberFile_(root, p, indexes);
	}
	return true;
}

files::Cache::ConstPtr files::Cache::GetFile(std::string path) const
{
	std::string key = GetKey_(fs::path(path).lexically_normal());

	auto const& res = files_.find(key);
	if (res == files_.end()) {
		return nullptr;
	}
	return res->second;
}

bool files::Cache::RememberFile_(fs::path const& root, fs::path const& file, std::vector<std::string> const& indexes)
{	
	// Key for map
	std::string key = GetKey_(file.lexically_relative(root));
	
	// Already in map
	if (files_.find(key) != files_.end()) {
		return true;
	}

	// File not found
	if (!fs::exists(file)) {
		return false;
	}

	// Read data of file
	std::ifstream fin(file, std::ios::binary);
	if (!fin.is_open()) {
		return false;
	}
	Ptr data(new std::vector<uint8_t>(std::istreambuf_iterator<char>(fin), {}));
	fin.close();
	
	// Add file as folder if index of folder
	std::string filename = file.filename().string();
	for (auto& index : indexes) {
		if (index == filename) {
			std::string folderKey = GetKey_(fs::path(key).remove_filename());
			files_.emplace(folderKey, data);
			break;
		}
	}

	// Add file in map
	files_.emplace(key, data);
	return true;
}

std::string files::Cache::GetKey_(std::filesystem::path const& path)
{
	std::string key = path.string();
#ifdef _WIN32
	std::replace(key.begin(), key.end(), '\\', '/');
#endif
	return key;
}
