#include "Queue.h"

files::Queue::Item::Item()
	: data()
	, next(nullptr)
{}

files::Queue::Item::Item(Task const& _data)
	: data(_data)
	, next(nullptr)
{}

files::Queue::Item::Item(Task&& _data)
	: data(_data)
	, next(nullptr)
{}

files::Queue::Queue()
	: first_(new Item())
{
	last_ = first_;
}

files::Queue::~Queue()
{
	Item* curr = first_;
	first_ = nullptr;
	last_ = nullptr;
	while (curr != nullptr) {
		Item* next = curr->next;
		delete curr;
		curr = next;
	}
}

bool files::Queue::IsEmpty()
{
	return first_ == last_;
}

void files::Queue::Push(Task const& value)
{
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
}

void files::Queue::Push(Task&& value)
{
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
}

files::Task files::Queue::Pop()
{
	if (first_ == last_) {
		return Task();
	}

	Task data = std::move(first_->data);
	Item* tmp = first_;
	first_ = first_->next;
	delete tmp;
	return data;
}
