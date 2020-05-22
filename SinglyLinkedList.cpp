/* this implementation of Singly Linked List
	is zero-indexed
*/

#include "SinglyLinkedList.h"


// A constructor to initialize data members
template<class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	leftEnd = rightEnd = nullptr;
	length = 0;
}

// A destructor to free up memory
template<class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	// iterate and delete every node
	SingleNode<T> *it = leftEnd, *temp;
	while (it != nullptr) {
		temp = it;
		it = it->next;
		delete temp;
	}

	leftEnd = rightEnd = nullptr;
	length = 0;
}

template<class T>
int SinglyLinkedList<T>::Length() const
{
	return length;
}

// A method that takes a starting point and a key to check if the key exists
template<class T>
bool SinglyLinkedList<T>::Find(int k, T & x) const
{
	if (k < 0 || k >= length)
		return false;

	// declare an iterator ptr
	SingleNode<T> *it = leftEnd;

	// iterate until the position given
	for (int i = 0; i < k; i++) {
		it = it->next;
	}

	// save the value and declare success
	x = it->data;
	return true;
}

// A method that searches for a specific key and return its position
template<class T>
int SinglyLinkedList<T>::Search(const T & x) const
{
	// declare iterator ptr
	SingleNode<T> *it = leftEnd;

	// iterate until you find it
	for (int i = 0; i < length; i++) {
		if (it->data == x)
			return i;
		it = it->next;
	}

	// otherwise
	return -1;
}

// A method that deletes an element with a given key
template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::Delete(int k, T & x)
{
	// iterator ptr
	SingleNode<T> *it = leftEnd, *temp;

	// check index and that's not empty
	if (k < 0 || k >= length || isEmpty())
		return *this;


	// in case its the first element
	else if (k == 0) {
		temp = leftEnd;
		leftEnd = leftEnd->next;
	}

	// otherwise iterate untill the prev to the position given
	else {
		for (int i = 0; i < k - 1; i++) {
			it = it->next;
		}

		// in case it's the last element 
		if (k == length - 1) {
			temp = rightEnd;
			rightEnd = it;
			rightEnd->next = nullptr;
		}

		// in case it's in between
		else {
			temp = it->next;
			it->next = temp->next;
		}
	}

	// delete the element and save its value
	x = temp->data;
	delete temp;
	length--;
	return *this;
}

template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::Insert(int k, const T & x)
{
	// A method that check the index is valid
	checkIndex(k);

	// create a new node 
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = x;

	// insert in case it's empty
	if (isEmpty()) {
		leftEnd = rightEnd = newNode;
	}

	// insert in case at the beginning
	else if (k == 0) {
		newNode->next = leftEnd;
		leftEnd = newNode;
	}

	else {
		// iterate untill the prev of the position given
		SingleNode<T> *it = leftEnd;
		for (int i = 0; i < k - 1; i++)
			it = it->next;

		// in case at the end
		if (k == length) {
			rightEnd->next = newNode;
			rightEnd = newNode;
		}

		// in case in between
		else {
			SingleNode<T> *temp = it->next;
			it->next = newNode;
			newNode->next = temp;
		}
	}

	length++;
	return *this;
}

// A method that prints the list to the given stream
template<class T>
void SinglyLinkedList<T>::Output(std::ostream & out) const
{
	// iterate and print every element
	SingleNode<T> *it = leftEnd;
	while (it != nullptr) {
		out << it->data;
		if (it->next != nullptr)
			out << ", ";
		it = it->next;
	}
}

// overload the operator << to work with this object
template<class T>
std::ostream & operator<<(std::ostream & out, const SinglyLinkedList<T>& x)
{
	x.Output(out);
	return out;
}

// A method to get the length Iteratively
template<class T>
int SinglyLinkedList<T>::getLengthIterative()
{
	int l = 0;
	SingleNode<T> *it = leftEnd;
	while (it != nullptr) {
		l++;
		it = it->next;
	}
	return l;
}

// A method to get the length Recusively
template<class T>
int SinglyLinkedList<T>::getLengthRecursive()
{
	static SingleNode<T> *it = leftEnd;
	if (it == nullptr)
		return 0;
	it = it->next;
	return 1 + getLengthRecursive();
}

