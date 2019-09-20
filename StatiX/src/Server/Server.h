#ifndef __SERVER_INCLUDED__
#define __SERVER_INCLUDED__

#include "../Network/Session.h"
#include "../Network/Parser.h"
#include "../Network/NetPool.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace serv
{
	class Server
	{
	public:
		Server(short port, size_t threadsCount, std::filesystem::path const& folder);
		void Run();
		void Stop();

	private:
		bool started_;
		boost::asio::io_service io_service_;
		tcp::acceptor acceptor_;
		net::Parser parser_;
		net::NetPool netPool_;
		files::Cache cache_;
		files::FilesPool filesPool_;
	};

	void GetFile(files::FilesPool& filesPool, net::Client client, net::Header header);
	void Answer(net::Client client, std::shared_ptr<files::CacheFile> file);

}

#endif // !__SERVER_INCLUDED__
