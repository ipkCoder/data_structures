/*
 * Date: December 14, 2014
 * Purpose: test llist reverse method
 */

#include <iostream>
using namespace std;

#include "llist.h"

void testReverse(llist& list) {
	
	list.reverse();
	// list.recursiveReverse();
	list.displayAll();
	
	list.addFront(0);
	list.addRear(4);
	list.displayAll();
}

int main() {
	
	llist list;
	
	list.addRear(2);
	list.addRear(3);
	list.addFront(1);
	list.displayAll();
	// cout << list.head() << endl;
	// cout << list.back() << endl;

	testReverse(list);	
}