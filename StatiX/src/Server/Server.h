#ifndef __SERVER_INCLUDED__
#define __SERVER_INCLUDED__

#include "../Network/Session.h"
#include "../Network/Parser.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace serv
{
	class Server
	{
	public:
		Server(boost::asio::io_service& io_service, short port);

	private:
		boost::asio::io_service& io_service_;
		tcp::acceptor acceptor_;
		net::Parser parser_;

		void StartAccept();
		void HandleAccept(net::Session* new_session, const boost::system::error_code& error);
	};
}

#endif // !__SERVER_INCLUDED__
