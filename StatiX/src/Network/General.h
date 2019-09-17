#ifndef __NET_GENERAL_INCLUDED__
#define __NET_GENERAL_INCLUDED__

#include "../Common/General.h"
#include <utility>
#include <memory>
#include <vector>
#include <string>


namespace net
{
	struct Header {

	};
	
	static size_t const RECEIVER_BUFFER_LENGTH = 256U;

	using Task = std::pair<Client, std::string>;
	using Callback = void(Client, Header);
}

#endif // !__NET_GENERAL_INCLUDED__
