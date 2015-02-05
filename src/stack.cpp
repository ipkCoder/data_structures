
/*================================================================================

HW1P1 - stack
Name:      Ian Kane
Date:      Sept. 10, 2014
Complier:  g++ 4.7
File type: stack class implementation (stack.cpp)

================================================================================*/

#include <iostream>
using namespace std;

#include "stack.h"

/*
 * Purpose: stack default constructor
 */
stack::stack() {
    // initialize top to be -1, indicating stack starts empty.
    top = -1; 
}

/*
 * Purpose: set stack default constructor
 */
stack::~stack() {
    // Stack destructor does not have to do anything since this 
    // is a static array.
}
  
/*
 * Purpose of function: - checks to see if stack is empty
 *                      - returns true if empty, false otherwise.
 */
bool stack::isEmpty() { 
    // if stack is empty (i.e., top does not indicate valid 
    // position), return true, else, return false
    if (top == -1) {
        return true; 
    }
    else { 
        return false;
    }
}
    
/*
 * Purpose of function - checks to see if stack is full 
 *                     - returns true if full, false otherwise.
 */
bool stack::isFull() { 
    // if top is at last element (i.e., stack is full), 
    // return true, else, return false
    if (top == MAX-1) {
        return true; 
    }
    else { 
        return false;
    }
}

/*
 * Purpose - add element to top of stack
 *
 * @param: el_t elem - element to add to top of stack
 */
void stack::push(el_t elem) {
    
    // if stack is full, throw Overflow exception
    // else, add element to top of stack
    if (isFull()) {
        throw Overflow();
    } 
    else {
        ++top;          // first increase top to to next position
        el[top] = elem;
    }
}

/*
 * Purpose: - remove top element from stack
 * 
 * @param: el_t& elem - reference to variable with which to 
 *                     hold stack's (removed) top element
 */
void stack::pop(el_t& elem) {
    
    // call isEmpty function
    // if stack is empty, throw Underflow exception
    // else, set elem value to top of stack
    if (isEmpty()) {
        throw Underflow();                       
    }
    else {
        elem = el[top];
        --top; // decrement "top" so "top" will index top of stack
    }
}

/*
 * Purpose: get top element from stack
 *
 * @param: el_t& elem - variable to hold value of top element in stack
 */
void stack::topElem(el_t& elem) {

    // Check to see if stack is empty before returning top element's 
    // value. If stack is empty, throw Underflow exception,
    // else, set parameter "elem" to value of top element in stack
    if (isEmpty()) {
        throw Underflow();
    }
    else {
        elem = el[top];
    }
}

/*
 * Purpose: vertically print all elements in stack from top to bottom 
 */
void stack::displayAll() {
    // before printing stack, check to see if stack is empty
    // if stack is empty, notify client
    // else, print stack
    if (isEmpty()) {
        cout << "[ empty ]" << endl;
    }
    else {
        // print all elements from top top to bottom
        for (int i=top; i>=0; i--) {
            cout << el[i] << endl; 
        }
    }
}

/*
 * Purpose: clear all elements from stack
 */
void stack::clearIt() {
    // for each element in stack, pop it from top
    el_t x;
    while (!isEmpty()) {
        pop(x);
    }
}

