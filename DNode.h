#ifndef DoubleNode_
#define DoubleNode_

template <class T> class DoublyLinkedList;

template <class T>
class DoubleNode
{
	friend DoublyLinkedList<T>;

	T data;
	DoubleNode<T> *next, *prev;

public:
	DoubleNode();
	~DoubleNode();
};

#endif