
/*================================================================================

HW1P1 - stack
Name:      Ian Kane
Date:      Sept. 10, 2014
Compiler:  g++ 4.7 
File type: header file stack.h

================================================================================*/

const int MAX = 10;   // The MAX number of elements for the stack
                      // MAX is unknown to the client

typedef char el_t;     // the el_t type is "int" for now
                      // el_t is unknown to the client

class stack { 

    private: // to be hidden from the client

        el_t   el[MAX];       // el is an array of el_t's (defined above)
        int    top;           // top is index to the top of stack

    public: // prototypes to be used by the client

        // exception handling classes  
        class Overflow{};
        class Underflow{};

      	stack();   // constructor
      	~stack();  // destructor  

        // HOW TO CALL: pass the element to be pushed
        // PURPOSE: if not full, enters an element at the top;
        //          otherwise throws an exception - Overflow
        void push(el_t);

        // HOW TO CALL: provide variable to receive the popped element
        // PURPOSE: if not empty, removes and gives back the top element;
        //          otherwise throws an exception - Underflow
        void pop(el_t&);

        // HOW TO CALL: pass the element to hold the value of the 
        //              stack's top element 
        // PURPOSE: if stack is not empty, gives the top element 
        //          without removing it, otherwise, throws an Underflow
        //          exception
        void topElem(el_t&);

        /*
         * Purpose: return a boolean indicating whether the stack is empty
         *          (i.e., there are no elements in the stack)
         */
      	bool isEmpty();
        /*
         * Purpose: return a boolean indicating whether the stack is full 
         *          (i.e., can't add any more elements to stack) 
         */
      	bool isFull();
        /*
         * Purpose: print all elements in the stack
         */
        void displayAll();
        /*
         * Purpose: erase all elements in the stack
         */
        void clearIt();      
};
