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
		std::string Method;
		std::string Path;
	};

	std::string const HeaderEnd = "\r\n";
	std::string const StaticResponceHeader = "Server: StatiX\r\nConnection: Closed\r\n";

	static size_t const RECEIVER_BUFFER_LENGTH = 16U;

	using Task = Client;
	using Callback = void(Client, Header);
}

#endif // !__NET_GENERAL_INCLUDED__
