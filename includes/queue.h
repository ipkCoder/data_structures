
/*================================================================================

HW1P1 - queue
Name:      Ian Kane
Date:      Sept. 10, 2014
Compiler:  g++ 4.7 
File type: headher file queue.h

================================================================================*/

typedef char el_t;       // el_t is an alias for the data type

const int MAX_SIZE = 100;  // max number of elements in queue

class queue  {

  protected:
    el_t el[MAX_SIZE]; // el_t array
                       //  Elements will be found between front and rear but
                       // front may be behind rear since the queue wraps around
    
    int  count;        // how many elements do we have right now?
    int  front;        // where the front element of the queue is.
    int  rear;         // where the rear element of the queue is.

  public:    // prototypes to be used by the client

    // add exception classes here
    class Overflow{};
    class Underflow{};
    // constructor 
    queue(); 

    //destructor 
    ~queue();

     // PURPOSE: returns true if queue is empty, otherwise false
     bool isEmpty();

     // PURPOSE: returns true if queue is full, otherwise false
     bool isFull();

     // PURPOSE: if full, throws an exception Overflow
     // if not full, enters an element at the rear 
     // HOW TO CALL: provide the element to be added
     void add(el_t);

     // PURPOSE: if empty, calls an emergency exit routine
     // if not empty, removes the front element to give it back 
     // HOW TO CALL: provide a holder for the element removed (pass by ref)
     void remove(el_t&);

     // PURPOSE: if empty, throws an exception Underflow
     // if not empty, give back the front element (but does not remove it)
     // TO CALL: provide a holder for the element (pass by ref)
     void frontElem(el_t&);

     // PURPOSE: returns the current size to make it 
     // accessible to the client caller
     int getSize();

     // PURPOSE: display everything in the queue from front to rear
     //  enclosed in []
     // if empty, displays [ empty ]
     void displayAll();

     // PURPOSE: if empty, throws an exception Underflow
     //if queue has just 1 element, does nothing
     //if queue has more than 1 element, moves the front one to the rear
     void goToBack();
};           

