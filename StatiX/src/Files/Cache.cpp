#include "Cache.h"
#include <iostream>
#include <fstream>
#include <utility>

namespace fs = std::filesystem;

files::Cache::Cache(std::filesystem::path const& folder, std::vector<std::string> const& indexes)
	: files_()
{
	if (!CacheFolder(folder, indexes)) {
		std::cerr << "Impossible to found folder " << folder << std::endl;
	}
}

bool files::Cache::CacheFolder(fs::path const& root, std::vector<std::string> const& indexes)
{
	if (!fs::is_directory(root)) {
		return false;
	}

	for (auto& p : fs::recursive_directory_iterator(root)) {
		if (!fs::is_directory(p)) {
			RememberFile_(root, p, indexes);
		}
	}
	return true;
}

files::Cache::ConstPtr files::Cache::GetFile(std::string path) const
{
	std::string key = GetKey_(fs::path(path).lexically_normal());

	auto const& res = files_.find(key);
	if (res == files_.end()) {
		return ConstPtr();
	}
	return res->second;
}

bool files::Cache::RememberFile_(fs::path const& root, fs::path const& file, std::vector<std::string> const& indexes)
{	
	 // Key for map
	 std::string key = '/' + GetKey_(file.lexically_relative(root));

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

	 // Read file in array
	 fin.seekg(0, std::ios::end);
	 size_t fileSize = fin.tellg();
	 std::vector<char> data;
	 data.resize(fileSize);
	 fin.seekg(0, std::ios::beg);
	 fin.read(&data[0], fileSize);
	
	 // Save & Close
	 Ptr ptr(new CacheFile(std::move(data), file.extension().string()));
	 fin.close();
	
	 // Add file as folder if index of folder
	 std::string filename = file.filename().string();
	 for (auto& index : indexes) {
	 	if (index == filename) {
	 		std::string folderKey = GetKey_(fs::path(key).remove_filename());
	 		files_.emplace(folderKey, ptr);
	 		break;
	 	}
	 }

	 // Add file in map
	 files_.emplace(key, ptr);
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
