#ifndef H_VECTOR
#define H_VECTOR

#define DEBUG
#include <assert.h>
#include <iostream>

template <class T>
class Vector {
public:
	using value_type = T;
	using size_type = size_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = T*;
	using const_iterator = const T*;

	Vector();
	explicit Vector(size_type size);
	//Vector(const Vector<T>& another) = delete;
	Vector(const Vector<T>& another);
	~Vector();
	//Vector<T>& operator=(const Vector<T>& another) = delete;
	Vector<T>& operator=(const Vector<T>& another);
	reference operator[](size_type pos);
	reference at(size_type pos);
	reference front();
	reference back();
	bool empty() const;
	size_type size() const;
	size_type capacity() const;
	bool reserve(size_type new_cap);
	bool resize(size_type count, const value_type& value);
	void clear();
	void push_back(const T& value);
	void pop_back();
	iterator begin();
	iterator end();
	iterator cbegin() const;
	iterator cend() const;

private:
	static const size_type initSize = 4;
	value_type* buffer;
	size_type bufferSize;
	size_type elementsCount;
	void is_OK() const;
	void DUMP();
};

template <class T>
Vector<T>::Vector() : bufferSize(initSize), elementsCount(0) {
	std::cout << "call constructor\n";
	try {
		buffer = new value_type[bufferSize];
        #ifdef DEBUG
		    std::cout << "INIT VECTOR\n";
		    DUMP();
        #endif
	}
	catch (std::bad_alloc &e) {
		std::cout << "allocation failed\n";
		throw e;
	}
}

template <class T>
Vector<T>::Vector(size_type size) : bufferSize(size), elementsCount(0) {
	std::cout << "call constructor with size\n";
	if (size < initSize)
		bufferSize = initSize;
	try {
		buffer = new value_type[bufferSize];
        #ifdef DEBUG
		    std::cout << "INIT VECTOR\n";
		    DUMP();
        #endif
	}
	catch (std::bad_alloc &e) {
		std::cout << "allocation failed\n";
		throw e;
	}
}

template <class T>
Vector<T>::Vector(const Vector<T>& another) : bufferSize(4), elementsCount(0) {
	std::cout << "call COPYING constructor\n";
	bufferSize = another.capacity();
	elementsCount = another.size();
	try {
		buffer = new value_type[bufferSize];
		size_type i = 0;
		for (iterator it = another.cbegin(); it != another.cend() && i < elementsCount; it++) {
			buffer[i] = (*it);
			i++;
		}
        #ifdef DEBUG
		    std::cout << "INIT VECTOR\n";
		    DUMP();
        #endif
	}
	catch (std::bad_alloc &e) {
		std::cout << "allocation failed\n";
		throw e;
	}
}

template <class T>
Vector<T>::~Vector() {
	std::cout << "call destructor, this: " << this << "\n";
	is_OK();
	DUMP();
	std::cout << "deletion address: " << buffer << "\n";
	delete[] buffer;
	#ifdef DEBUG
	std::cout << "VECTOR DELETED\n";
	#endif
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& another) {
	std::cout << "assignment operator\n";
	is_OK();
	if (bufferSize < another.size()) {
		try {
			if (!reserve(another.size()))
				throw (bufferSize);
			bufferSize = another.capacity();
			elementsCount = another.size();
		}
		catch (size_type &e) {
			std::cout << "error: not enough memory. Only the first " << e << " items will be copied\n";
			elementsCount = bufferSize;
		}
	}
	else {
		elementsCount = another.size();
	}
	size_type i = 0;
	for (iterator it = another.cbegin(); it != another.cend() && i < elementsCount; it++) {
		buffer[i] = (*it);
		i++;
	}
	// DUMP();
	return *this;
}
template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
	is_OK();
	return buffer[pos];
}

template <class T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
	is_OK();
	try {
		if (pos >= elementsCount)
			throw (std::out_of_range("error: position is out of range\n"));
		return buffer[pos];
		}
		catch (std::out_of_range &e) {
			std::cout << e.what();
			throw e;
		}
}

template <class T>
typename Vector<T>::reference Vector<T>::front() {
	std::cout << "call front\n";
	is_OK();
	try {
		if (elementsCount == 0)
			throw (std::length_error("error: vector is empty\n"));
		return buffer[0];
	}
	catch (std::length_error &e) {
		std::cout << e.what();
		throw e;
	}
}

