#include <iostream>
#include "Files/Cache.h"
#include "Files/Pool.h"
#include <mutex>
#include <time.h>

std::mutex output_mutex;

void print(files::Socket sock, std::shared_ptr<std::vector<uint8_t>> data) {
	if (!data) {
		output_mutex.lock();
		std::cout << "Not Found!" << std::endl;
		output_mutex.unlock();
		return;
	}
	//output_mutex.lock();
	//for (auto& ch : *data) {
	//	std::cout << ch;
	//}
	//std::cout << std::endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	//output_mutex.unlock();
}

int main()
{
	size_t const count{ 1000000 };

	files::Cache cache;
	if (!cache.CacheFolder("./src")) {
		std::cout << "Impossible to cache folder!" << std::endl;
		return 1;
	}

	files::Pool pool(256, cache, print);
	for (size_t i = 0; i < count; ++i) {
		pool.Push(files::Task(i, "html/main.html"));
	}

	clock_t start{ clock() };
	pool.Start();
	pool.Join();
	clock_t end{ clock() };
	std::cout << "PPS = " << count / ((double)(end - start) / CLOCKS_PER_SEC) << std::endl;

	return 0;
}