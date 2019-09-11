template<class T, class C>
statix::Pool<T, C>::Pool(size_t threadNum, CallbackFunc callback)
{
	threads_.reserve(threadNum);
	for (size_t i = 0; i < threadNum; ++i) {
		threads_.emplace_back([this, callback]() -> void {
			while (true) {
				TaskElem task;
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
	//cv_.notify_one();
}

template<class T, class C>
void statix::Pool<T, C>::Push(TaskElem&& task)
{
	if (stop_) {
		return;
	}
	queue_.Push(task);
	//cv_.notify_one();
}

template<class T, class C>
void statix::Pool<T, C>::Start()
{
	cv_.notify_all();
}

template<class T, class C>
void statix::Pool<T, C>::Stop()
{
	stop_ = true;
}

template<class T, class C>
void statix::Pool<T, C>::Join()
{
	while (!queue_.IsEmpty()) {}
}

template<class T, class C>
void statix::Pool<T, C>::Tick_(TaskElem task, CallbackFunc callback)
{}
