#include "BinaryTree.h"
#include  "LinkedQueue.h"
#include  "LinkedQueue.cpp"


template<class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<class T>
BinaryTree<T>::BinaryTree(BinaryTreeNode<T>* u)
{
	root = u;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
}

template<class T>
bool BinaryTree<T>::IsEmpty() const
{
	return (root == nullptr);
}

template<class T>
bool BinaryTree<T>::Root(T& x) const
{
	// Return root data in x. Return false if no root.
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;  // no root
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	// Combine left, right, and element to make new tree.
	 // left, right, and this must be different trees.
	// create combined tree
	root = new BinaryTreeNode<T>(element, left.root, right.root);

	// deny access from trees left and right
	left.root = right.root = 0;
}

template<class T>
void BinaryTree<T>::BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	// left, right, and this must be different trees.

	if (!root) throw std::exception(); // check if empty. Tree empty

	// break the tree
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;

	delete root;
	root = 0;
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T> *u))
{
	// Preorder traversal.
	if (root)
	{
		Visit(root);
		((BinaryTree)(root->LeftChild)).PreOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
		((BinaryTree)(root->RightChild)).PreOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
	}
}

template <class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T> *u))
{
	// Inorder traversal.
	if (root)
	{
		((BinaryTree)(root->LeftChild)).InOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
		Visit(root);
		((BinaryTree)(root->RightChild)).InOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
	}
}

template <class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T> *u))
{
	// Postorder traversal.
	if (root)
	{
		((BinaryTree)(root->LeftChild)).PostOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
		((BinaryTree)(root->RightChild)).PostOrder(Visit); // Type casting from BinaryTreeNode to BinaryTree using the second constductor
		Visit(root);
	}
}

template <class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T> *u))
{
	// Level-order traversal.
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		Visit(t);
	}
}

template<class T>
bool BinaryTree<T>::search(T & x)
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		if (t->data == x)
			return true;
	}
	return false;
}

template<class T>
int BinaryTree<T>::getHeight()
{
	return getHeight(root);
}

template<class T>
int BinaryTree<T>::getHeight(BinaryTreeNode<T>* node)
{
	if (node == nullptr)
		return 0;

	int leftHeight = getHeight(node->LeftChild);
	int rightHeight = getHeight(node->RightChild);

	if (leftHeight > rightHeight)
		return(leftHeight + 1);
	else 
		return(rightHeight + 1);
}

template<class T>
T BinaryTree<T>::getMax()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T max = root->data;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		if (t->data > max)
			max = t->data;
	}
	return max;
}

template<class T>
T BinaryTree<T>::getMin()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T min = root->data;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		if (t->data < min)
			min = t->data;
	}
	return min;
}

template<class T>
T BinaryTree<T>::getSum()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T sum = 0;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		sum += t->data;
	}
	return sum;
}

template<class T>
T BinaryTree<T>::getAver()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T sum = 0;
	int length = 0;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		sum += t->data;
		length++;
	}
	return sum / length;
}

template<class T>
T BinaryTree<T>::getMedian()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	LinkedQueue<T> Q2;
	BinaryTreeNode<T> *t;
	int length = 0;
	t = root;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		Q2.Add(t->data);
		length++;
	}
	return Q2.getMedian();
}

template<class T>
T BinaryTree<T>::getStrDev()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T mean = getAver(), stdDev = 0;
	int length = 0;
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		stdDev += (t->data - mean) * (t->data - mean);
		length++;
	}
	stdDev /= length;
	stdDev = sqrt(stdDev);
	return stdDev;
}

template<class T>
T BinaryTree<T>::getMaxSecond()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T max, secondMax;
	if (root->data > root->LeftChild->data) {
		max = root->data;
		secondMax = root->LeftChild->data;
	}
	else {
		max = root->LeftChild->data;
		secondMax = root->data;
	}
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);

		if (t->data > max) {
			secondMax = max;
			max = t->data;
		}
		else if (t->data > secondMax && t->data != max) {
			secondMax = t->data;
		}
	}
	return secondMax;
}

template<class T>
T BinaryTree<T>::getMinSecond()
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	T min, secondMin;
	if (root->data < root->LeftChild->data) {
		min = root->data;
		secondMin = root->LeftChild->data;
	}
	else {
		min = root->LeftChild->data;
		secondMin = root->data;
	}
	Q.Add(root);
	while (!Q.IsEmpty())
	{
		Q.Delete(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);

		if (t->data < min) {
			secondMin = min;
			min = t->data;
		}
		else if (t->data < secondMin && t->data != min) {
			secondMin = t->data;
		}
	}
	return secondMin;
}
