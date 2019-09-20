#ifndef __COMMON_POOL_INCLUDED__
#define __COMMON_POOL_INCLUDED__

#include "Queue.h"
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace statix
{
	template<class T, class C>
	class Pool
	{
	public:
		using TaskElem = T;
		using CallbackFunc = std::function<C>;

		Pool(size_t threadsCount, CallbackFunc callback);
		Pool(Pool const&) = delete;
		Pool(Pool&&) = delete;

		virtual ~Pool();

		void Push(TaskElem const& task);
		void Push(TaskElem&& task);
		void Stop();
		void Join();

		Pool& operator=(Pool const&) = delete;
		Pool& operator=(Pool&&) = delete;

	protected:
		virtual void Tick_(TaskElem task, CallbackFunc callback);

	private:
		std::atomic_bool stop_;
		std::mutex m_;
		std::condition_variable cv_;

		Queue<TaskElem> queue_;
		std::vector<std::thread> threads_;
	};
}

#include "Pool.inl"

#endif // !__COMMON_POOL_INCLUDED__
