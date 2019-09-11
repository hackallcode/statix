#ifndef __FILES_GLOBAL_INCLUDED__
#define __FILES_GLOBAL_INCLUDED__

#include <utility>
#include <memory>
#include <vector>
#include <string>

namespace files 
{
	using Socket = int;
	using Task = std::pair<Socket, std::string>;
	using Callback = void(Socket, std::shared_ptr<std::vector<uint8_t>>);
}

#endif // !__FILES_GLOBAL_INCLUDED__
