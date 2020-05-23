/* this implementation of Doubly Linked List
	is zero-indexed
*/

#include "DoublyLinkedList.h"


// A constructor to initialize data members
template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	leftEnd = rightEnd = nullptr;
	length = 0;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	// iterate and delete every node
	DoubleNode<T> *it = leftEnd, *temp;
	while (it != nullptr) {
		temp = it;
		it = it->next;
		delete temp;
	}

	leftEnd = rightEnd = nullptr;
	length = 0;
}

template<class T>
int DoublyLinkedList<T>::Length() const
{
	return length;
}

// A method that takes a starting point and a key to check if the key exists
template<class T>
bool DoublyLinkedList<T>::Find(int k, T & x) const
{
	if (k < 0 || k >= length)
		return false;

	// declare an iterator ptr
	DoubleNode<T> *it = leftEnd;

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
int DoublyLinkedList<T>::Search(const T & x) const
{
	// declare iterator ptr
	DoubleNode<T> *it = leftEnd;

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
DoublyLinkedList<T>& DoublyLinkedList<T>::Delete(int k, T & x)
{
	// iterator ptr
	DoubleNode<T> *it = leftEnd, *temp;

	// check index and that's not empty
	if (k < 0 || k >= length || isEmpty())
		return *this;


	// in case its the first element
	else if (k == 0) {
		temp = leftEnd;
		leftEnd = leftEnd->next;
		leftEnd->prev = nullptr;
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
			temp->next->prev = it;
		}
	}

	// delete the element and save its value
	x = temp->data;
	delete temp;
	length--;
	return *this;
}

// A methdod that inserts an element into agiven position
template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::Insert(int k, const T & x)
{
	// A method that check the index is valid
	checkIndex(k);

	// create a new node 
	DoubleNode<T> *newNode = new DoubleNode<T>();
	newNode->data = x;

	// insert in case it's empty
	if (isEmpty()) {
		leftEnd = rightEnd = newNode;
	}

	// insert in case at the beginning
	else if (k == 0) {
		newNode->next = leftEnd;
		leftEnd->prev = newNode;
		leftEnd = newNode;
	}

	// in case at the end
	else if (k == length) {
		rightEnd->next = newNode;
		newNode->prev = rightEnd;
		rightEnd = newNode;
	}

	// otherwise, in case in between
	else {
		// iterate untill the position given
		DoubleNode<T> *it = leftEnd;
		for (int i = 0; i < k - 1; i++)
			it = it->next;

		DoubleNode<T> *temp = it->next;
		it->next = newNode;
		newNode->prev = it;
		newNode->next = temp;
		temp->prev = newNode;
	}

	length++;
	return *this;
}

// A method that prints the list to the given stream
template<class T>
void DoublyLinkedList<T>::Output(std::ostream & out) const
{
	// iterate and print every element
	DoubleNode<T> *it = leftEnd;
	while (it != nullptr) {
		out << it->data;
		if (it->next != nullptr)
			out << ", ";
		it = it->next;
	}
}

// overload the operator << to work with this object
template<class T>
std::ostream & operator<<(std::ostream & out, const DoublyLinkedList<T>& x)
{
	x.Output(out);
	return out;
}

// A method to get the length Iteratively
template<class T>
int DoublyLinkedList<T>::getLengthIterative()
{
	int l = 0;
	DoubleNode<T> *it = leftEnd;
	while (it != nullptr) {
		l++;
		it = it->next;
	}
	return l;
}

// A method to get the length Recusively
template<class T>
int DoublyLinkedList<T>::getLengthRecursive()
{
	static DoubleNode<T> *it = leftEnd;
	if (it == nullptr)
		return 0;
	it = it->next;
	return 1 + getLengthRecursive();
}

// A method that swaps two elements without swapping the data inside
template<class T>
void DoublyLinkedList<T>::swap(int firstIndex, int secondIndex)
{
	// check indexes
	if (firstIndex < 0 || firstIndex >= length
		|| secondIndex < 0 || secondIndex >= length)
		throw std::out_of_range("Index Out of Bounds");

	// declare some pointers to work with
	DoubleNode<T> *firstNodePrev = nullptr, *firstNode = leftEnd,
		*secondNodePrev = nullptr, *secondNode = leftEnd;

	// get the first node and its previous
	if (firstIndex != 0) {
		firstNodePrev = leftEnd;
		for (int i = 0; i < firstIndex - 1; i++)
			firstNodePrev = firstNodePrev->next;
		firstNode = firstNodePrev->next;
	}

	// get the second node and its previous
	if (secondIndex != 0) {
		secondNodePrev = leftEnd;
		for (int i = 0; i < secondIndex - 1; i++)
			secondNodePrev = secondNodePrev->next;
		secondNode = secondNodePrev->next;
	}

	// swap the previous nexts and prevs
	if (firstNodePrev != nullptr)
		firstNodePrev->next = secondNode;
	secondNode->prev = firstNodePrev;
	if (secondNodePrev != nullptr)
		secondNodePrev->next = firstNode;
	firstNode->prev = secondNodePrev;

	// swap the nodes nexts and prevs
	DoubleNode<T> *temp = firstNode->next;
	firstNode->next = secondNode->next;
	secondNode->next->prev = firstNode;
	secondNode->next = temp;
	temp->prev = secondNode;

	// update list pointers
	if (firstIndex == 0)
		leftEnd = secondNode;
	if (secondIndex == 0)
		leftEnd = firstNode;
	if (firstIndex == length - 1)
		rightEnd = secondNode;
	if (secondIndex == length - 1)
		rightEnd = firstNode;
}

// A method that reverses the linked list
template<class T>
void DoublyLinkedList<T>::reverse()
{
	// iterate and swap every next with prev
	DoubleNode<T> *it = leftEnd, *temp;
	while (it != nullptr) {
		temp = it->next;
		it->next = it->prev;
		it->prev = temp;
		it = temp;
	}

	// swap leftEnd with righEnd
	temp = leftEnd;
	leftEnd = rightEnd;
	rightEnd = temp;
}

// A method that merges 2 sorted lists into another sorted one
template<class T>
DoublyLinkedList<T>* DoublyLinkedList<T>::merge(DoublyLinkedList<T>* list)
{
	// initialize some variables
	DoubleNode<T> *it1 = leftEnd, *it2 = list->leftEnd;
	DoublyLinkedList<T> *newList = new DoublyLinkedList<T>();
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
T DoublyLinkedList<T>::getMax()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	T max = leftEnd->data;
	DoubleNode<T> *it = leftEnd->next;
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
T DoublyLinkedList<T>::getMin()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	T min = leftEnd->data;
	DoubleNode<T> *it = leftEnd->next;
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
T DoublyLinkedList<T>::getSum()
{
	if (isEmpty())
		return 0;

	T sum = leftEnd->data;
	DoubleNode<T> *it = leftEnd->next;
	while (it != nullptr) {
		sum += it->data;
		it = it->next;
	}
	return sum;
}

// A method that gets the average value in the list using the sum
template<class T>
T DoublyLinkedList<T>::getAver()
{
	return getSum() / length;
}

template<class T>
T DoublyLinkedList<T>::getMedian()
{
	// iterate over the middle
	DoubleNode<T> *it = leftEnd;
	for (int i = 0; i < length / 2 - 1; i++) {
		it = it->next;
	}

	// calculate the median
	T med;
	if (length & 1)
		med = it->next->data;
	else
		med = (it->data + it->next->data) / 2;

	return med;
}

template<class T>
T DoublyLinkedList<T>::getStrDev()
{
	T mean = getAver(), stdDev = 0;
	DoubleNode<T> *it = leftEnd;
	while (it != nullptr) {
		stdDev += (it->data - mean) * (it->data - mean);
		it = it->next;
	}
	stdDev /= length;
	stdDev = sqrt(stdDev);
	return stdDev;
}

// A method that gets the second maximum value in the list
template<class T>
T DoublyLinkedList<T>::getMaxSecond()
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
	DoubleNode<T> *it = leftEnd->next->next;
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
T DoublyLinkedList<T>::getMinSecond()
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
	DoubleNode<T> *it = leftEnd->next->next;
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
DoublyLinkedList<T>* DoublyLinkedList<T>::split()
{
	// create a new list for the right half
	DoublyLinkedList<T> *rightHalf = new DoublyLinkedList<T>();

	// update the length
	rightHalf->length = length - length / 2;
	length = length / 2;

	// iterate untill the breaking point
	DoubleNode<T> *it = leftEnd;
	for (int i = 0; i < length - 1; i++) {
		it = it->next;
	}

	// Split the list 
	rightHalf->leftEnd = it->next;
	rightHalf->rightEnd = rightEnd;
	rightEnd = it;
	rightEnd->next = nullptr;
	rightHalf->leftEnd->prev = nullptr;

	// return the new list
	return rightHalf;
}

// A method that Inserts elements and maintains sorted order list (Similar to Insert)
template<class T>
void DoublyLinkedList<T>::insert(T element)
{
	// create the new node
	DoubleNode<T> *newNode = new DoubleNode<T>();
	newNode->data = element;

	// in case it's empty
	if (isEmpty()) {
		leftEnd = rightEnd = newNode;
	}

	// insert in case at the beginning
	else if (leftEnd->data > element) {
		newNode->next = leftEnd;
		leftEnd->prev = newNode;
		leftEnd = newNode;
	}

	// in case insertion should be at the end
	else if (rightEnd->data < element) {
		rightEnd->next = newNode;
		newNode->prev = rightEnd;
		rightEnd = newNode;
	}

	// otherwise, in case in between
	else {
		// iterate until the proper position
		DoubleNode<T> *it = leftEnd;
		while (it->next != nullptr && it->next->data < element)
			it = it->next;

		DoubleNode<T> *temp = it->next;
		it->next = newNode;
		newNode->prev = it;
		newNode->next = temp;
		temp->prev = newNode;
	}

	length++;
}

// A method to check if a list is sorted
template<class T>
bool DoublyLinkedList<T>::isSorted()
{
	if (isEmpty())
		return true;

	DoubleNode<T> *it = leftEnd;
	while (it->next != nullptr) {
		if (it->data > it->next->data)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only even values
template<class T>
bool DoublyLinkedList<T>::isEven()
{
	DoubleNode<T> *it = leftEnd;
	while (it != nullptr) {
		if (it->data % 2 != 0)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only odd values
template<class T>
bool DoublyLinkedList<T>::isOdd()
{
	DoubleNode<T> *it = leftEnd;
	while (it != nullptr) {
		if (it->data % 2 != 1)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list is empty
template<class T>
bool DoublyLinkedList<T>::isEmpty() {
	return (length == 0);
}

// A method that checks valid index
template<class T>
void DoublyLinkedList<T>::checkIndex(int index) {
	if (index < 0 || index > length)
		throw std::out_of_range("Index Out of Bounds");
}
