
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 11, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp slist.cpp search_list_main -o main
 * File Type:    source file (llist.cpp)
 * Dependencies: llist.cpp llist.h
 *               slist.cpp slist.h
 * Purpose:      implement a singularly linked list
 --------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
using namespace std;

#include "slist.h"

/*
 * Purpose: test linked list functions
 * @param const string& test_file - name of file with commands to use for test
 * @param: int test_n - test number
 */
void testLLCommands(const string& test_file, int test_n) { 

	slist A;             // linkec list to test on
	string command;      // command for function to test
	int val, idx, arg;   // argements to command
	
	fstream fin(test_file.data());

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
		// if command is to delete from front of list, try to delete from front
		// if no elements in LL, Underflow exception is thrown
		else if (command == "deleteFront") {
			try {
				A.deleteFront(val); // deleted element is stored in "val"
				cout << "Deleted " << val << " from front" << endl;
			} catch (slist::Underflow) {
				cout << "Could not delete from front: Underflow exception" << endl;
			}
		} 
		// if command is to delete from end of list, try to delete from end
		// if no elements in LL, Underflow exception is thrown
		else if (command == "deleteRear") {
			try {
				A.deleteRear(val); // deleted element is stored in "val"
				cout << "Deleted " << val << " from rear" << endl;
			} catch (slist::Underflow) {
				cout << "Could not delete from rear: Underflow exception" << endl;
			}
		} 
		// if command is to display all elements, display all elements
		else if (command == "displayAll") {
			A.displayAll();
		} 
		// if command is to add an element before a given index, read in index 
		// and value to add
		// if invalid index is given, OutOfRange exception is thrown
		// else add element before index
		else if (command == "addBeforeI") {
			fin >> idx >> arg;
			try {
				A.addbeforeIth(idx, arg);
				cout << "Added " << arg << " before index " << idx << endl;
			} catch (slist::OutOfRange) {
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
			} catch (slist::OutOfRange) {
				cout << "Could not delete element " << idx 
				     << ": OutOfRange exception" << endl;
			}
		} 
		// if command is to delete all elements from the end of the LL, 
		// delete all from end
		else if (command == "deleteAllFromRear") {
			A.deleteAllFromRear();
		} 
		// if command is to check if LL is empty, tell user whether it is 
		// empty or not
		else if (command == "isEmpty") {
			bool empty = A.isEmpty();
			if (empty) {
				printf("List is empty\n");
			} else {
				printf("List is not empty\n");
			}
		} 
		// search for element "arg" in list, report position index
		// if "arg" is not found, index will be 0 
		else if (command == "search") {
			fin >> arg; // get element to search for
			idx = A.search(arg);
			if (idx != 0) { // if element was found
				cout << "found " << arg << " at position " << idx << endl;
			} else {
				cout << arg << " was not found" << endl;
			}
		} 
		// replace a given index "idx with element "arg"
		// if invalid index, exception is thrown
		else if (command == "replace") {
			fin >> idx >> arg; // get index and element to replace with
			try {
				A.replace(idx, arg);
				cout << "replaced position " << idx << " with " << arg << endl;
			} catch (slist::OutOfRange) {
				cout << "Could not replace position " << idx 
				     << ": OutOfRange exception" << endl;
			}
		} 
		// search and replace at the same time
		else if (command == "searchAndReplace") {
			fin >> arg; // get element to search for
			idx = A.search(arg);
			if (idx != 0) { // if element was found
				try {
					cout << "found " << arg << " at position " << idx;
					fin >> arg; // get element to replace found element with
					A.replace(idx, arg);
					cout << ". replaced position " << idx << " with " << arg << endl;
				} catch (slist::OutOfRange) {
					cout << "Could not replace position " << idx 
					     << ": OutOfRange exception" << endl;
				}
			} else {
				cout << "Could not replace " << arg << ". " << arg 
				     << " was not found" << endl;
			}
		}
	}

	A.deleteAllFromRear(); // release memory used by linked list
	cout << endl;
	fin.close();
}

int main() {

	int test_n = 1;

	testLLCommands("data/slist/slist_case1.txt", test_n++);
}

