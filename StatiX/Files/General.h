#ifndef __FILESYSTEM_GLOBAL_INCLUDED__
#define __FILESYSTEM_GLOBAL_INCLUDED__

#include <utility>
#include <functional>

namespace files 
{
	using Socket = int;
	using Task = std::pair<Socket, std::string>;
	using Callback = void(Socket, std::shared_ptr<std::vector<uint8_t>>);
}

#endif // !__FILESYSTEM_GLOBAL_INCLUDED__
