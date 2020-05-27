#include <iostream>
#include "BinaryTree.h"
#include "BinaryTree.cpp"

using namespace std;

int counts = 0;

template<class T>
void ct(BinaryTreeNode<T> *t)
{
	counts++;
}

void binaryTreeTest() {
	cout << "\n ----------------- Binary Tree Test ----------------- \n";
	BinaryTree<int> a, x, y, z;

	y.MakeTree(1, a, a);
	z.MakeTree(2, a, a);
	x.MakeTree(3, y, z);
	y.MakeTree(4, x, a);

	y.PreOrder(ct);
	cout << " Using PreOrder; Count of nodes is " << counts << endl;

	counts = 0;
	y.InOrder(ct);
	cout << " Using InOrder; Count of nodes is " << counts << endl;

	counts = 0;
	y.PostOrder(ct);
	cout << " Using PostOrder; Count of nodes is " << counts << endl;

	counts = 0;
	y.LevelOrder(ct);
	cout << " Using LevelOrder; Count of nodes is " << counts << endl;

	int three = 3;
	cout << " contains 3? " << y.search(three) << endl;
	cout << " Height: " << y.getHeight() << endl;
	cout << " Max: " << y.getMax() << endl;
	cout << " Min: " << y.getMin() << endl;
	cout << " Sum: " << y.getSum() << endl;
	cout << " Average: " << y.getAver() << endl;
	cout << " Median: " << y.getMedian() << endl;
	cout << " Standard Deviation: " << y.getStrDev() << endl;
	cout << " Second Max: " << y.getMaxSecond() << endl;
	cout << " Second Min: " << y.getMinSecond() << endl;
}
