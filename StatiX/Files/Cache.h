#ifndef __FILESYSTEM_CACHE_INCLUDED__
#define __FILESYSTEM_CACHE_INCLUDED__

#include <string>
#include <unordered_map>
#include <filesystem>

namespace files 
{
	class Cache
	{
	public:
		using Ptr = std::shared_ptr<std::vector<uint8_t>>;
		using ConstPtr = Ptr const;

		Cache();
		
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

#endif // !__FILESYSTEM_CACHE_INCLUDED__
