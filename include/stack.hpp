#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <mutex>

template <typename T>
class stack
{
private:
	void swap(stack<T> &);

public:
	stack();
	stack(stack<T> const &) /* strong */;
	stack<T>& operator = (stack<T> const &);
	size_t count() const;
	void push(T const &) /* strong */;
	void pop() /* strong */;
	T top() /* strong */;
	bool empty() const;

private:
	std::mutex mutex_;
	T* array_;
	size_t array_size_;
	size_t count_;
};

template <typename T>
stack<T>::stack() : count_(0), array_size_(0), array_(nullptr)
{}

template <typename T>
size_t stack<T>::count() const
{
	return count_;
}

template <typename T>
stack<T>::stack(stack<T> const& copy)
{
	T* temp = new T[copy.array_size_];
	array_size_ = copy.array_size_;
	count_ = copy.count_;
	array_ = temp;
	try
	{
		std::copy(copy.array_, copy.array_ + count_, array_);
	}
	catch (...)
	{
		std::cerr << "Error! Try again!" << std::endl;
		delete[] array_;
	}
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T> const& other)
{
	mutex_.lock();
	if (this != &other)
	{
		stack<T> temp(other);
		swap(temp);
	}

	return *this;
	
	mutex_.unlock();
}

template <typename T>
void stack<T>::swap(stack<T>& other)
{
	mutex_.lock();
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
	mutex_.unlock();
}

template <typename T>
void stack<T>::push(T const& value)
{
	mutex_.lock();
	if (array_size_ == count_)
	{
		size_t size = array_size_;
		if (size == 0)
			size = 1;
		else
			size = array_size_ * 2;

		T* temp = new T[size];
		std::copy(array_, array_ + count_, temp);

		array_size_ = size;
		delete[] array_;
		array_ = temp;
	}

	array_[count_] = value;
	++count_;
	mutex_.unlock();
}

template <typename T>
void stack<T>::pop()
{
	mutex_.lock();
	if (count_ == 0)
	{
		throw "Stack is empty! Try again!\n";
	}
	else
	{
		--count_;
	}
	mutex_.unlock();
}

template <typename T>
T stack<T>::top()
{
	mutex_.lock();
	if (count_ == 0)
	{
		throw "Stack is empty!";
	}
	else
	{
		return array_[count_ - 1];
	}
	mutex_.unlock();
}

template <typename T>
bool stack<T>::empty() const
{
	mutex_.lock();
	return (count_ == 0);
	mutex_.unlock();
	
}
