#include "Server.h"
#include <signal.h>

serv::Server::Server(short port, size_t threadsCount, std::filesystem::path const& folder)
	: started_(false)
	, io_service_()
	, acceptor_(io_service_, tcp::endpoint(tcp::v4(), port))
	, parser_()
	, cache_(folder)
	, filesPool_(cache_, threadsCount, Answer)
	, netPool_(parser_, threadsCount, std::bind(&GetFile, std::ref(filesPool_), std::placeholders::_1, std::placeholders::_2))
{}

void serv::Server::Run()
{
	if (started_) {
		return;
	}

	started_ = true;
	while (started_) {
		net::Client client(std::make_shared<net::Session>(net::Session(io_service_)));
		boost::system::error_code error;
		acceptor_.accept(client->Socket(), error);
		if (!error) {
			netPool_.Push(client);
		}
	}
}

void serv::Server::Stop()
{
	started_ = false;
	acceptor_.close();
}

void serv::GetFile(files::FilesPool& filesPool, net::Client client, net::Header header)
{
	client->SetMethod(header.Method);
	filesPool.Push(files::Task{ client, header.Path });
}

void serv::Answer(net::Client client, std::shared_ptr<files::CacheFile> file)
{
	client->SendFile(file);
}