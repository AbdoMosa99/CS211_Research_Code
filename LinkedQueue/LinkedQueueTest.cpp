#include "LinkedQueue.h"
#include "LinkedQueue.cpp"
#include <iostream>

using namespace std;

void queueTest() {
	LinkedQueue<int> queue;
	cout << "\n ----------------- Queue Test ----------------- \n";

	// Add
	queue.Add(1);
	queue.Add(2);
	queue.Add(3);
	queue.Add(4);

	// Math   
	cout << "\n Max: " << queue.getMax()
		<< ", Min: " << queue.getMin()
		<< ", Sum: " << queue.getSum()
		<< ", Average: " << queue.getAver() << endl
		<< " Median: " << queue.getMedian()
		<< ", StrDev: " << queue.getStrDev()
		<< ", SecondMax: " << queue.getMaxSecond()
		<< ", SecondMin: " << queue.getMinSecond();

	// boolean
	cout << "\n isSorted: " << queue.isSorted()
		<< ", isEven: " << queue.isEven()
		<< ", isOdd: " << queue.isOdd();

	// Reverse
	queue.reverse();

	// Deletion
	int x;

	cout << "\n Queue should be 4321";
	cout << "\n " << queue.First() << " is first, " << queue.Last() << " is last" << endl;

	queue.Delete(x);
	cout << " Deleted " << x << endl;
	queue.Delete(x);
	cout << " Deleted " << x << endl;
	queue.Delete(x);
	cout << " Deleted " << x << endl;
	queue.Delete(x);
	cout << " Deleted " << x << endl;
}
