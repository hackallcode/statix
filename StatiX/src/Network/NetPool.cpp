#include "NetPool.h"

net::NetPool::NetPool(Parser const& parser, size_t threadNum, CallbackFunc callback)
	: parser_{ parser }
	, statix::Pool<Task, Callback>(threadNum, callback)
{}

void net::NetPool::Tick_(TaskElem client, CallbackFunc callback)
{
	try {
		auto header{ parser_.Parse(client->Read()) };
		if (header.Method != "GET" && header.Method != "HEAD") {
			client->Send405();
			return;
		}
		if (header.Path.back() == '/') {
			client->SetIdDir(true);
		}
		client->SetMethod(header.Method);
		callback(client, header);
	}
	catch (std::exception&) {}
}
