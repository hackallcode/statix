#ifndef __FILES_QUEUE_INCLUDED__
#define __FILES_QUEUE_INCLUDED__

#include "General.h"
#include <string>
#include <unordered_map>

namespace files {
	class Queue
	{
	public:
		Queue();
		~Queue();

		bool IsEmpty();
		void Push(Task const& value);
		void Push(Task&& value);
		Task Pop();
	private:
		class Item
		{
		public:
			Task data;
			Item* next;

			Item();
			Item(Task const& data);
			Item(Task&& data);
		};

		Item* first_;
		Item* last_;
	};
}

#endif // !__FILES_QUEUE_INCLUDED__
