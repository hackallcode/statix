template<class T>
files::Queue<T>::Item::Item()
	: data()
	, next(nullptr)
{}

template<class T>
files::Queue<T>::Item::Item(T const& _data)
	: data(_data)
	, next(nullptr)
{}

template<class T>
files::Queue<T>::Item::Item(T&& _data)
	: data(_data)
	, next(nullptr)
{}

template<class T>
files::Queue<T>::Queue()
	: first_(new Item())
{
	last_ = first_;
}

template<class T>
files::Queue<T>::~Queue()
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

template<class T>
bool files::Queue<T>::IsEmpty()
{
	return first_ == last_;
}

template<class T>
void files::Queue<T>::Push(T const& value)
{
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
}

template<class T>
void files::Queue<T>::Push(T&& value)
{
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
}

template<class T>
T files::Queue<T>::Pop()
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
