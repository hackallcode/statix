#ifndef __FILESYSTEM_POOL_INCLUDED__
#define __FILESYSTEM_POOL_INCLUDED__

#include "../Common/Queue.h"
#include "General.h"
#include "Cache.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace files 
{
	template<class C>
	class Pool
	{
	public:
		using CallbackFunc = std::function<C>;

		Pool(size_t threadNum, Cache const& cache, CallbackFunc callback);
		~Pool();

		void Push(Task const& task);
		void Push(Task&& task);
		void Stop();
		void Join();

	protected:
		void Tick_(CallbackFunc callback);

	private:
		std::atomic_bool stop_;
		std::mutex m_;
		std::condition_variable cv_;

		Queue<Task> queue_;
		Cache cache_;
		std::vector<std::thread> threads_;
	};
}

#include "Pool.inl"

#endif // !__FILESYSTEM_POOL_INCLUDED__
