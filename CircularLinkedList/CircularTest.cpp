#include "CircularLinkedList.h"
#include "CircularLinkedList.cpp"

using namespace std;

void CircularTest() {
	CircularLinkedList<int> list;
	cout << "\n ----------------- Circular Test ----------------- \n";

	// Insert
	list.Insert(0, 5);
	list.Insert(0, 4);
	list.Insert(2, 6);
	list.Insert(3, 7);
	cout << "\n After normal Insertion: ";
	list.Output(cout);

	// sorted insert
	list.insert(1);
	list.insert(3);
	list.insert(8);
	list.insert(2);
	cout << "\n After sorted Insertion: ";
	list.Output(cout);

	// length
	cout << "\n The length is: " << list.getLengthIterative() << ", "
		<< list.getLengthRecursive() << ", "
		<< list.Length() << endl;

	// Split and Merge
	CircularLinkedList<int> list2 = list.split();
	list = list.merge(list2);
	cout << "\n After Splitting and Merging: ";
	list.Output(cout);

	// Math   
	cout << "\n Max: " << list.getMax()
		<< ", Min: " << list.getMin()
		<< ", Sum: " << list.getSum() << endl
		<< " Average: " << list.getAver()
		<< " Median: " << list.getMedian()
		<< " Standard Deviation: " << list.getStrDev()
		<< ", SecondMax: " << list.getMaxSecond()
		<< ", SecondMin: " << list.getMinSecond() << endl;

	// boolean
	cout << "\n isSorted: " << list.isSorted()
		<< ", isEven: " << list.isEven()
		<< ", isOdd: " << list.isOdd() << endl;

	// Reverse
	list.reverse();
	cout << "\n After Reversing: ";
	list.Output(cout);

	// Swap
	list.swap(2, 6);
	list.swap(1, 5);
	cout << "\n After Swapping 2 with 6 and 1 with 5: ";
	list.Output(cout);

	// Search & Delete
	int one = 1, nine = 9;
	cout << "\n 1 exist? " << list.Find(0, one) << ", 9 exist? " << list.Find(0, nine);
	cout << "\n Where is 2? " << list.Search(2) << ", where is 10? " << list.Search(10);
	list.Delete(0, one);
	cout << "\n After Deleting 1: ";
	list.Output(cout);
}