// A method that swaps two elements without swapping the data inside
template<class T>
void SinglyLinkedList<T>::swap(int firstIndex, int secondIndex)
{
	// check indexes
	checkIndex(firstIndex);
	checkIndex(secondIndex);

	// get the previous node of the first
	SingleNode<T> *firstNodePrev = leftEnd;
	for (int i = 0; i < firstIndex - 1; i++)
		firstNodePrev = firstNodePrev->next;

	// get the previous node of the second
	SingleNode<T> *secondNodePrev = leftEnd;
	for (int i = 0; i < secondIndex - 1; i++)
		secondNodePrev = secondNodePrev->next;

	// get the nodes themselves
	SingleNode<T> *firstNode = firstNodePrev->next;
	SingleNode<T> *secondNode = secondNodePrev->next;

	// swap the previous nexts
	firstNodePrev->next = secondNode;
	secondNodePrev->next = firstNode;

	// swap the nodes nexts
	SingleNode<T> *temp = firstNode->next;
	firstNode->next = secondNode->next;
	secondNode->next = temp;
}

// A method that reverses the linked list
template<class T>
void SinglyLinkedList<T>::reverse()
{
	// initialize pointers to work with
	SingleNode<T> *originalStart = leftEnd;
	SingleNode<T> *fakeStart = nullptr;

	// keep inserting the nodes in the fake list in reversing order
	while (originalStart != nullptr) {
		SingleNode<T> *temp = originalStart->next;
		originalStart->next = fakeStart;
		fakeStart = originalStart;
		originalStart = temp;
	}

	// swap the left and right ends
	originalStart = leftEnd;
	leftEnd = rightEnd;
	rightEnd = originalStart;
}

// A method that merges 2 sorted lists into another sorted one
template<class T>
SinglyLinkedList<T>* SinglyLinkedList<T>::merge(SinglyLinkedList *list)
{
	// initialize some variables
	SingleNode<T> *it1 = leftEnd, *it2 = list->leftEnd;
	SinglyLinkedList<T> *newList = new SinglyLinkedList<T>();
	int i = 0;

	// use merge technique and insert to the new list
	while (it1 != nullptr && it2 != nullptr) {
		if (it1->data < it2->data) {
			newList->Insert(i++, it1->data);
			it1 = it1->next;
		}
		else {
			newList->Insert(i++, it2->data);
			it2 = it2->next;
		}
	}

	// insert the rest 
	while (it1 != nullptr) {
		newList->Insert(i++, it1->data);
		it1 = it1->next;
	}
	while (it2 != nullptr) {
		newList->Insert(i++, it2->data);
		it2 = it2->next;
	}

	return newList;
}

// A method that gets the maximum value in the list
template<class T>
T SinglyLinkedList<T>::getMax()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	T max = leftEnd->data;
	SingleNode<T> *it = leftEnd->next;
	while (it != nullptr) {
		if (it->data > max) {
			max = it->data;
		}
		it = it->next;
	}
	return max;
}

// A method that gets the minimum value in the list
template<class T>
T SinglyLinkedList<T>::getMin()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	T min = leftEnd->data;
	SingleNode<T> *it = leftEnd->next;
	while (it != nullptr) {
		if (it->data < min) {
			min = it->data;
		}
		it = it->next;
	}
	return min;
}

// A method that gets the sum of all elements in the list
template<class T>
T SinglyLinkedList<T>::getSum()
{
	if (isEmpty())
		return 0;

	T sum = leftEnd->data;
	SingleNode<T> *it = leftEnd->next;
	while (it != nullptr) {
		sum += it->data;
		it = it->next;
	}
	return sum;
}

// A method that gets the average value in the list using the sum
template<class T>
T SinglyLinkedList<T>::getAver()
{
	return getSum() / length;
}

