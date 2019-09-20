template<class T, class C>
statix::Pool<T, C>::Pool(size_t threadsCount, CallbackFunc callback)
{
	threads_.reserve(threadsCount);
	for (size_t i = 0; i < threadsCount; ++i) {
		threads_.emplace_back([this, callback]() -> void {
			while (true) {
				TaskElem task;
				{
					std::unique_lock<std::mutex> lock(m_);
					cv_.wait(lock, [this]() -> bool { return !queue_.IsEmpty() || stop_; });

					if (stop_ && queue_.IsEmpty()) {
						return;
					}

					if (!queue_.IsEmpty()) {
						task = queue_.Pop();
					}
				}
				Tick_(task, callback);
			}
			});
	}
}

template<class T, class C>
statix::Pool<T, C>::~Pool()
{
	Stop();
	Join();
	cv_.notify_all();
	for (auto& thread : threads_) {
		thread.join();
	}
}

template<class T, class C>
void statix::Pool<T, C>::Push(TaskElem const& task)
{
	if (stop_) {
		return;
	}
	queue_.Push(task);
	cv_.notify_one();
}

template<class T, class C>
void statix::Pool<T, C>::Push(TaskElem&& task)
{
	if (stop_) {
		return;
	}
	queue_.Push(task);
	cv_.notify_one();
}

template<class T, class C>
void statix::Pool<T, C>::Stop()
{
	stop_ = true;
}

template<class T, class C>
void statix::Pool<T, C>::Join()
{
	while (!queue_.IsEmpty()) {
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

template<class T, class C>
void statix::Pool<T, C>::Tick_(TaskElem task, CallbackFunc callback)
{}
