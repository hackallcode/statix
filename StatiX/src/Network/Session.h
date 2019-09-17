#ifndef __NET_SESSION_INCLUDED__
#define __NET_SESSION_INCLUDED__

#include "General.h"
#include "Parser.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace net
{
	class Session
	{
	public:
		Session(boost::asio::io_service& io_service, net::Parser const& parser);

		tcp::socket& Socket();

		void Start();
		void Write(std::shared_ptr<std::vector<uint8_t>> data);

	private:
		tcp::socket socket_;
		std::string input_;
		net::Parser parser_;
		char data_[RECEIVER_BUFFER_LENGTH];

		void OnRead_(const boost::system::error_code& error, size_t bytes_transferred);
		void OnWrite_(const boost::system::error_code& error);
	};
}

#endif // !__NET_SESSION_INCLUDED__