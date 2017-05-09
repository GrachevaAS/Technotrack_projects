#ifndef H_STACK
#define H_STACK

#define DEBUG

#include <assert.h>
#include <stdlib.h>
#include <new>

template <class T>
class Stack {
public:
	Stack();
	~Stack();
	using value_type = T;
	using size_type = size_t;
	using reference = T&;
	using const_reference = const T&;

	void push(value_type value);
	void pop();
	const_reference top() const;
	bool empty() const;
	size_type size() const;
private:
	static const size_type initSize = 4;
	size_type bufferSize;
	value_type* buffer;
	size_type elementsCount;
	void resizeBuffer(size_type new_size);
	void is_OK() const;
	void DUMP() const;
};

template <class T>
Stack<T>::Stack() : bufferSize(initSize), elementsCount(0) {
	try {
		buffer = new value_type[bufferSize];
		#ifdef DEBUG
	        std::cout << "INIT STACK";
	        DUMP();
        #endif
	}
	catch (std::bad_alloc &e) {
		std::cout << "allocation failed\n";
	}
}

template <class T>
Stack<T>::~Stack() {
	is_OK();
	delete[] buffer;
    #ifdef DEBUG
	std::cout << "STACK IS DELETED";
    #endif
}

//
template <class T>
void Stack<T>::push(value_type value) {
    #ifdef DEBUG
	    std::cout << "call push\n";
    #endif
	is_OK();
	try {
		if (elementsCount == bufferSize) {
			resizeBuffer(2 * bufferSize);
		}
		buffer[elementsCount] = value;
		elementsCount++;
	}
	catch (std::bad_alloc) {
		std::cout << "not pushed\n";
		throw;
		return;
	}
}

template <class T>
void Stack<T>::pop() {
    #ifdef DEBUG
	    std::cout << "call pop\n";
    #endif
	is_OK();
	try {
		if (elementsCount == 0)
			throw - 1;
		elementsCount--;
	}
	catch (int) {
		std::cout << "the stack is empty\n";
	}
}

template <class T>
typename Stack<T>::const_reference Stack<T>::top() const {
	is_OK();
	try {
		if (elementsCount == 0)
			throw - 1;
		return buffer[elementsCount - 1];
	}
	catch (int) {
		std::cout << "the stack is empty\n";
	}
}

template <class T>
bool Stack<T>::empty() const {
	is_OK();
	return elementsCount == 0;
}

template <class T>
typename Stack<T>::size_type Stack<T>::size() const {
	is_OK();
	return elementsCount;
}

template <class T>
void Stack<T>::resizeBuffer(typename Stack<T>::size_type new_size) {
    #ifdef DEBUG
	    std::cout << "reallocation...\n";
    #endif
	is_OK();
	if (new_size <= bufferSize)
		return;
	try {
		value_type* bufferCopy = new value_type[new_size];
		for (size_type i = 0; i < bufferSize; i++) {
			bufferCopy[i] = buffer[i];
		}
		delete[] buffer;
		buffer = bufferCopy;
		bufferSize = new_size;
	}
	catch (std::bad_alloc) {
		std::cout << "allocation failed\n";
		throw;
		return;
	}
	DUMP();
}

template <class T>
void Stack<T>::is_OK() const {
	assert(elementsCount >= 0);
	assert(bufferSize > 0);
	assert(elementsCount <= bufferSize);
	assert(buffer != NULL);
}

template <class T>
void Stack<T>::DUMP() const {
	is_OK();
	std::cout << "\n-----printing the stack:-----\n";
	std::cout << "this: " << this << "\n";
	std::cout << "bufferSize = " << bufferSize << "\n";
	std::cout << size() << " elements, " << empty() << " empty\n";
	if (!empty()) {
		for (size_type i = 0; i < elementsCount; i++) {
			std::cout << buffer[i] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "-----stack is printed-----\n\n";
}

#endif