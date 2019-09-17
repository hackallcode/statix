#ifndef __FILES_GENERAL_INCLUDED__
#define __FILES_GENERAL_INCLUDED__

#include "../Common/General.h"
#include <utility>
#include <memory>
#include <vector>
#include <string>

namespace files 
{
	using Task = std::pair<net::Client, std::string>;
	using Callback = void(net::Client, std::shared_ptr<std::vector<uint8_t>>);
}

#endif // !__FILES_GENERAL_INCLUDED__