template <class T>
typename Vector<T>::reference Vector<T>::back() {
	std::cout << "call back\n";
	is_OK();
	try {
		if (elementsCount == 0)
			throw (std::length_error("error: vector is empty\n"));
		return buffer[elementsCount - 1];
	}
	catch (std::length_error &e) {
		std::cout << e.what();
		throw e;
	}
}

template <class T>
bool Vector<T>::empty() const {
	is_OK();
	return (elementsCount == 0);
}

template <class T>
typename Vector<T>::size_type Vector<T>::size() const {
	is_OK();
	return (elementsCount);
}

template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const {
	is_OK();
	return (bufferSize);
}

template <class T>
bool Vector<T>::reserve(size_type new_cap) {
	std::cout << "call reserve!\n";
	is_OK();
	if (new_cap <= bufferSize)
		return true;
	try {
		value_type* bufferCopy = new value_type[new_cap];
		for (size_type i = 0; i < bufferSize; i++) {
			bufferCopy[i] = buffer[i];
		}
		delete[] buffer;
		buffer = bufferCopy;
		bufferSize = new_cap;
		DUMP();
		return true;
	}
	catch (std::bad_alloc) {
		std::cout << "error: allocation failed\n"; 
		return false;
	}
}

template <class T>
bool Vector<T>::resize(size_type count, const value_type& value) {
	std::cout << "call resize!\n";
	is_OK();
	if (count <= bufferSize) {
		elementsCount = count;
		return true;
	}
	try {
		size_type countToReserve = count < bufferSize * 2 ? bufferSize * 2 : count;
		if (!reserve(countToReserve))
			throw (-1);
		for (size_type i = elementsCount; i < count; i++) {
			buffer[i] = value;
		}
		elementsCount = count;
		DUMP();
		return true;
	}
	catch (int) {
		std::cout << "error: resize is impossible\n";
		return false;
	}
}

template <class T>
void Vector<T>::clear() {
	std::cout << "call clear\n";
	is_OK();
	elementsCount = 0;
	//DUMP();
}

template <class T>
void Vector<T>::push_back(const T& value) {
	std::cout << "push back ";
	is_OK();
	if (elementsCount + 1 > bufferSize) {
		try {
			if(!reserve(bufferSize * 2))
				throw(-1);
		} catch(int) {
			std::cout << "error: reached memory limit\n";
		}
	}
	buffer[elementsCount] = value;
	elementsCount++;
	std::cout << value << "\n";
}

template <class T>
void Vector<T>::pop_back() {
	std::cout << "call pop back\n";
	is_OK();
	try {
		if (elementsCount == 0)
			throw(-1);
		elementsCount--;
	}
	catch (int) {
		std::cout << "error: vector is empty\n";
	}
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
	is_OK();
	return buffer;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() {
	is_OK();
	return buffer + elementsCount;
}

template <class T>
typename Vector<T>::iterator Vector<T>::cbegin() const {
	is_OK();
	return buffer;
}

template <class T>
typename Vector<T>::iterator Vector<T>::cend() const {
	is_OK();
	return buffer + elementsCount;
}

template <class T>
void Vector<T>::is_OK() const {
	assert(bufferSize > 0);
	assert(elementsCount <= bufferSize);
	assert(elementsCount >= 0);
	assert(buffer != NULL);
}

template <class T>
void Vector<T>::DUMP() {
	is_OK();
	std::cout << "\n-----printing the vector:-----\n";
	std::cout << "this: " << this << "\n";
	std::cout << "capacity = " << capacity() << "\n";
	std::cout << size() << " elements, " << empty() << " empty\n";
	if (!empty()) {
		std::cout << "Front: " << front() << "\nBack: " << back() << "\n";
		for (iterator it = begin(); it != end(); it++) {
			std::cout << (*it) << " ";
		}
		std::cout << "\nrepeat:\n";
		for (size_type i = 0; i < elementsCount; i++) {
			std::cout << at(i) << " ";
		}
	std::cout << "\n";
	}
	std::cout << "-----vector is printed-----\n\n";
}

#endif

