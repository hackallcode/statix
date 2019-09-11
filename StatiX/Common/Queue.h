#ifndef __FILES_QUEUE_INCLUDED__
#define __FILES_QUEUE_INCLUDED__

#include <string>
#include <unordered_map>

namespace files
{
	template<typename T>
	class Queue
	{
	public:
		Queue();
		~Queue();

		bool IsEmpty();
		void Push(T const& value);
		void Push(T&& value);
		T Pop();
	private:
		class Item
		{
		public:
			T data;
			Item* next;

			Item();
			Item(T const& data);
			Item(T&& data);
		};

		Item* first_;
		Item* last_;
	};
}

#include "Queue.inl"

#endif // !__FILES_QUEUE_INCLUDED__
