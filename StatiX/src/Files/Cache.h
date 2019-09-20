#ifndef __FILES_CACHE_INCLUDED__
#define __FILES_CACHE_INCLUDED__

#include "General.h"
#include <string>
#include <unordered_map>
#include <filesystem>

namespace files
{
	class Cache
	{
	public:
		using Ptr = std::shared_ptr<CacheFile>;
		using ConstPtr = Ptr const;

		Cache(std::filesystem::path const& folder,
			std::vector<std::string> const& indexes = std::vector<std::string>{ "index.html" });
		
		bool CacheFolder(std::filesystem::path const& folder,
			std::vector<std::string> const& indexes = std::vector<std::string>{ "index.html" });

		ConstPtr GetFile(std::string path) const;
	private:
		std::unordered_map<std::string, Ptr> files_;

		bool RememberFile_(std::filesystem::path const& folder, std::filesystem::path const& file,
			std::vector<std::string> const& indexes = std::vector<std::string>{});

		static std::string GetKey_(std::filesystem::path const& path);
	};
}

#endif // !__FILES_CACHE_INCLUDED__
