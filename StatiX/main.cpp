#include <iostream>
#include "Files/Cache.h"
#include "Files/Pool.h"
#include "Queue.h"
#include <mutex>

std::mutex output_mutex;

void print(files::Socket sock, std::shared_ptr<std::vector<uint8_t>> data) {
	if (!data) {
		output_mutex.lock();
		std::cout << "Not Found!" << std::endl;
		output_mutex.unlock();
		return;
	}
	output_mutex.lock();
	std::cout << sock << std::endl;
	for (auto& ch : *data) {
		std::cout << ch;
	}
	std::cout << std::endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	output_mutex.unlock();
}

int main()
{
	files::Cache cache;
	if (!cache.CacheFolder("./src")) {
		std::cout << "Impossible to cache folder!" << std::endl;
		return 1;
	}

	files::Pool pool(cache, 20, print);
	for (size_t i = 0; i < 100; ++i) {
		pool.Push(files::Task(i, "html/main.html"));
	}
	pool.Run();
	pool.Join();
;	return 0;
}