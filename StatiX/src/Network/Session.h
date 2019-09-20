#ifndef __NET_SESSION_INCLUDED__
#define __NET_SESSION_INCLUDED__

#include "General.h"
#include "Parser.h"
#include "../Files/FilesPool.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <chrono>

using boost::asio::ip::tcp;

namespace net
{
	class Session
	{
	public:
		Session(boost::asio::io_service& io_service);

		tcp::socket& Socket();

		std::string Read();
		void Send405();
		void SendFile(std::shared_ptr<files::CacheFile> file);
		void SetIdDir(bool isDir);
		void SetMethod(std::string const& method);

	private:
		tcp::socket socket_;
		std::string method_;
		std::string date_;
		bool isDir_;
	};

	std::string GetHeader403_(std::string const& date);
	std::string GetHeader404_(std::string const& date);
	std::string GetHeader405_(std::string const& date);

	std::string GetHeader200_(std::string const& date, std::string const& type, std::string const& length);
}

#endif // !__NET_SESSION_INCLUDED__