
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 8, 2014
 * Compiler:     g++ 4.7
 * File Type:    header file (llist.h)
 * Purpose:      implement a singularly linked list
 --------------------------------------------------------------------------------*/

#ifndef llist_H
#define llist_H

typedef char el_t;

// create struct Node to use in linked list
struct Node {
    el_t elem;   // elem is the element stored
    Node* next;  // next is the pointer to the next node
    Node();
    Node(el_t _elem);
};

class llist {

public:

    Node* front;    // front pointer 
    Node* rear;     // rear pointer
    int   count;    // counter for the number of elements

    void reverseRecursively(Node* curr);

public:
    
    // exception for when trying to delete element that doesn't exist
    class Underflow{};    
    // exception for when trying to access element that doesn't exist
    class OutOfRange {};
      
    llist ();
    ~llist();

    el_t head();
    el_t back();

    // check if list is empty
    bool isEmpty();
    
    // display all elements in list
    void displayAll();
    
    // add to front
    void addFront(el_t NewNum);

    // add to rear
    llist& addRear(el_t NewNum);
    
    // add before the ith element
    void addbeforeIth(int I, el_t newNum);

    // delete front element
    void deleteFront(el_t& OldNum);
    
    // delete last element
    void deleteRear(el_t& OldNum);
      
    // delete ith element
    void deleteIth(int I, el_t& OldNum);

    // delete all elements in the list from the end
    void deleteAllFromRear(bool verbose=false);

    int size();

    void reverse();
    void recursiveReverse();

};

#endif
