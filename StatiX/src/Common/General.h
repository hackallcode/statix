#ifndef __COMMON_GENERAL_INCLUDED__
#define __COMMON_GENERAL_INCLUDED__

#include <memory>
#include <boost/asio.hpp>

namespace net
{
	class Session;
	using Client = std::shared_ptr<Session>;
}

#endif // !__COMMON_GENERAL_INCLUDED__
