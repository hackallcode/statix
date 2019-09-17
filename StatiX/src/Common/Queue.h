#ifndef __COMMON_QUEUE_INCLUDED__
#define __COMMON_QUEUE_INCLUDED__

namespace statix
{
	template<typename T>
	class Queue
	{
	public:
		Queue();
		Queue(Queue const&) = delete;
		Queue(Queue&&) = delete;

		~Queue();

		bool IsEmpty();
		void Push(T const& value);
		void Push(T&& value);
		T Pop();

		Queue& operator=(Queue const&) = delete;
		Queue& operator=(Queue&&) = delete;

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

#endif // !__COMMON_QUEUE_INCLUDED__
