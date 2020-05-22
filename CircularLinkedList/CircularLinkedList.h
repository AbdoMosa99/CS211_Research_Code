#ifndef Circular_
#define Circular_

#include <iostream>
#include <string>
#include "snode.h"
#include "SNode.cpp"

template <class T>
class CircularLinkedList
{
public:
	// constructor and destructor
	CircularLinkedList();
	~CircularLinkedList();

	// basic operations 
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	CircularLinkedList<T>& Delete(int k, T& x);
	CircularLinkedList<T>& Insert(int k, const T& x);
	void Output(std::ostream& out) const;

	// required methods ordered ascendingly
	int getLengthIterative();
	int getLengthRecursive();
	void swap(int firstIndex, int secondIndex);
	void reverse();
	CircularLinkedList<T> merge(CircularLinkedList list);
	T getMax();
	T getMin();
	T getSum();
	T getAver();
	T getMedian();
	T getStrDev();
	T getMaxSecond();
	T getMinSecond();
	CircularLinkedList<T> split();
	void insert(T element);
	bool isSorted();
	bool isEven();
	bool isOdd();

private:
	// data members
	SingleNode<T> *head;
	int length;

	// additional methods needed 
	bool isEmpty();
	void checkIndex(int index);
};

#endif
