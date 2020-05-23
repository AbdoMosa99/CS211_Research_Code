/* this implementation of Circular Linked List
	is zero-indexed
*/

#include "CircularLinkedList.h"


// A constructor to initialize data members
template<class T>
CircularLinkedList<T>::CircularLinkedList()
{
	head = last = nullptr;
	length = 0;
}

template<class T>
CircularLinkedList<T>::~CircularLinkedList()
{
	// iterate and delete every node
	SingleNode<T> *it = head, *temp;
	for (int i = 0; i < length; i++) {
		temp = it;
		it = it->next;
		delete temp;
	}
	head = last = nullptr;
	length = 0;
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
	if (k < 0 || k >= length)
		return false;

	// declare an iterator ptr
	SingleNode<T> *it = head;

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
	SingleNode<T> *it = head, *temp;

	// check index and that's not empty
	if (k < 0 || k >= length || isEmpty())
		return *this;


	// in case it's the first element
	else if (k == 0) {
		temp = head;
		head = head->next;
		last->next = head;
	}

	// otherwise iterate untill the prev to the position given
	else {
		for (int i = 0; i < k - 1; i++) {
			it = it->next;
		}

		// in case it's the last element 
		if (k == length - 1) {
			temp = last;
			last = it;
			last->next = head;
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

// A methdod that inserts an element into agiven position
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
		head = last = newNode;
		last->next = head;
	}

	// insert in case at the beginning
	else if (k == 0) {
		newNode->next = head;
		head = newNode;
		last->next = head;
	}

	// in case at the end
	if (k == length) {
		last->next = newNode;
		last = newNode;
		last->next = head;
	}

	// otherwise, in case in between
	else {
		// iterate untill the position given
		SingleNode<T> *it = head;
		for (int i = 0; i < k - 1; i++)
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
	SingleNode<T> *it = head;
	for (int i = 0; i < length; i++) {
		out << it->data;
		if (it != last)
			out << ", ";
		it = it->next;
	}
}

// overload the operator << to work with this object
template<class T>
std::ostream & operator<<(std::ostream & out, const CircularLinkedList<T>& x)
{
	x.Output(out);
	return out;
}

// A method to get the length Iteratively
template<class T>
int CircularLinkedList<T>::getLengthIterative()
{
	// in case it's already empty
	if (head == nullptr)
		return 0;

	// otherwise, start counting with 1 considering the last
	int l = 1;
	SingleNode<T> *it = head;
	while (it != last) {
		l++;
		it = it->next;
	}

	return l;
}

// A method to get the length Recusively
template<class T>
int CircularLinkedList<T>::getLengthRecursive()
{
	static SingleNode<T> *it = head;
	if (it == last)
		return 1;
	it = it->next;
	return 1 + getLengthRecursive();
}

// A method that swaps two elements without swapping the data inside
template<class T>
void CircularLinkedList<T>::swap(int firstIndex, int secondIndex)
{
	// check indexes
	if (firstIndex < 0 || firstIndex >= length
		|| secondIndex < 0 || secondIndex >= length)
		throw std::out_of_range("Index Out of Bounds");

	// declare some pointers to work with
	SingleNode<T> *firstNodePrev = last, *firstNode = head,
		*secondNodePrev = last, *secondNode = head;

	// get the first node and its previous
	if (firstIndex != 0) {
		firstNodePrev = head;
		for (int i = 0; i < firstIndex - 1; i++)
			firstNodePrev = firstNodePrev->next;
		firstNode = firstNodePrev->next;
	}

	// get the second node and its previous
	if (secondIndex != 0) {
		secondNodePrev = head;
		for (int i = 0; i < secondIndex - 1; i++)
			secondNodePrev = secondNodePrev->next;
		secondNode = secondNodePrev->next;
	}

	// swap the previous nexts
	firstNodePrev->next = secondNode;
	secondNodePrev->next = firstNode;

	// swap the nodes nexts
	SingleNode<T> *temp = firstNode->next;
	firstNode->next = secondNode->next;
	secondNode->next = temp;

	// update list pointers
	if (firstIndex == 0)
		head = secondNode;
	if (secondIndex == 0)
		head = firstNode;
	if (firstIndex == length - 1)
		last = secondNode;
	if (secondIndex == length - 1)
		last = firstNode;
}

// A method that reverses the linked list
template<class T>
void CircularLinkedList<T>::reverse()
{
	if (isEmpty())
		return;

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

	// update the pointers
	last = head;
	head = fakeStart;
	last->next = head;
	
}

// A method that merges 2 sorted lists into another sorted one
template<class T>
CircularLinkedList<T>* CircularLinkedList<T>::merge(CircularLinkedList<T>* list)
{
	// initialize some variables
	SingleNode<T> *it1 = head, *it2 = list->head;
	int i = 0, j = 0;
	CircularLinkedList<T> *newList = new CircularLinkedList<T>();
	int c = 0;

	// use merge technique and insert to the new list
	while (i < length && j < length) {
		if (it1->data < it2->data) {
			newList->Insert(c++, it1->data);
			it1 = it1->next;
			i++;
		}
		else {
			newList->Insert(c++, it2->data);
			it2 = it2->next;
			j++;
		}
	}

	// insert the rest 
	while (i < length) {
		newList->Insert(i++, it1->data);
		it1 = it1->next;
		i++;
	}
	while (j < length) {
		newList->Insert(i++, it2->data);
		it2 = it2->next;
		j++;
	}

	return newList;
}

// A method that gets the maximum value in the list
template<class T>
T CircularLinkedList<T>::getMax()
{
	if (isEmpty())
		throw std::exception("Empty List!");

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
	if (isEmpty())
		throw std::exception("Empty List!");

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
	if (isEmpty())
		return 0;

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
	for (int i = 0; i < length; i++) {
		stdDev += (it->data - mean) * (it->data - mean);
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
	// check validation
	if (length < 2)
		throw std::exception("Not Enough Elements!");

	// initialize the max and second max
	T max, secondMax;
	if (head->data > head->next->data) {
		max = head->data;
		secondMax = head->next->data;
	}
	else {
		max = head->next->data;
		secondMax = head->data;
	}

	// iterate from the third position
	SingleNode<T> *it = head->next->next;
	while (it != head) {
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
T CircularLinkedList<T>::getMinSecond()
{
	// check validation
	if (length < 2)
		throw std::exception("Not Enough Elements!");

	// initialize the min and second min
	T min, secondMin;
	if (head->data < head->next->data) {
		min = head->data;
		secondMin = head->next->data;
	}
	else {
		min = head->next->data;
		secondMin = head->data;
	}

	// iterate from the third position
	SingleNode<T> *it = head->next->next;
	while (it != head) {
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
CircularLinkedList<T>* CircularLinkedList<T>::split()
{
	// create a new list for the right half
	CircularLinkedList<T> *rightHalf = new CircularLinkedList<T>();

	// update the lengths
	rightHalf->length = length - length / 2;
	length = length / 2;

	// iterate untill the breaking point
	SingleNode<T> *it = head;
	for (int i = 0; i < length - 1; i++) {
		it = it->next;
	}

	// Split the list 
	rightHalf->head = it->next;
	rightHalf->last = last;
	rightHalf->last->next = rightHalf->head;
	last = it;
	last->next = head;
	

	// return the new list
	return rightHalf;
}

// A method that Inserts elements and maintains sorted order list (Similar to Insert)
template<class T>
void CircularLinkedList<T>::insert(T element)
{
	// create the new node
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = element;

	// in case it's empty
	if (isEmpty()) {
		head = last = newNode;
		last->next = head;
	}

	// in case insertion should be at the beginning
	else if (head->data > element) {
		newNode->next = head;
		head = newNode;
		last->next = head;
	}

	// in case insertion should be at the end
	else if (last->data < element) {
		last->next = newNode;
		last = newNode;
		last->next = head;
	}

	// otherwise, in case in between
	else {
		// iterate untill the proper position 
		SingleNode<T> *it = head;
		while (it->next->data < element)
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
	for (int i = 0; i < length; i++) {
		if (it->data % 2 != 0)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only odd values
template<class T>
bool CircularLinkedList<T>::isOdd()
{
	SingleNode<T> *it = head;
	for (int i = 0; i < length; i++) {
		if (it->data % 2 != 1)
			return false;
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
