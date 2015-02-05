
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 8, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp -o llist
 * File Type:    source file (llist.cpp)
 * Dependencies: llist.h
 * Purpose:      implement a singularly linked list
 --------------------------------------------------------------------------------*/

#ifndef llist_C
#define llist_C

#include <iostream>
using namespace std;

#include "llist.h" 

/*
 * Purpose: Default Node constructor
 */
Node::Node(): elem(0), next(NULL) {}

/*
 * Purpose: Node constructor that initializes new node with a given value
 */
Node::Node(el_t _elem) : elem(_elem), next(NULL) {}

/*
 * Purpose: Default linked list constructor
 */
llist::llist() : front(NULL), rear(NULL), count(0)
{}

el_t llist::head() {
	return front->elem;
}
el_t llist::back() {
	return rear->elem;
}

int llist::size(){
 	return this->count;
 }
/*
 * Purpose: delete all elements left in the linked list
 */
llist::~llist() {
	Node* tmp;
	while (front != NULL) {
		tmp = front;
		// cout << "Delete: " << tmp << endl;
		front = front->next;
		delete tmp;
	}
}

/*
 * Purpose: determine if lihked list is empty
 */
bool llist::isEmpty() {
	return count == 0 ? true : false;
}

/*
 * Purpose: display all elemnts in the linked list
 */
void llist::displayAll() {
		
	// cout << "Display: ";
	if (front == NULL) {
		cout << "[ None ]" << endl;
		return;
	}

	Node* tmp = front;
	while (tmp != NULL) {
		cout << "[ " << tmp->elem << " ] ";
		tmp = tmp->next;
	}
	cout << endl;
}

/*
 * Purpose: add element to front of linked list
 * @param el_t NewNum - element to add to linked list
 */
void llist::addFront(el_t NewNum) {
	
	// if no nodes in list, set front and rear pointers to new node
	if (front == NULL) {
		front = new Node(NewNum);
		rear = front;
	} 
	// else, have new node's next pointer point to front element
	// then set front pointer to new node
	else {
		Node* new_node = new Node(NewNum);
		new_node->next = front;
		front = new_node;
	}
	++count;
}

/*
 * Purpose: add element to end of linked list
 * @param el_t NewNum - element to add to linked list
 */
llist& llist::addRear(el_t NewNum) {
	
	// if list is empty, add to front of list
	if (front == NULL) {
		addFront(NewNum);
	} 
	// else, set rear node's next pointer to point to new node
	// then, update rear pointer to new node
	else {
		rear->next = new Node(NewNum);
		rear = rear->next;
		++count;
	}

	return *this;
}

/*
 * Purpose: delete element from front of linked list
 * @param el_t OldNum - variable to capture element deleted from linked list
 */
void llist::deleteFront(el_t& OldNum) {
	
	// if no elements in linked list, throw Underflow exception since 
	// no elements can be deleted
	if (front == NULL) {
		throw Underflow();
	}
	else {
		OldNum = front->elem;    // store element to be deleted
		Node* tmp = front->next; // set pointer to point to second element, or NULL
		                         // in the case that there is no second element
		delete front;            // delete front element
		front = tmp;             // have front pointer point to second element, 
                                 // or NULL

		if (front == NULL) {     // if, no elements left, set rear to NULL also
			rear = NULL;
		}

		--count; // account for deleted element
	}
}

/*
 * Purpose: delete element from end of linked list
 * @param el_t OldNum - variable to capture element deleted from linked list
 */
void llist::deleteRear(el_t& OldNum) {
	
	if (rear == NULL) {               // no nodes
		throw Underflow();
	}

	if (front->next == NULL) {        // if one node
		deleteFront(OldNum);          // delete from front, no need to rewrite code
	} else {                          // else, more than one node
		Node* tmp = front;
		// while "tmp" pointer is not at node before end node, go to next node
		while (tmp->next != rear) {
			tmp = tmp->next;
		}
		OldNum = rear->elem;         // store element to delete
		delete rear;
		rear = tmp;                  // reasign end pointer
		rear->next = NULL;
		--count;                     // one node was deleted
	}
}

/*
 * Purpose: delete the ith element in the linked list
 * @param el_t OldNum - variable to capture element deleted from linked list
 */
void llist::deleteIth(int idx, el_t& OldNum) {
	
	if (idx < 1 || idx > count) { // check to make sure index is a valid index
		throw OutOfRange();
	}

	// if delete first element, call deleteFront to check if there is an element 
	// in the list, and if there is, delete first element
	if (idx == 1) {              
		deleteFront(OldNum);
	} 
	// else if delete last element, call deleteRear to check if there is an 
	// element in the list, and if there is, delete last element
	else if (idx == count) {
		deleteRear(OldNum);
	} else {
		Node* before_ith = front;
		// loop through list until pointing to element before ith element
		for (int i = 1; i < (idx-1); ++i) { 
			before_ith = before_ith->next;
		}
		Node* ith = before_ith->next; // point to ith element, in order to delete
		OldNum = ith->elem;
		before_ith->next = ith->next; // have the before_ith's next pointer point
		                              // to the element after the ith element
		delete ith;
		--count;                      // one less element in list
	}
}

