#ifndef H_STACK
#define H_STACK

template <class T>
class Stack {
public:
	Stack();
	~Stack();
	using value_type = T;
	using size_type = size_t;
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
};

template <class T>
Stack<T>::Stack() : bufferSize(initialSize), currentSize(0) {
	buffer = new value_type[bufferSize];
}
template <class T>
Stack<T>::~Stack() {
	is_OK();
	delete[] buffer;
}

template <class T>
void Stack<T>::push(value_type value) {
	is_OK();
	if (currentSize == bufferSize) {
		buffer = reallocate(buffer);
	}
	buffer[currentSize] = value;
	currentSize++;
}

template <class T>
void Stack<T>::pop() {
	is_OK();
	currentSize--;
	is_OK();
}

template <class T>
typename Stack<T>::value_type Stack<T>::top() const {
	is_OK();
	assert(currentSize > 0);
	return buffer[currentSize];
}

template <class T>
bool Stack<T>::empty() const {
	is_OK();
	return currentSize == 0;
}

template <class T>
typename Stack<T>::size_type Stack<T>::size() const {
	is_OK();
	return currentSize;
}

template <class T>
void Stack<T>::is_OK() {
	assert(currentSize >= 0);
	assert(bufferSize >= 0);
	assert(currentSize <= bufferSize);
}

template <class T>
typename Stack<T>::value_type* Stack<T>::resizeBuffer(typename Stack<T>::value_type* buffer) {
	value_type* bufferCopy = new value_type[bufferSize * 2];
	int temp = 0;
	for (int i = 0; i < bufferSize; i++) {
		bufferCopy[i] = buffer[i];
	}
	delete[] buffer;
	bufferSize *= 2;
	return bufferCopy;
}

#endif