#include "Pool.h"

serv::ServerPool::ServerPool(size_t threadNum, Session const& session, CallbackFunc callback)
	: session_{ session }
	, statix::Pool<Task, Callback>(threadNum, callback)
{}

void serv::ServerPool::Tick_(TaskElem task, CallbackFunc callback)
{
	//auto header = session_.Parse(task.second);
	//callback(task.first, header);
}
