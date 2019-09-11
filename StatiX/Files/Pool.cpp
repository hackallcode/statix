#include "Pool.h"

files::Pool::Pool(Cache const& cache, size_t threadNum, Callback callback)
	: hasRunned_(false)
{
	queues_.reserve(threadNum);
	threads_.reserve(threadNum);

	for (size_t i = 0; i < threadNum; ++i) {
		queues_.emplace_back();
		threads_.emplace_back(Loop_, std::ref(queues_.back()), std::ref(cache), callback);
	}
}

void files::Pool::Push(Task const& task)
{
	input_.Push(task);
}

void files::Pool::Push(Task&& task)
{
	input_.Push(task);
}

void files::Pool::Run()
{
	if (hasRunned_) {
		return;
	}

	thread_ = std::thread(std::bind(&Pool::Run_, this));
	hasRunned_ = true;
}

void files::Pool::Join()
{
	if (hasRunned_ && thread_.joinable()) {
		thread_.join();
		hasRunned_ = false;
	}
}

void files::Pool::Run_()
{
	size_t i = 0U;
	while (true) {
		while (input_.IsEmpty()) {}
		while (!queues_[i].IsEmpty()) {
			++i;
			i %= queues_.size();
		}
		queues_[i].Push(input_.Pop());
	}
}

void files::Pool::Loop_(Queue& input, Queue& output, Cache const& cache)
{
	while (true) {
		while (queue.IsEmpty()) {}
		Task task = queue.Pop();
		auto file = cache.GetFile(task.second);
		callback(task.first, file);
	}
}
