
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 8, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp llist_test.cpp -o llist_test
 * File Type:    source file (llist_test.cpp)
 * Dependencies: llist.cpp, llist.h
 * Purpose:      test and implement a singularly linked list
 --------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
using namespace std;

#include "llist.h"

/*
 * Purpose: test linked list functions
 * @param const string& test_file - name of file with commands to use for test
 * @param: int test_n - test number
 */
void testLLCommands(const string& test_file, int test_n) { 

	llist A;             // linkec list to test on
	string command;      // command for function to test
	int val, idx, arg;   // argements to command
	
	fstream fin(test_file.data());

	if (!fin) {
		cout << "Error opening file" << endl;
		return;
	}

	cout << "-------------- Test " << test_n << " ---------------" << endl;

	// while there are still commands to be read from file,
	// process commands
	while (fin >> command) {
		// if command is to add to front of LL, read value to insert, 
		// add to front
		if (command == "addFront") {
			fin >> arg;
			A.addFront(arg);
			cout << "Added " << arg << " to front" << endl;
		} 
		// if command is to add to end of LL, read value to insert, add to end
		else if (command == "addRear") {
			fin >> arg;
			A.addRear(arg);
			cout << "Added " << arg << " to rear" << endl;
		} 
		// if command is to delete from front of LL, try to delete from front
		// if no elements in LL, Underflow exception is thrown
		else if (command == "deleteFront") {
			try {
				A.deleteFront(val); // deleted element is stored in "val"
				cout << "Deleted " << val << " from front" << endl;
			} catch (llist::Underflow) {
				cout << "Could not delete from front: Underflow exception" << endl;
			}
		} 
		// if command is to delete from end of LL, try to delete from end
		// if no elements in LL, Underflow exception is thrown
		else if (command == "deleteRear") {
			try {
				A.deleteRear(val); // deleted element is stored in "val"
				cout << "Deleted " << val << " from rear" << endl;
			} catch (llist::Underflow) {
				cout << "Could not delete from rear: Underflow exception" << endl;
			}
		} 
		// if command is to display all elements, display all elements
		else if (command == "displayAll") {
			A.displayAll();
		} 
		// if command is to add an element before a given index, read in index 
        // and value to add 
        // if an invalid index is given, OutOfRange exception is thrown
		// else add element before index
		else if (command == "addBeforeI") {
			fin >> idx >> arg;
			try {
				A.addbeforeIth(idx, arg);
				cout << "Added " << arg << " before index " << idx << endl;
			} catch (llist::OutOfRange) {
				cout << "Could not add before element " << idx 
                     << ": OutOfRange exception" << endl;
			}
		} 
		// if command is to delete an element at a given index, try to delete 
        // element
        // if invalid index is given, OutOfRange exception is thrown
		else if (command == "deleteI") {
			fin >> idx;
			try {
				A.deleteIth(idx, val); // deleted element is stored in "val"
				cout << "Deleted " << val << " at index " << idx << endl;
			} catch (llist::OutOfRange) {
				cout << "Could not delete element " << idx 
                     << ": OutOfRange exception" << endl;
			}
		} 
		// if command is to delete all elements from the end of the list, 
        // delete all from end
		else if (command == "deleteAllFromRear") {
			A.deleteAllFromRear(true);
		} 
		// if command is to check if list is empty, tell user whether it is 
        // empty or not
		else if (command == "isEmpty") {
			bool empty = A.isEmpty();
			if (empty) {
				printf("List is empty\n");
			} else {
				printf("List is not empty\n");
			}
		}
	}
	A.deleteAllFromRear(); // relesae memnory used by linked list
	cout << endl;
	fin.close();
}

int main() {

	int test_n = 1;

	// test files, compile from created_classes folder
	testLLCommands("data/llist/case1.txt", test_n++);    // test case #1
	testLLCommands("data/llist/case2.txt", test_n++);    // test case #2
	testLLCommands("data/llist/case3.txt", test_n++);    // test case #3
	testLLCommands("data/llist/case4.txt", test_n++);    // test case #4	
	testLLCommands("data/llist/case5.txt", test_n++);    // test case #5	

}

