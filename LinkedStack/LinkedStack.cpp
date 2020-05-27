#include "LinkedStack.h"



template<class T>
LinkedStack<T>::LinkedStack()
{
	top = nullptr;
	length = 0;
}

template<class T>
LinkedStack<T>::~LinkedStack()
{
	SingleNode<T> *it;
	while (top != nullptr)
	{
		it = top->next;
		delete top;
		top = it;
	}
}

template<class T>
bool LinkedStack<T>::IsFull() const
{
	//Is the stack full?
	try
	{
		SingleNode<T> *temp = new SingleNode<T>;
		delete temp;
		return false;
	}
	catch (std::exception) { return true; }
}

template<class T>
T LinkedStack<T>::Top() const
{
	// Return top element.
	if (IsEmpty()) throw std::out_of_range("Empty Stack!");
	return top->data;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Add(const T& x)
{
	// Add x to stack.
	SingleNode<T> *newNode = new SingleNode<T>;
	newNode->data = x;
	newNode->next = top;
	top = newNode;
	length++;
	return *this;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Delete(T& x)
{
	// Delete top element and put it in x.
	if (IsEmpty()) throw std::out_of_range("Empty Stack!");
	x = top->data;
	SingleNode<T> *temp = top;
	top = top->next;
	delete temp;
	length--;
	return *this;
}

template<class T>
bool LinkedStack<T>::IsEmpty() const
{
	return (top == nullptr);
}

// A method that reverses the linked stack
template<class T>
void LinkedStack<T>::reverse()
{
	// initialize pointers to work with
	SingleNode<T> *originalStart = top;
	SingleNode<T> *fakeStart = nullptr;

	// keep inserting the nodes in the fake stack in reversing order
	while (originalStart != nullptr) {
		SingleNode<T> *temp = originalStart->next;
		originalStart->next = fakeStart;
		fakeStart = originalStart;
		originalStart = temp;
	}

	top = fakeStart;
}

// A method that merges 2 sorted stacks into another sorted one
template<class T>
LinkedStack<T>* LinkedStack<T>::merge(LinkedStack<T> *stack)
{
	// initialize some variables
	SingleNode<T> *it1 = top, *it2 = stack->top;
	LinkedStack<T> *newStack = new LinkedStack<T>();
	int i = 0;

	// use merge technique and insert to the new stack
	while (it1 != nullptr && it2 != nullptr) {
		if (it1->data < it2->data) {
			newStack->Add(it1->data);
			it1 = it1->next;
		}
		else {
			newStack->Add(it2->data);
			it2 = it2->next;
		}
	}

	// insert the rest 
	while (it1 != nullptr) {
		newStack->Add(it1->data);
		it1 = it1->next;
	}
	while (it2 != nullptr) {
		newStack->Add(it2->data);
		it2 = it2->next;
	}

	return newStack;
}

// A method that gets the maximum value in the stack
template<class T>
T LinkedStack<T>::getMax()
{
	if (IsEmpty())
		throw std::exception("Empty Stack!");

	T max = top->data;
	SingleNode<T> *it = top->next;
	while (it != nullptr) {
		if (it->data > max) {
			max = it->data;
		}
		it = it->next;
	}
	return max;
}

// A method that gets the minimum value in the stack
template<class T>
T LinkedStack<T>::getMin()
{
	if (IsEmpty())
		throw std::exception("Empty Stack!");

	T min = top->data;
	SingleNode<T> *it = top->next;
	while (it != nullptr) {
		if (it->data < min) {
			min = it->data;
		}
		it = it->next;
	}
	return min;
}

// A method that gets the sum of all elements in the stack
template<class T>
T LinkedStack<T>::getSum()
{
	if (IsEmpty())
		return 0;

	T sum = top->data;
	SingleNode<T> *it = top->next;
	while (it != nullptr) {
		sum += it->data;
		it = it->next;
	}
	return sum;
}

// A method that gets the average value in the stack using the sum
template<class T>
T LinkedStack<T>::getAver()
{
	return getSum() / length;
}

template<class T>
T LinkedStack<T>::getMedian()
{
	// iterate over the middle
	SingleNode<T> *it = top;
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
T LinkedStack<T>::getStrDev()
{
	T mean = getAver(), stdDev = 0;
	SingleNode<T> *it = top;
	while (it != nullptr) {
		stdDev += (it->data - mean) * (it->data - mean);
		it = it->next;
	}
	stdDev /= length;
	stdDev = sqrt(stdDev);
	return stdDev;
}

// A method that gets the second maximum value in the stack
template<class T>
T LinkedStack<T>::getMaxSecond()
{
	// initialize the max and second max
	T max, secondMax;
	if (top->data > top->next->data) {
		max = top->data;
		secondMax = top->next->data;
	}
	else {
		max = top->next->data;
		secondMax = top->data;
	}

	// iterate from the third position
	SingleNode<T> *it = top->next->next;
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

// A method that gets the second minimum value in the stack
template<class T>
T LinkedStack<T>::getMinSecond()
{
	// initialize the min and second min
	T min, secondMin;
	if (top->data < top->next->data) {
		min = top->data;
		secondMin = top->next->data;
	}
	else {
		min = top->next->data;
		secondMin = top->data;
	}

	// iterate from the third position
	SingleNode<T> *it = top->next->next;
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

// A method to check if a list is sorted
template<class T>
bool LinkedStack<T>::isSorted()
{
	if (IsEmpty())
		return true;

	SingleNode<T> *it = top;
	while (it->next != nullptr) {
		if (it->data < it->next->data)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only even values
template<class T>
bool LinkedStack<T>::isEven()
{
	SingleNode<T> *it = top;
	while (it != nullptr) {
		if (it->data % 2 != 0)
			return false;
		it = it->next;
	}
	return true;
}

// A method to check if a list contains only odd values
template<class T>
bool LinkedStack<T>::isOdd()
{
	SingleNode<T> *it = top;
	while (it != nullptr) {
		if (it->data % 2 != 1)
			return false;
		it = it->next;
	}
	return true;
}
