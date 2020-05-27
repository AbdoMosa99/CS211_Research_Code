// linked stack
#ifndef LinkedStack_
#define LinkedStack_

#include <iostream>
#include "SNode.h"
#include "SNode.cpp"

template<class T>
class LinkedStack
{
public:
	LinkedStack();
	~LinkedStack();

	// basic operations
	T Top() const;
	LinkedStack<T>& Add(const T& x);
	LinkedStack<T>& Delete(T& x);
	bool IsEmpty() const;
	bool IsFull() const;

	// required methods ordered ascendingly
	void reverse();
	LinkedStack<T>* merge(LinkedStack<T>* stack);
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
	SingleNode<T> *top; // pointer to top node
	int length;
};

#endif;