/*
 * Purpose: add a new element before the ith element
 * @param el_t NewNum - element to add to the linked list
 */
void llist::addbeforeIth(int I, el_t NewNum) {

	if (I < 1 || I > count+1) { // make sure index is a valid index
		throw OutOfRange();
	}

	// if add before first element, call addFront to add new element 
	// before the first element if it exists
	if (I == 1) {
		addFront(NewNum);
	} 
	// if index is one passed the last element's index, add to end of list
	else if (I == count+1) {
		addRear(NewNum);
	} 
	// else, figure out how to insert in middle of list
	else {
		Node* before_ith = front;
		// loop through list until pointing to element before ith element
		for (int i = 1; i < (I-1); ++i) {
			before_ith = before_ith->next;
		}
		Node* new_node = new Node(NewNum); 
		new_node->next = before_ith->next; // point the new element's next 
		                                   // pointer to the ith element
		before_ith->next = new_node;       // point the before_ith's next 
		                                   // pointer to the new element
		++count; // list increased by one
	}
}

/*
 * Purpose: delete all elements in linked list from the rear
 *          print results
 * @param bool verbose - tell whether to output deleted elements
 */
void llist::deleteAllFromRear(bool verbose /* =false */) {
	el_t OldNum; 
	while (front != NULL) {	
		deleteRear(OldNum);
		if (verbose) {
			cout << "Deleted " << OldNum << ". " << count << " left" << endl;
		}
	} 
}

/*
 * Date: December 14, 2014
 * Purpose: Reverse linked-list in one pass
 */
// void llist::reverse() {
	
// 	if (front != NULL) {
// 		rear = front;                // rear will now be at front
// 		Node* reverse_front = front; // front of list that has been reversed
// 		// Node* tmp = front->next;     // tmp starts ahead of front
// 		reverse_front->next = NULL;  // last element in reversed list
// 		                             // last next is NULL
		
// 		// cout << "Start with:" << endl;
// 		// cout << ".. rear is now " << rear->elem << endl;
// 		// cout << ".. reverse front is " << reverse_front->elem << endl;
// 		// cout << ".. tmp is " << tmp->elem << endl;
// 		// cout << "start reverse:" << endl;

// 		while (tmp != NULL) { // while list hasn't been reveresed all the way
// 			front = tmp; // move front forward
// 			// cout << ".. front is now " << front->elem << endl;
// 			tmp = front->next; // move tmp forward
// 			// cout << ".. tmp moved forward" << endl;
// 			// if (tmp != NULL) {
// 				// cout << ".... tmp is now " << tmp->elem << endl;
// 			// } else {
// 				// cout << ".... tmp is now NULL" << endl;
// 			// }
// 			front->next = reverse_front; // point backwards
// 			// cout << ".. front->next now points backwards" << endl;
// 			// cout << ".... front->next = " << front->next->elem << endl;
// 			reverse_front = front; // one more node has been reversed
// 			// cout << ".. reverse front is moved forward" << endl;
// 			// cout << ".... reverse_front->elem =" << reverse_front->elem << endl;
// 		}
// 	}
// }

void llist::reverse() {
	
	if (front != NULL) {
		rear = front;                // rear will now be at front
		Node* reverse_front = front; // front of list that has been reversed
		front = front->next;
		reverse_front->next = NULL;  // last element in reversed list
		                             // last next is NULL
		cout << "Start with:" << endl;
		cout << ".. front is " << front->elem << endl;
		cout << ".. rear is now " << rear->elem << endl;
		cout << ".. reverse front is " << reverse_front->elem << endl;
		cout << "start reverse:" << endl;

		while (front != NULL) { // while list hasn't been reveresed all the way
			// cout << ".. tmp moved forward" << endl;
			if (front != NULL) {
				cout << ".... front is now " << front->elem << endl;
			} else {
				cout << ".... front is now NULL" << endl;
			}
			front->next = reverse_front; // point backwards
			cout << ".. front->next now points backwards" << endl;
			cout << ".... front->next = " << front->next->elem << endl;
			reverse_front = front; // one more node has been reversed
			cout << ".. reverse front is moved forward" << endl;
			cout << ".... reverse_front->elem =" << reverse_front->elem << endl;
		}
	}
}

void llist::recursiveReverse() {
	reverseRecursively(front);
}

void llist::reverseRecursively(Node* curr) {

	if (curr->next == NULL) { // stop at last
		this->front = curr; // set front of linked-list to end node
		return;
	}

	reverseRecursively(curr->next); // reverse the rest of linked-list first
	curr->next->next = curr; // set next node's next pointer to current node (point behind)
	curr->next = NULL;       // make sure last (curr) next is null
	this->rear = curr;       // remember last node
}

#endif



