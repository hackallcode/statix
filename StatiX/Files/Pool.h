#ifndef __FILESYSTEM_POOL_INCLUDED__
#define __FILESYSTEM_POOL_INCLUDED__

#include "Queue.h"
#include "Cache.h"
#include <thread>

namespace files {
	class Pool
	{
	public:
		Pool(Cache const& cache, size_t threadNum);
		void Push(Task const& task);
		void Push(Task&& task);
		void Run();
		void Join();
	private:
		bool hasRunned_;
		Queue input_, output_;
		std::thread thread_;

		std::vector<Queue> queues_;
		std::vector<std::thread> threads_;

		void Run_();
		static void Loop_(Queue& input, Queue& output, Cache const& cache);
	};
}

#endif // !__FILESYSTEM_POOL_INCLUDED__
