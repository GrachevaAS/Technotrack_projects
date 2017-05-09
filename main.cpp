#include <iostream>
#include "Vector.h"
#include "Stack.h"
#include "Array.h"

template <class T>
void copyTest(Vector<T> vectorValue) {
	std::cout << "this function copies vector by value\n";
}

int main() {
	Vector<int> myVector;
	for (int i = 0; i < 7; i++)
		myVector.push_back(i*i);

	Vector<int> myVector2 = myVector;     // copying constructor + assignment operator
	Vector<int> myVector3;
	myVector3 = myVector;

	for (unsigned int i = 0; i < myVector.size(); i++) {       // index operator
		std::cout << myVector[i] << "\t" << myVector2[i] << "\t" << myVector3[i] << "\n";
	}

	//myVector.resize(20, 0);               // resize function
	//Vector<int> myVector2(6);
	//myVector2 = myVector;
	//
	//copyTest(myVector);                // copying vector by value
	//
	//for (int i = 0; i < myVector.size(); i++) {       // index operator
	//	std::cout << myVector[i] << " ";
	//}
	//for (int i = 0; i < 6; i++) {
	//	myVector.pop_back();
	//}
	return 0;
}