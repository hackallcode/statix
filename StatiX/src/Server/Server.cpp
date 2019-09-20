#include "Server.h"
#include <signal.h>

serv::Server::Server(short port, size_t threadsCount, std::filesystem::path const& folder)
	: io_service_()
	, acceptor_(io_service_, tcp::endpoint(tcp::v4(), port))
	, parser_()
	, cache_(folder)
	, filesPool_(cache_, threadsCount, Answer)
	, netPool_(parser_, threadsCount, std::bind(&GetFile, std::ref(filesPool_), std::placeholders::_1, std::placeholders::_2))
{
	// Wait for signals indicating time to shut down.
	boost::asio::signal_set signals(io_service_);
	signals.add(SIGINT);
	signals.add(SIGTERM);
	#if defined(SIGQUIT)
		signals.add(SIGQUIT);
	#endif
	signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service_));
	// Start listening for clients
	StartAccept_();
	io_service_.run();
}

void serv::Server::Run()
{
}

void serv::Server::StartAccept_()
{
	net::Client client = net::Client(new net::Session(io_service_));
	acceptor_.async_accept(
		client->Socket(),
		boost::bind(&Server::HandleAccept_, this, client, boost::asio::placeholders::error)
	);
}

void serv::Server::HandleAccept_(net::Client client, const boost::system::error_code& error)
{
	if (!error) {
		netPool_.Push(client);
	}

	StartAccept_();
}

void serv::GetFile(files::FilesPool& filesPool, net::Client client, net::Header header)
{
	client->SetMethod(header.Method);
	filesPool.Push(files::Task(client, header.Path));
}

void serv::Answer(net::Client client, std::shared_ptr<files::CacheFile> file)
{
	client->SendFile(file);
}