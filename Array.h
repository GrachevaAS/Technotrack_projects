#ifndef H_ARRAY
#define H_ARRAY

// #define DEBUG

#include <assert.h>
#include <iostream>

class MyError : std::exception {
public:
	MyError() {
		line = "";
	}
	MyError(const char* newline) {
		line = newline;
	}
	const char* what() const {
		return line;
	}
private:
	const char* line;
};

template <class T, std::size_t Size>
class Array {
public:
	using value_type = T;
	using size_type = size_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = T*;
	using const_iterator = const T*;

	Array();
	Array(Array<T, Size>& another);
	Array<T, Size>& operator=(Array<T, Size>& another);
	~Array();
	void swap(Array<T, Size>& another) noexcept;
	reference operator[](size_type pos);
	void fill(const_reference value);
	reference at(size_type pos);
	reference front();
	reference back();
	bool empty() const;
	size_type size() const;
	iterator begin();
	iterator end();
	iterator cbegin() const;
	iterator cend() const;

private:
	value_type buffer[Size];
	void is_OK() const;
	void DUMP();
};

template <class T, std::size_t Size>
Array<T,Size>::Array() {
	#ifdef DEBUG
	std::cout << "INIT ARRAY\n";
	#endif
}

template <class T, std::size_t Size>
Array<T, Size>::~Array() {
	is_OK();
#ifdef DEBUG
	std::cout << "call destructor, this: " << this << "\n";
	std::cout << "ARRAY DELETED\n";
#endif
}

template <class T, std::size_t Size>
Array<T, Size>::Array(Array<T, Size>& another) {
	is_OK();
	int i = 0;
	for (iterator it = another.begin(); it != another.end(); it++) {
		buffer[i] = (*it);
		i++;
	}
	#ifdef DEBUG
	std::cout << "INIT ARRAY\n";
	#endif
}

template <class T, std::size_t Size>
void Array<T, Size>::swap(Array<T, Size>& another) noexcept {
	for (size_t it = 0; it < Size; it++) {
		std::swap(at(it), another.at(it));
	}
}

template <class T, std::size_t Size>
Array<T, Size>& Array<T, Size>::operator=(Array<T, Size>& another) {
	is_OK();
	Array<T, Size> temp(another);
	this->swap(temp);
	return *this;
}

template <class T, std::size_t Size>
typename Array<T, Size>::reference Array<T, Size>::operator[](size_type pos) {
	is_OK();
	return buffer[pos];
}

template <class T, std::size_t Size>
typename Array<T, Size>::reference Array<T, Size>::at(size_type pos) {
	is_OK();
	if (pos >= Size) {
		throw (MyError("error: position is out of range\n"));
		DUMP();
	}
	return buffer[pos];
}

template <class T, std::size_t Size>
void Array<T, Size>::fill(const_reference value) {
	is_OK();
	for (int i = 0; i < Size; i++) {
		buffer[i] = value;
	}
}

template <class T, std::size_t Size>
typename Array<T, Size>::reference Array<T, Size>::front() {
	is_OK();
	if (Size == 0) {
		throw (MyError("error: array is empty(front)\n"));
		DUMP();
	}
	return *(this->begin());
}

template <class T, std::size_t Size>
typename Array<T, Size>::reference Array<T, Size>::back() {
	is_OK();
	if (Size == 0) {
		throw (MyError("error: array is empty(back)\n"));
		DUMP();
	}
	return *(this->end() - 1);
}

template <class T, std::size_t Size>
bool Array<T, Size>::empty() const {
	is_OK();
	return (Size == 0);
}

template <class T, std::size_t Size>
typename Array<T, Size>::size_type Array<T, Size>::size() const {
	is_OK();
	return (Size);
}

template <class T, std::size_t Size>
typename Array<T, Size>::iterator Array<T, Size>::begin() {
	is_OK();
	return &buffer[0];
}

template <class T, std::size_t Size>
typename Array<T, Size>::iterator Array<T, Size>::end() {
	is_OK();
	return &buffer[Size - 1] + 1;
}

template <class T, std::size_t Size>
typename Array<T, Size>::iterator Array<T, Size>::cbegin() const {
	return &buffer[0];
}

template <class T, std::size_t Size>
typename Array<T, Size>::iterator Array<T, Size>::cend() const {
	is_OK();
	return &buffer[Size - 1] + 1;
}

template <class T, std::size_t Size>
void Array<T, Size>::is_OK() const {
	assert(Size >= 0);
	assert(&buffer[0] != NULL);
}

template <class T, std::size_t Size>
void Array<T, Size>::DUMP() {
	is_OK();
	std::cerr << "\n-----printing the array:-----\n";
	std::cerr << "this: " << this << "\n";
	std::cerr << size() << " elements, " << empty() << " empty\n";
	if (!empty()) {
		std::cerr << "Front: " << front() << "\nBack: " << back() << "\n";
		for (iterator it = begin(); it != end(); it++) {
			std::cerr << (*it) << " ";
		}
	}
	std::cerr << "-----array is printed-----\n\n";
}

#endif


