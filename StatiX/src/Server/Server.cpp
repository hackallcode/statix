#include "Server.h"

serv::Server::Server(boost::asio::io_service& io_service, short port)
	: io_service_(io_service)
	, acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	, parser_()
{
	StartAccept();
}

void serv::Server::StartAccept()
{
	net::Session* newSession = new net::Session(io_service_, parser_);
	acceptor_.async_accept(
		newSession->Socket(),
		boost::bind(&Server::HandleAccept, this, newSession, boost::asio::placeholders::error)
	);
}

void serv::Server::HandleAccept(net::Session* newSession, const boost::system::error_code& error)
{
	if (!error) {
		newSession->Start();
	}
	else {
		delete newSession;
	}

	StartAccept();
}
