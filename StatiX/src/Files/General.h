#ifndef __FILES_GENERAL_INCLUDED__
#define __FILES_GENERAL_INCLUDED__

#include "../Common/General.h"
#include <utility>
#include <memory>
#include <vector>
#include <string>

namespace files 
{
	class CacheFile {
	public:
		CacheFile(std::vector<char>&& _data, std::string const& ext)
			: data(_data)
			, type(GetType(ext))
			, length(std::to_string(data.size()))
		{}

		std::vector<char> data;
		std::string type;
		std::string length;
	private:
		std::string GetType(std::string const& ext) {
			if (ext == ".html") {
				return "text/html";
			}
			else if (ext == ".css") {
				return "text/css";
			}
			else if (ext == ".js") {
				return "text/javascript";
			}
			else if (ext == ".jpg" || ext == ".jpeg") {
				return "image/jpeg";
			}
			else if (ext == ".png") {
				return "image/png";
			}
			else if (ext == ".gif") {
				return "image/gif";
			}
			else if (ext == ".swf") {
				return "application/x-shockwave-flash";
			}
			else {
				return "text/plain";
			}
		}
	};

	struct Task {
		net::Client client;
		std::string path;

		operator bool() const {
			return client.operator bool();
		}
	};
	using Callback = void(net::Client, std::shared_ptr<CacheFile>);
}

#endif // !__FILES_GENERAL_INCLUDED__