// A method that gets the second maximum value in the list
template<class T>
T SinglyLinkedList<T>::getMaxSecond()
{
	// check validation
	if (length < 2)
		throw std::exception("Not Enough Elements!");

	// initialize the max and second max
	T max, secondMax;
	if (leftEnd->data > leftEnd->next->data) {
		max = leftEnd->data;
		secondMax = leftEnd->next->data;
	}
	else {
		max = leftEnd->next->data;
		secondMax = leftEnd->data;
	}

	// iterate from the third position
	SingleNode<T> *it = leftEnd->next->next;
	while (it != nullptr) {
		// in case it's bigger than max
		if (it->data > max) {
			secondMax = max;
			max = it->data;
		}

		// in case it's between max and second
		else if (it->data > secondMax) {
			secondMax = it->data;
		}

		it = it->next;
	}
	return secondMax;
}

// A method that gets the second minimum value in the list
template<class T>
T SinglyLinkedList<T>::getMinSecond()
{
	// check validation
	if (length < 2)
		throw std::exception("Not Enough Elements!");

	// initialize the min and second min
	T min, secondMin;
	if (leftEnd->data < leftEnd->next->data) {
		min = leftEnd->data;
		secondMin = leftEnd->next->data;
	}
	else {
		min = leftEnd->next->data;
		secondMin = leftEnd->data;
	}

	// iterate from the third position
	SingleNode<T> *it = leftEnd->next->next;
	while (it != nullptr) {
		// in case it's smaller than min
		if (it->data < min) {
			secondMin = min;
			min = it->data;
		}

		// in case it's between min and second
		else if (it->data < secondMin) {
			secondMin = it->data;
		}

		it = it->next;
	}
	return secondMin;
}

// A method that splits a list into two halves
template<class T>
SinglyLinkedList<T>* SinglyLinkedList<T>::split()
{
	// create a new list for the right half
	SinglyLinkedList<T> *rightHalf = new SinglyLinkedList<T>();

	// update the lengths
	rightHalf->length = length - length / 2;
	length = length / 2;

	// iterate untill the breaking point
	SingleNode<T> *it = leftEnd;
	for (int i = 0; i < length - 1; i++) {
		it = it->next;
	}

	// Split the list 
	rightHalf->leftEnd = it->next;
	rightHalf->rightEnd = rightEnd;
	rightEnd = it;
	rightEnd->next = nullptr;

	// return the new list
	return rightHalf;
}

// A method that Inserts elements and maintains sorted order list (Similar to Insert)
template<class T>
void SinglyLinkedList<T>::insert(T element)
{
	// create the new node
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = element;

	// in case it's empty
	if (isEmpty()) {
		leftEnd = rightEnd = newNode;
	}
	
	// in case insertion should be at the beginning
	else if (leftEnd->data > element) {
		newNode->next = leftEnd;
		leftEnd = newNode;
	}

	// otherwise iterate until the proper position
	else {
		SingleNode<T> *it = leftEnd;
		while (it->next != nullptr && it->next->data < element)
			it = it->next;

		// in case insertion should be at the end
		if (it->next == nullptr) {
			rightEnd->next = newNode;
			rightEnd = newNode;
		}

		// in case insertion shoule be in between
		else {
			SingleNode<T> *temp = it->next;
			it->next = newNode;
			newNode->next = temp;
		}
	}
	length++;
}

// A method to check if a list is sorted
template<class T>
bool SinglyLinkedList<T>::isSorted()
{
	if (isEmpty())
		return true;

	SingleNode<T> *it = leftEnd;
	while (it->next != nullptr) {
		if (it->data > it->next->data)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only even values
template<class T>
bool SinglyLinkedList<T>::isEven()
{
	SingleNode<T> *it = leftEnd;
	while (it != nullptr) {
		if (it->data % 2 != 0)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only odd values
template<class T>
bool SinglyLinkedList<T>::isOdd()
{
	SingleNode<T> *it = leftEnd;
	while (it != nullptr) {
		if (it->data % 2 != 1)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list is empty
template<class T> 
bool SinglyLinkedList<T>::isEmpty() {
	return (length == 0);
}

// A method that checks valid index
template<class T>
void SinglyLinkedList<T>::checkIndex(int index) {
	if (index < 0 || index > length)
		throw std::out_of_range("Index Out of Bounds");
}
