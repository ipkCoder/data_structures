
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 18, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ slist.cpp -o slist
 * File Type:    source file (slist.cpp)
 * Dependencies: slist.h
 * Purpose:      extend singularly linked list
 --------------------------------------------------------------------------------*/

#ifndef slist_C
#define slist_C

#include <iostream>
using namespace std;

#include "slist.h"

/*
 *  Purpose: default constructor, calls llist base constructor
 */
slist::slist() : llist() {}

/*
 * Purpose: search for an element in the linked list
 * @param - const el_t& key - element to search for 
 * @return - index to element (1 - count), else 0
 */
int slist::search(const el_t& key) {
	
	Node* tmp = this->front;
	
	// starting with first element, search for element while 
	// not at the end of the list and element hasn't been found
	int idx = 1;
	while (tmp != NULL && tmp->elem != key) {
		tmp = tmp->next;
		++idx;             // index of next element to check
	}

	// if element was not found, return 0, else return 
	// index of found element
	if (tmp == NULL) { 
		idx = 0;
	} else {
		return idx;
	}
}

/*
 * Purpose: replace element at index "idx" with element "elem"
 * @param: int idx - index of element to replace
 * @oaram: const el_t& elem - constance reference to element to put in list
 */
void slist::replace(int idx, const el_t& elem) {
	
	if (idx < 1 || idx > this->count) {
		throw OutOfRange();
	}

	Node* tmp = this->front;
	for (int i = 1; i < (idx); ++i) {
		tmp = tmp->next;
	}

	tmp->elem = elem;
}

/*
 * Purpose: assign "this" list the value of other list
 * @param: const slist& source - linked list to copy
 */
slist& slist::operator=(const slist& source) {
	
	// if lists are not the same lists
	if (this != &source) {

		this->destroy(); // delete contents of "this" list
		
		// add elements of "source" list to this list
		Node* tmp = source.front;
		while (tmp != NULL) {
			this->addRear(tmp->elem);
			tmp = tmp->next;
		}
	}

	return *this;
}

/*
 * Purpose: create "==" operator for linked list
 * @param: const slist& other - list to compare against
 */ 
bool slist::operator==(const slist& other) {

	// if lengths are not the same, lists are not the same
	if (this->count != other.count) {
		return false;
	}

	bool equal = true;                  // assume lists are the same
	Node* this_current = this->front;
	Node* other_current = other.front;

	// compare all nodes in lists
	// if elements are not the same at same location in both lists, 
	// assign "equal" to false
	while (this_current != NULL) {
		if (this_current->elem != other_current->elem) {
			equal = false;
			break;
		} else {
			this_current = this_current->next;
			other_current = other_current->next;
		}
	}

	return equal;
}

/*
 * Purpose: create copy constructor in order to deep copy list
 * @param: const slist& source - list to copy
 */ 
slist::slist(const slist& source) {
	llist();       // set default values
	copy(source);
} 

/*
 * Purpose: deep copy a list into "this" list
 * @param: const slist& source - list to copy
 */ 
void slist::copy(const slist& source) {

	Node* source_current;
	Node* this_current;

	this->destroy(); // destroy "this" list

	if (source.front != NULL) { // if "source" is not empty
		
		source_current = source.front;

		// "this" front node is same as source's first node
		this->front = new Node(source_current->elem);
		++this->count;

		this_current = this->front;

		// copy all other elements in "source" to "this" list
		while(source_current->next != NULL){
			source_current = source_current->next;
			this_current->next = new Node(source_current->elem);
			++this->count;
			this_current = this_current->next;
		}

		this->rear = this_current; // remember last element
	}
}

/*
 * Purpose: delete all elements in list
 */
void slist::destroy() {
  
	Node* temp;

	// delete from front of list until front pointer is null
	while(front != NULL){
		temp = front;
		front = front->next;
		delete temp;
		--count;
	}
};

#endif
