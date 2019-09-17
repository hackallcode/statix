#ifndef __NET_PARSER_INCLUDED__
#define __NET_PARSER_INCLUDED__

#include "General.h"

namespace net
{
	class Parser
	{
	public:
		Parser();

		Header Parse(std::string header) const;
	private:

	};
}

#endif // !__NET_PARSER_INCLUDED__
