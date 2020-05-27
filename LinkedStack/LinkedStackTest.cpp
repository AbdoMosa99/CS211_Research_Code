#include "LinkedStack.h"
#include "LinkedStack.cpp"
#include <iostream>

using namespace std;

void stackTest() {
	LinkedStack<int> stack;
	cout << "\n ----------------- Stack Test ----------------- \n";

	// Add
	stack.Add(1);
	stack.Add(2);
	stack.Add(3);
	stack.Add(4);
	
	// Math   
	cout << "\n Max: " << stack.getMax()
		<< ", Min: " << stack.getMin()
		<< ", Sum: " << stack.getSum()
		<< ", Average: " << stack.getAver() << endl
		<< " Median: " << stack.getMedian()
		<< ", StrDev: " << stack.getStrDev()
		<< ", SecondMax: " << stack.getMaxSecond()
		<< ", SecondMin: " << stack.getMinSecond();

	// boolean
	cout << "\n isSorted: " << stack.isSorted()
		<< ", isEven: " << stack.isEven()
		<< ", isOdd: " << stack.isOdd();

	// Reverse
	stack.reverse();

	// Deletion
	int x;

	cout << "\n Stack should be 4321" << endl << " Stack top is " << stack.Top() << endl;

	stack.Delete(x);
	cout << " Deleted " << x << endl;
	stack.Delete(x);
	cout << " Deleted " << x << endl;
	stack.Delete(x);
	cout << " Deleted " << x << endl;
	stack.Delete(x);
	cout << " Deleted " << x << endl;
}
