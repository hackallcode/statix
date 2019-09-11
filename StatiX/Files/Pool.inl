template<class C>
files::Pool<C>::Pool(size_t threadNum, Cache const& cache, CallbackFunc callback)
	: cache_(cache)
{
	threads_.reserve(threadNum);

	for (size_t i = 0; i < threadNum; ++i) {
		threads_.emplace_back(std::bind(&Pool<C>::Tick_, this, callback));
	}
}

template<class C>
files::Pool<C>::~Pool()
{
	Stop();
	Join();
	cv_.notify_all();
	for (auto& thread : threads_) {
		thread.join();
	}
}

template<class C>
void files::Pool<C>::Push(Task const& task)
{
	if (stop_) {
		return;
	}
	queue_.Push(task);
	cv_.notify_one();
}

template<class C>
void files::Pool<C>::Push(Task&& task)
{
	if (stop_) {
		return;
	}
	queue_.Push(task);
	cv_.notify_one();
}

template<class C>
void files::Pool<C>::Stop()
{
	stop_ = true;
}

template<class C>
void files::Pool<C>::Join()
{
	while (!queue_.IsEmpty()) {}
}

template<class C>
void files::Pool<C>::Tick_(CallbackFunc callback)
{
	while (true) {
		Task task;
		{
			std::unique_lock<std::mutex> lock(m_);
			cv_.wait(lock, [this]() -> bool {
				return !queue_.IsEmpty() || stop_;
				});

			if (stop_ && queue_.IsEmpty()) {
				return;
			}

			task = std::move(queue_.Pop());
		}
		auto file = cache_.GetFile(task.second);
		callback(task.first, file);
	}
}
