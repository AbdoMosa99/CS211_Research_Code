#include "DoublyLinkedList.h"
#include "DoublyLinkedList.cpp"

using namespace std;

void doubleTest() {
	DoublyLinkedList<int> list;
	cout << "\n ----------------- Double Test ----------------- \n";

	// Insert
	list.Insert(0, 5);
	list.Insert(0, 4);
	list.Insert(2, 6);
	list.Insert(3, 7);
	cout << "\n After normal Insertion: " << list;

	// sorted insert
	list.insert(1);
	list.insert(3);
	list.insert(8);
	list.insert(2);
	cout << "\n After sorted Insertion: " << list;

	// length
	cout << "\n The length is: " << list.getLengthIterative() << ", "
		<< list.getLengthRecursive() << ", "
		<< list.Length();

	// Split and Merge
	DoublyLinkedList<int> *list2 = list.split();
	list = *list.merge(list2);
	cout << "\n After Splitting and Merging: " << list;

	// Math   
	cout << "\n Max: " << list.getMax()
		<< ", Min: " << list.getMin()
		<< ", Sum: " << list.getSum()
		<< ", Average: " << list.getAver()
		<< ", Median: " << list.getMedian()
		<< ", Standard Deviation: " << list.getStrDev()
		<< ", SecondMax: " << list.getMaxSecond()
		<< ", SecondMin: " << list.getMinSecond();

	// boolean
	cout << "\n isSorted: " << list.isSorted()
		<< ", isEven: " << list.isEven()
		<< ", isOdd: " << list.isOdd();

	// Reverse
	list.reverse();
	cout << "\n After Reversing: " << list;

	// Swap
	list.swap(2, 6);
	list.swap(1, 5);
	cout << "\n After Swapping 2 with 6 and 1 with 5: " << list;

	// Search & Delete
	int one, four;
	list.Find(1, one);
	list.Find(4, four);
	cout << "\n in pos 1: " << one << ", in pos 4: " << four;
	cout << "\n Where is 2? " << list.Search(2) << ", where is 10? " << list.Search(10);
	list.Delete(0, one);
	cout << "\n After Deleting the first element " << one << ": " << list << endl;
}