#ifndef Single_
#define Single_

#include <iostream>
#include <string>
#include "snode.h"
#include "SNode.cpp"

template <class T>
class SinglyLinkedList
{
public:
	// constructor and destructor
	SinglyLinkedList();
	~SinglyLinkedList();

	// basic operations 
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	SinglyLinkedList<T>& Delete(int k, T& x);
	SinglyLinkedList<T>& Insert(int k, const T& x);
	void Output(std::ostream& out) const;

	// required methods ordered ascendingly
	int getLengthIterative();
	int getLengthRecursive();
	void swap(int firstIndex, int secondIndex);
	void reverse();
	SinglyLinkedList<T>* merge(SinglyLinkedList *list);
	T getMax();
	T getMin();
	T getSum();
	T getAver();
	T getMaxSecond();
	T getMinSecond();
	SinglyLinkedList<T>* split();
	void insert(T element);
	bool isSorted();
	bool isEven();
	bool isOdd();

private:
	// data members
	SingleNode<T> *leftEnd, *rightEnd;
	int length;

	// additional methods needed 
	bool isEmpty();
	void checkIndex(int index);
};

#endif
