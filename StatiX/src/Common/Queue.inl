template<class T>
statix::Queue<T>::Item::Item()
	: data()
	, next(nullptr)
{}

template<class T>
statix::Queue<T>::Item::Item(T const& _data)
	: data(_data)
	, next(nullptr)
{}

template<class T>
statix::Queue<T>::Item::Item(T&& _data)
	: data(_data)
	, next(nullptr)
{}

template<class T>
statix::Queue<T>::Queue()
	: first_(new Item())
{
	last_ = first_;
}

template<class T>
statix::Queue<T>::~Queue()
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
bool statix::Queue<T>::IsEmpty()
{
	return first_ == last_;
}

template<class T>
void statix::Queue<T>::Push(T const& value)
{
	m_.lock();
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
	m_.unlock();
}

template<class T>
void statix::Queue<T>::Push(T&& value)
{
	m_.lock();
	last_->data = value;
	Item* item = new Item();
	last_->next = item;
	last_ = item;
	m_.unlock();
}

template<class T>
T statix::Queue<T>::Pop()
{
	m_.lock();
	if (first_ == last_) {
		return T();
	}

	Item* tmp = first_;
	first_ = first_->next;
	m_.unlock();
	
	T data = std::move(tmp->data);
	delete tmp;
	return data;
}
