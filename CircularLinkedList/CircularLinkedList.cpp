#include "CircularLinkedList.h"


// A constructor to initialize data members
template<class T>
CircularLinkedList<T>::CircularLinkedList()
{
	head = nullptr;
	length = 0;
}

template<class T>
CircularLinkedList<T>::~CircularLinkedList()
{
}

template<class T>
int CircularLinkedList<T>::Length() const
{
	return length;
}

// A method that takes a starting point and a key to check if the key exists
template<class T>
bool CircularLinkedList<T>::Find(int k, T & x) const
{
	if (head->data == x)
		return true;

	// declare an iterator ptr
	SingleNode<T> *it = head->next;

	// iterate until the starting point
	for (int i = 0; i < k; i++) {
		it = it->next;
	}

	// iterate to see if the key exists and returns true
	while (it != head) {
		if (it->data == x)
			return true;
		it = it->next;
	}
	// otherwise
	return false;
}

// A method that searches for a specific key and return its position
template<class T>
int CircularLinkedList<T>::Search(const T & x) const
{
	// declare iterator ptr
	SingleNode<T> *it = head;

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
CircularLinkedList<T>& CircularLinkedList<T>::Delete(int k, T & x)
{
	// iterator ptr
	SingleNode<T> *it = head;

	// in case it's empty, do nothing
	if (isEmpty())
		return *this;

	// in case its the first element
	else if (it->data == x) {
		SingleNode<T> *temp = head, *last = head;
		while (last->next != head) {
			last = last->next;
		}
		head = head->next;
		last->next = head;
		delete temp;
		length--;
	}

	// otherwise iterate and if found then delete
	else {
		while (it->next != head) {
			if (it->next->data == x) {
				SingleNode<T> *temp = it->next;
				it->next = temp->next;
				delete temp;
				length--;
				break;
			}
			it = it->next;
		}
	}
	return *this;
}

template<class T>
CircularLinkedList<T>& CircularLinkedList<T>::Insert(int k, const T & x)
{
	// A method that check the index is valid
	checkIndex(k);

	// create a new node 
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = x;

	// insert in case it's empty
	if (isEmpty()) {
		head = newNode;
		head->next = head;
	}

	// insert in case at the beginning
	else if (k == 0) {
		newNode->next = head;
		SingleNode<T> *last = head;
		while (last->next != head) {
			last = last->next;
		}
		head = newNode;
		last->next = head;
	}

	else {
		// iterate untill the position given
		SingleNode<T> *it = head;
		for (int i = 0; i < k - 1 && it->next != head; i++)
			it = it->next;

		SingleNode<T> *temp = it->next;
		it->next = newNode;
		newNode->next = temp;
	}

	length++;
	return *this;
}

// A method that prints the list to the given stream
template<class T>
void CircularLinkedList<T>::Output(std::ostream & out) const
{
	// iterate and print every element
	out << head->data << ", ";
	SingleNode<T> *it = head->next;
	while (it != head) {
		out << it->data << ", ";
		it = it->next;
	}
	out << std::endl;
}

// A method to get the length Iteratively
template<class T>
int CircularLinkedList<T>::getLengthIterative()
{
	if (head == nullptr)
		return 0;

	int length = 1;
	SingleNode<T> *it = head->next;
	while (it != head) {
		length++;
		it = it->next;
	}
	return length;
}

// A method to get the length Recusively
template<class T>
int CircularLinkedList<T>::getLengthRecursive()
{
	static SingleNode<T> *it = head;
	if (it->next == head)
		return 1;
	it = it->next;
	return 1 + getLengthRecursive();
}

// A method that swaps two elements without swapping the data inside
template<class T>
void CircularLinkedList<T>::swap(int firstIndex, int secondIndex)
{
	// check indexes
	checkIndex(firstIndex);
	checkIndex(secondIndex);

	// get the previous node of the first
	SingleNode<T> *firstNodePrev = head;
	for (int i = 0; i < firstIndex - 1; i++)
		firstNodePrev = firstNodePrev->next;

	// get the previous node of the second
	SingleNode<T> *secondNodePrev = head;
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
void CircularLinkedList<T>::reverse()
{
	// initialize pointers to work with
	SingleNode<T> *originalStart = head->next;
	SingleNode<T> *fakeStart = head;

	// keep inserting the nodes in the fake list in reversing order
	while (originalStart != head) {
		SingleNode<T> *temp = originalStart->next;
		originalStart->next = fakeStart;
		fakeStart = originalStart;
		originalStart = temp;
	}

	head = fakeStart;
	originalStart->next = head;
	
}

// A method that merges 2 sorted lists into another sorted one
template<class T>
CircularLinkedList<T> CircularLinkedList<T>::merge(CircularLinkedList list)
{
	// initialize some variables
	SingleNode<T> *it1 = head, *it2 = list.head;
	CircularLinkedList<T> newList;
	int i = 0;

	// use merge technique and insert to the new list
	while (it1 != nullptr && it2 != nullptr) {
		if (it1->data < it2->data) {
			newList.Insert(i++, it1->data);
			if (it1->next == head)
				it1 = nullptr;
			else
				it1 = it1->next;
		}
		else {
			newList.Insert(i++, it2->data);
			if (it2->next == head)
				it2 = nullptr;
			else
				it2 = it2->next;
		}
	}

	// insert the rest 
	while (it1 != nullptr) {
		newList.Insert(i++, it1->data);
		if (it1->next == head)
			it1 = nullptr;
		else
			it1 = it1->next;
	}
	while (it2 != nullptr) {
		newList.Insert(i++, it2->data);
		if (it2->next == list.head)
			it2 = nullptr;
		else
			it2 = it2->next;
	}

	return newList;
}

// A method that gets the maximum value in the list
template<class T>
T CircularLinkedList<T>::getMax()
{
	T max = head->data;
	SingleNode<T> *it = head->next;
	while (it != head) {
		if (it->data > max) {
			max = it->data;
		}
		it = it->next;
	}
	return max;
}

// A method that gets the minimum value in the list
template<class T>
T CircularLinkedList<T>::getMin()
{
	T min = head->data;
	SingleNode<T> *it = head->next;
	while (it != head) {
		if (it->data < min) {
			min = it->data;
		}
		it = it->next;
	}
	return min;
}

// A method that gets the sum of all elements in the list
template<class T>
T CircularLinkedList<T>::getSum()
{
	T sum = head->data;
	SingleNode<T> *it = head->next;
	while (it != head) {
		sum += it->data;
		it = it->next;
	}
	return sum;
}

// A method that gets the average value in the list using the sum
template<class T>
T CircularLinkedList<T>::getAver()
{
	return getSum() / length;
}

template<class T>
T CircularLinkedList<T>::getMedian()
{
	// iterate over the middle
	SingleNode<T> *it = head;
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
T CircularLinkedList<T>::getStrDev()
{
	T mean = getAver(), stdDev = 0;
	SingleNode<T> *it = head;
	while (it != nullptr) {
		stdDev += (it->data - mean) * (it->data - mean);
		if (it->next == head)
			it = nullptr;
		else
			it = it->next;
	}
	stdDev /= length;
	stdDev = sqrt(stdDev);
	return stdDev;
}

// A method that gets the second maximum value in the list
template<class T>
T CircularLinkedList<T>::getMaxSecond()
{
	T max = getMax();
	T secondMax;
	if (max == head->data)
		secondMax = head->next->data;
	else
		secondMax = head->data;

	SingleNode<T> *it = head->next;
	while (it != head) {
		if (it->data > secondMax && it->data != max) {
			secondMax = it->data;
		}
		it = it->next;
	}
	return secondMax;
}

// A method that gets the second minimum value in the list
template<class T>
T CircularLinkedList<T>::getMinSecond()
{
	T min = getMin();
	T secondMin;
	if (min == head->data)
		secondMin = head->next->data;
	else
		secondMin = head->data;

	SingleNode<T> *it = head->next;
	while (it != head) {
		if (it->data < secondMin && it->data != min) {
			secondMin = it->data;
		}
		it = it->next;
	}
	return secondMin;
}

// A method that splits a list into two halves
template<class T>
CircularLinkedList<T> CircularLinkedList<T>::split()
{
	// create a new list for the right half
	CircularLinkedList<T> rightHalf;

	// update some attributes
	rightHalf.length = length - length / 2;
	length = length / 2;

	// iterate untill the breaking point
	SingleNode<T> *it = head;
	for (int i = 0; i < length - 1; i++) {
		it = it->next;
	}

	// Split the list 
	rightHalf.head = it->next;
	it->next = head;
	it = rightHalf.head;
	while (it->next != head) {
		it = it->next;
	}
	it->next = rightHalf.head;

	// return the new list
	return rightHalf;
}

// A method that Inserts elements and maintains sorted order list (Similar to Insert)
template<class T>
void CircularLinkedList<T>::insert(T element)
{
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = element;
	SingleNode<T> *it = head;

	if (isEmpty()) {
		head = newNode;
		head->next = head;
	}

	else if (it->data > element) {
		newNode->next = it;
		SingleNode<T> *last = head;
		while (last->next != head) {
			last = last->next;
		}
		head = newNode;
		last->next = head;
	}

	else {
		while (it->next != head && it->next->data < element)
			it = it->next;

			SingleNode<T> *temp = it->next;
			it->next = newNode;
			newNode->next = temp;
	}
	length++;
}

// A method to check if a list is sorted
template<class T>
bool CircularLinkedList<T>::isSorted()
{
	if (isEmpty())
		return true;

	SingleNode<T> *it = head;
	while (it->next != head) {
		if (it->data > it->next->data)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only even values
template<class T>
bool CircularLinkedList<T>::isEven()
{
	SingleNode<T> *it = head;
	while (it != nullptr) {
		if (it->data % 2 != 0)
			return false;

		if (it->next == head)
			it = nullptr;
		else
			it = it->next;
	}
	return true;
}

// A method to check if a list contains only odd values
template<class T>
bool CircularLinkedList<T>::isOdd()
{
	SingleNode<T> *it = head;
	while (it != nullptr) {
		if (it->data % 2 != 1)
			return false;
		
		if (it->next == head)
			it = nullptr;
		else
			it = it->next;
	}
	return true;
}

// A method to check if a list is empty
template<class T>
bool CircularLinkedList<T>::isEmpty() {
	return (length == 0);
}

// A method that checks valid index
template<class T>
void CircularLinkedList<T>::checkIndex(int index) {
	if (index < 0 || index > length)
		throw std::out_of_range("Index Out of Bounds");
}
