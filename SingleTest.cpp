#include "SinglyLinkedList.h"
#include "SinglyLinkedList.cpp"

using namespace std;

void singleTest() {
	SinglyLinkedList<int> list;
	cout << "\n ----------------- Single Test ----------------- \n";

	// Insert
	list.Insert(0, 5);
	list.Insert(0, 4);
	list.Insert(2, 6);
	list.Insert(3, 7);
	cout << "\n After normal Insertion: ";
	cout << list;

	// sorted insert
	list.insert(1);
	list.insert(3);
	list.insert(8);
	list.insert(2);
	cout << "\n After sorted Insertion: ";
	cout << list;

	// length
	cout << "\n The length is: " << list.getLengthIterative() << ", "
		<< list.getLengthRecursive() << ", "
		<< list.Length() << endl;

	// Split and Merge
	SinglyLinkedList<int>* list2 = list.split();
	list = *list.merge(list2);
	cout << "\n After Splitting and Merging: ";
	cout << list;

	// Math   
	cout << "\n Max: " << list.getMax()
		<< ", Min: " << list.getMin()
		<< ", Sum: " << list.getSum() << endl
		<< " Average: " << list.getAver()
		<< ", SecondMax: " << list.getMaxSecond()
		<< ", SecondMin: " << list.getMinSecond() << endl;

	// boolean
	cout << "\n isSorted: " << list.isSorted()
		<< ", isEven: " << list.isEven()
		<< ", isOdd: " << list.isOdd() << endl;

	// Reverse
	list.reverse();
	cout << "\n After Reversing: ";
	cout << list;

	// Swap
	list.swap(2, 6);
	list.swap(1, 5);
	cout << "\n After Swapping 2 with 6 and 1 with 5: ";
	cout << list;

	// Search & Delete
	int one, four;
	list.Find(1, one);
	list.Find(4, four);
	cout << "\n in pos 1: " << one << ", in pos 4: " << four;
	cout << "\n Where is 2? " << list.Search(2) << ", where is 10? " << list.Search(10);
	list.Delete(0, one);
	cout << "\n After Deleting the first element " << one << ": ";
	cout << list;
	cout << endl;
}