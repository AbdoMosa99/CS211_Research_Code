#ifndef Double_
#define Double_

#include <iostream>
#include <string>
#include "dnode.h"
#include "DNode.cpp"

template <class T>
class DoublyLinkedList
{
public:
	// constructor and destructor
	DoublyLinkedList();
	~DoublyLinkedList();

	// basic operations 
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	DoublyLinkedList<T>& Delete(int k, T& x);
	DoublyLinkedList<T>& Insert(int k, const T& x);
	void Output(std::ostream& out) const;

	// required methods ordered ascendingly
	int getLengthIterative();
	int getLengthRecursive();
	void swap(int firstIndex, int secondIndex);
	void reverse();
	DoublyLinkedList<T>* merge(DoublyLinkedList<T>* list);
	T getMax();
	T getMin();
	T getSum();
	T getAver();
	T getMedian();
	T getStrDev();
	T getMaxSecond();
	T getMinSecond();
	DoublyLinkedList<T>* split();
	void insert(T element);
	bool isSorted();
	bool isEven();
	bool isOdd();

private:
	// data members
	DoubleNode<T> *leftEnd, *rightEnd;
	int length;

	// additional methods needed 
	bool isEmpty();
	void checkIndex(int index);
};

#endif
