// file BinaryTree.h

#ifndef BinaryTree_
#define BinaryTree_

#include <iostream>
#include "BinaryTreeNode.h"
#include "BinaryTreeNode.cpp"

template<class T>
class BinaryTree
{
public:
	// Constructors & Destructor
	BinaryTree();
	BinaryTree(BinaryTreeNode<T> *u);
	~BinaryTree();

	// Basic Operations
	bool IsEmpty() const;
	bool Root(T& x) const;
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void PreOrder(void(*Visit)(BinaryTreeNode<T> *u));
	void InOrder(void(*Visit)(BinaryTreeNode<T> *u));
	void PostOrder(void(*Visit)(BinaryTreeNode<T> *u));
	void LevelOrder(void(*Visit)(BinaryTreeNode<T> *u));

	// required methods ordered ascendingly
	bool search(T &x);
	int getHeight();
	int getHeight(BinaryTreeNode<T>* node);
	T getMax();
	T getMin();
	T getSum();
	T getAver();
	T getMedian();
	T getStrDev();
	T getMaxSecond();
	T getMinSecond();

private:
	BinaryTreeNode<T> *root;  // pointer to root
};

#endif
