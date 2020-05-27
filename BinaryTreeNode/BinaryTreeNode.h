#ifndef BinaryTreeNode_
#define BinaryTreeNode_

template <class T> class BinaryTree;

template <class T>
class BinaryTreeNode
{
	friend BinaryTree<T>;

public:
	BinaryTreeNode();
	BinaryTreeNode(const T& d);
	BinaryTreeNode(const T& d, BinaryTreeNode *l, BinaryTreeNode *r);
	~BinaryTreeNode();

private:
	T data;
	BinaryTreeNode<T> *LeftChild, *RightChild;   // left subtree and right subtree
};

#endif
