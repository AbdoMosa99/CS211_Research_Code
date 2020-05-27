#include "LinkedQueue.h"


template<class T>
LinkedQueue<T>::LinkedQueue()
{
	front = rear = nullptr;
	length = 0;
}

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	// Queue destructor.  Delete all nodes.
	SingleNode<T> *it;
	while (front != nullptr)
	{
		it = front->next;
		delete front;
		front = it;
	}
}

template<class T>
inline bool LinkedQueue<T>::IsEmpty() const
{
	return (front == nullptr);
}

template<class T>
bool LinkedQueue<T>::IsFull() const
{
	// Is the queue full?
	SingleNode<T> *p;
	try
	{
		p = new SingleNode<T>;
		delete p;
		return false;
	}
	catch (std::exception)
	{
		return true;
	}
}

template<class T>
T LinkedQueue<T>::First() const
{
	// Return first element of queue.  Throw OutOfBounds exception if the queue is empty.
	if (IsEmpty()) throw std::out_of_range("Empty Queue!");
	return front->data;
}

template<class T>
T LinkedQueue<T>::Last() const
{
	// Return last element of queue.  Throw OutOfBounds exception if the queue is empty.
	if (IsEmpty()) throw std::out_of_range("Empty Queue!");
	return rear->data;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	// Add x to rear of queue.  Do not catch possible NoMem exception thrown by new.
	// create node for new element
	SingleNode<T> *newNode = new SingleNode<T>();
	newNode->data = x;

	// add new node to rear of queue
	if (front != nullptr)
		rear->next = newNode; // queue not empty
	else
		front = newNode; // queue empty
	rear = newNode;
	length++;
	return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{
	// Delete first element and put it in x.  Throw OutOfBounds exception if the queue is empty.

	if (IsEmpty()) throw std::out_of_range("Empty Queue!");

	// save element in first node
	x = front->data;

	// delete first node
	SingleNode<T> *temp = front;
	front = front->next;
	delete temp;
	length--;
	return *this;
}

template<class T>
void LinkedQueue<T>::reverse()
{
	// initialize pointers to work with
	SingleNode<T> *originalStart = front;
	SingleNode<T> *fakeStart = nullptr;

	// keep inserting the nodes in the fake list in reversing order
	while (originalStart != nullptr) {
		SingleNode<T> *temp = originalStart->next;
		originalStart->next = fakeStart;
		fakeStart = originalStart;
		originalStart = temp;
	}

	// swap the left and right ends
	originalStart = front;
	front = rear;
	rear = originalStart;
}

template<class T>
LinkedQueue<T>* LinkedQueue<T>::merge(LinkedQueue<T>* queue)
{
	// initialize some variables
	SingleNode<T> *it1 = front, *it2 = queue->front;
	LinkedQueue<T> *newQueue = new LinkedQueue<T>();
	int i = 0;

	// use merge technique and insert to the new queue
	while (it1 != nullptr && it2 != nullptr) {
		if (it1->data < it2->data) {
			newQueue->Add(it1->data);
			it1 = it1->next;
		}
		else {
			newQueue->Add(it2->data);
			it2 = it2->next;
		}
	}

	// insert the rest 
	while (it1 != nullptr) {
		newQueue->Add(it1->data);
		it1 = it1->next;
	}
	while (it2 != nullptr) {
		newQueue->Add(it2->data);
		it2 = it2->next;
	}

	return newQueue;
}

template<class T>
T LinkedQueue<T>::getMax()
{
	if (IsEmpty())
		throw std::exception("Empty Queue!");

	T max = front->data;
	SingleNode<T> *it = front->next;
	while (it != nullptr) {
		if (it->data > max) {
			max = it->data;
		}
		it = it->next;
	}
	return max;
}

template<class T>
T LinkedQueue<T>::getMin()
{
	if (IsEmpty())
		throw std::exception("Empty Queue!");

	T min = front->data;
	SingleNode<T> *it = front->next;
	while (it != nullptr) {
		if (it->data < min) {
			min = it->data;
		}
		it = it->next;
	}
	return min;
}

template<class T>
T LinkedQueue<T>::getSum()
{
	if (IsEmpty())
		return 0;

	T sum = front->data;
	SingleNode<T> *it = front->next;
	while (it != nullptr) {
		sum += it->data;
		it = it->next;
	}
	return sum;
}

template<class T>
T LinkedQueue<T>::getAver()
{
	return getSum() / length;
}

template<class T>
T LinkedQueue<T>::getMedian()
{
	// iterate over the middle
	SingleNode<T> *it = front;
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
T LinkedQueue<T>::getStrDev()
{
	T mean = getAver(), stdDev = 0;
	SingleNode<T> *it = front;
	while (it != nullptr) {
		stdDev += (it->data - mean) * (it->data - mean);
		it = it->next;
	}
	stdDev /= length;
	stdDev = sqrt(stdDev);
	return stdDev;
}

template<class T>
T LinkedQueue<T>::getMaxSecond()
{
	T max, secondMax;
	if (front->data > front->next->data) {
		max = front->data;
		secondMax = front->next->data;
	}
	else {
		max = front->next->data;
		secondMax = front->data;
	}

	// iterate from the third position
	SingleNode<T> *it = front->next->next;
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

template<class T>
T LinkedQueue<T>::getMinSecond()
{
	// initialize the min and second min
	T min, secondMin;
	if (front->data < front->next->data) {
		min = front->data;
		secondMin = front->next->data;
	}
	else {
		min = front->next->data;
		secondMin = front->data;
	}

	// iterate from the third position
	SingleNode<T> *it = front->next->next;
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

template<class T>
bool LinkedQueue<T>::isSorted()
{
	if (IsEmpty())
		return true;

	SingleNode<T> *it = front;
	while (it->next != nullptr) {
		if (it->data > it->next->data)
			return false;
		it = it->next;
	}
	return true;
}

template<class T>
bool LinkedQueue<T>::isEven()
{
	SingleNode<T> *it = front;
	while (it != nullptr) {
		if (it->data % 2 != 0)
			return false;
		it = it->next;
	}
	return true;
}

template<class T>
bool LinkedQueue<T>::isOdd()
{
	SingleNode<T> *it = front;
	while (it != nullptr) {
		if (it->data % 2 != 1)
			return false;
		it = it->next;
	}
	return true;
}
