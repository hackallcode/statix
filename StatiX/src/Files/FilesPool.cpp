#include "FilesPool.h"

files::FilesPool::FilesPool(Cache const& cache, size_t threadNum, CallbackFunc callback)
	: cache_{ cache }
	, statix::Pool<Task, Callback>(threadNum, callback)
{}

void files::FilesPool::Tick_(TaskElem task, CallbackFunc callback)
{
	auto file = cache_.GetFile(task.second);
	callback(task.first, file);
}
