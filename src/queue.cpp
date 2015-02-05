
/*================================================================================

HW1P1 - queue
Name:      Ian Kane
Date:      Sept. 10, 2014
Complier:  g++ 4.7
File type: queue class implementation (queue.cpp)

================================================================================*/

#include <iostream>
using namespace std;

#include "queue.h"

/*
 * Purpose: - default constructor
 *          - initialize data members
 */
queue::queue() {
	front = 0;
	rear = -1;
	count = 0;
}

/*
 * Purpose: set queue default constructor
 */
queue::~queue() {
	// queue destructor does not have to do anything since this is 
	// a static queue array.
}

// PURPOSE: returns true if queue is empty, otherwise false
bool queue::isEmpty() {
	return count == 0 ? true: false;
}

// PURPOSE: returns true if queue is full, otherwise false
bool queue::isFull() {
	return count == MAX_SIZE ? true : false;
}

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear 
// HOW TO CALL: provide the element to be added
void queue::add(el_t e) {
	if (isFull()) {
		throw Overflow();
	}
	else {
		rear = ++rear % MAX_SIZE;
		el[rear] = e;
		++count;
	}
}

// PURPOSE: if empty, calls an emergency exit routine
// if not empty, removes the front element to give it back 
// HOW TO CALL: provide a holder for the element removed (pass by ref)
void queue::remove(el_t& e){
	if (isEmpty()) {
		exit(0);
	}
	else {
		e = el[front];
		front = ++front % MAX_SIZE;
		--count;
	}
}

// PURPOSE: if empty, throws an exception Underflow
   // if not empty, give back the front element (but does not remove it)
   // TO CALL: provide a holder for the element (pass by ref)
void queue::frontElem(el_t& elem) {
	if (isEmpty()) {
		throw Underflow();
	}
	else {
		elem = el[front];
	}	
}

// PURPOSE: returns the current size to make it 
// accessible to the client caller
int queue::getSize(){
	return count;
}

// PURPOSE: display everything in the queue from front to rear
//  enclosed in []
// if empty, displays [ empty ]
void queue::displayAll() {
	int i;
	cout << "[ ";
	for (i = front; i < (front + count); ++i) {
		cout << el[i % MAX_SIZE] << " ";
	}
	cout << "]" << endl;
}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear
void queue::goToBack() {
	if (isEmpty()) {
		throw Underflow();
	}
	else if (count > 1) {
		el_t tmp;
		remove(tmp);
		add(tmp);
	}
}

// =============== Test queue class ================
// int main() {
	
// 	queue q;
	
// 	try {
// 		q.goToBack();
// 	}
// 	catch (queue::Underflow){
// 		cout << "caught goToBack()" << endl;
// 	}

// 	try {
// 		int x;
// 		q.frontElem(x);
// 	}
// 	catch (queue::Underflow){
// 		cout << "caught frontElem()" << endl;
// 	}

// 	cout << "Full: " << q.isFull() << endl;
// 	cout << "Empty: " << q.isEmpty() << endl;
// 	int i;
// 	for (i = 0; i < 10; ++i)
// 		q.add(i);
// 	cout << "Full: " << q.isFull() << endl;
// 	cout << "Empty: " << q.isEmpty() << endl;
	
// 	q.displayAll();
	
// 	//q.goToBack();
// 	//q.displayAll();
	
// 	cout << "size: " << q.getSize() << endl;
	
// 	int front;
// 	q.frontElem(front);
// 	cout << "Front: " << front << endl;
// 	cout << q.front << " " << q.rear << endl;
// 	//q.goToBack();
	
// 	q.remove(front);
// 	cout << "size: : " << q.getSize() << endl;
// 	q.displayAll();

// 	q.frontElem(front);
// 	cout << "Front: " << front << endl;

// 	q.remove(front);
// 	cout << q.front << " " << q.rear << endl;
// 	q.displayAll();

// 	q.add(99);
// 	cout << q.front << " " << q.rear << endl;
// 	q.displayAll();

// 	try {
// 		q.add(78);
// 		q.add(89);
// 	}
// 	catch(queue::Overflow) {
// 		cout << "caught add()" << endl;
// 	}

// 	q.goToBack();
// 	q.displayAll();

// }




