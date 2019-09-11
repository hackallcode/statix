#include "Pool.h"

files::Pool::Pool(size_t threadNum, Cache const& cache, CallbackFunc callback)
	: cache_{ cache }
	, statix::Pool<Task, Callback>(threadNum, callback)
{}

void files::Pool::Tick_(TaskElem task, CallbackFunc callback)
{
	auto file = cache_.GetFile(task.second);
	callback(task.first, file);
}
