// header file lqueue.h
// linked queue

#ifndef LinkedQueue_
#define LinkedQueue_

#include "SNode.h"
#include "SNode.cpp"
#include <iostream>

template<class T>
class LinkedQueue
{
public:
	LinkedQueue(); // constructor
	~LinkedQueue(); // destructor

	// basic operations
	bool IsEmpty() const;
	bool IsFull() const;
	T First() const; // return first element
	T Last() const; // return last element
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);

	// required methods ordered ascendingly
	void reverse();
	LinkedQueue<T>* merge(LinkedQueue<T>* stack);
	T getMax();
	T getMin();
	T getSum();
	T getAver();
	T getMedian();
	T getStrDev();
	T getMaxSecond();
	T getMinSecond();
	bool isSorted();
	bool isEven();
	bool isOdd();

private:
	SingleNode<T> *front;  // pointer to first node
	SingleNode<T> *rear;   // pointer to last node
	int length;
};

#endif
