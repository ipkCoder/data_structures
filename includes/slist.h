
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 18, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ slist.cpp -o slist
 * File Type:    header file (slist.h)
 * Purpose:      extend singularly linked list (search, replace, copy, =, ==)
 --------------------------------------------------------------------------------*/
#ifndef slist_H
#define slist_H

#include <iostream>
using namespace std;

#include "llist.h" // regular linked list to inherit

class slist: public llist {

public: 

	slist();
	slist(const slist& source);
	// no need to initialize destructor, llist's destructor will be called
	
	// search for given element, return element's position in list 
	// if element was not found, return 0
	int search(const el_t& key);
	
	// replace the element at index "idx" with element "elem"
	// if "idx" is not a valid index, throws OutOfRange exception
	void replace(int idx, const el_t& elem);

	// deep copy contents of "source" slist to "this" slist
	slist& operator=(const slist& source);
	
	// compare "other" slist to "this" slist 
	bool operator==(const slist& other);

	// delete all elements in "this" list
	void destroy();

protected:

	// deep copy "source" list into "this" list
	void copy(const slist& source);
};

#endif
