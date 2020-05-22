#ifndef SingleNode_
#define SingleNode_

template <class T> class SinglyLinkedList;
template <class T> class CircularLinkedList;

template <class T>
class SingleNode
{
	friend SinglyLinkedList<T>;
	friend CircularLinkedList<T>;

	T data;
	SingleNode<T> *next;

public:
	SingleNode();
	~SingleNode();
};

#endif
