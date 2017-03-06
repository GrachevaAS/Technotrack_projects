#ifndef H_STACK
#define H_STACK

template <class T>
class Stack {
public:
	Stack();
	~Stack();
	using value_type = T;
	using size_type = size_t;
	//using reference = T&;
	//using const_reference = const T&;

	void push(value_type value);
	void pop();
	value_type top() const;
	bool empty() const;
	size_type size() const;
private:
	static const int initialSize = 4;
	size_type bufferSize;
	value_type* buffer;
	size_type currentSize;
	value_type* resizeBuffer(value_type* buffer);
	void is_OK();
}; #pragma once

#endif