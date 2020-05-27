#include "BinaryTreeNode.h"


template<class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	LeftChild = RightChild = 0;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T & d)
{
	data = d;
	LeftChild = RightChild = 0;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T & d, BinaryTreeNode * l, BinaryTreeNode * r)
{
	data = d;
	LeftChild = l; RightChild = r;
}

template<class T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
}
