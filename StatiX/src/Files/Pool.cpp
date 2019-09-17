#include "Pool.h"

files::FilesPool::FilesPool(size_t threadNum, Cache const& cache, CallbackFunc callback)
	: cache_{ cache }
	, statix::Pool<Task, Callback>(threadNum, callback)
{}

void files::FilesPool::Tick_(TaskElem task, CallbackFunc callback)
{
	auto file = cache_.GetFile(task.second);
	callback(task.first, file);
}
