
/*================================================================================

HW1P1 - queue client
Name:           Ian Kane
Date:           Sept. 10, 2014
Complier:       g++ 4.7
How to compile: g++ queue.cpp client2.cpp -o client2
File type:      client file
Purpose:        generate all string combinations of input chars/strings 
                using a queue

Algorithm Design:
	Given a set of N input chars, there are N sets of strings that can be 
	generated from the input set (strings of length 1, 2, …, N). The 
	original input chars will be held in a string array. Strings in the 
	string queue will represent the strings generated in the previous set. 
	For the first set of strings, print the original input chars 
	(strings of length 1). Store these values in the queue. For all other 
	sets of strings (1 < length  <= N), for each string in the queue, add 
	each input char, one at a time, to the end of the string, print, and 
	add to end of queue to use in next round.

	Example:
	Input chars:      A, B, C
	Length 1 strings: A, B, C
	Length 2 strings: A+A (AA), A+B (AB), A+C (AC), B+A (BA), B+B (BB), 
		         B+C (BC), C+A (CA), C+B (CB), C+C (CC)
	Length 3 strings: AA+A (AAA) AA+B (AAB), AA+C (AAC), AB+A (ABA), 
	                  AB+B (ABB), AB+C (ABC), AC+A (ACA), AC+B (ACB), …  

================================================================================*/

#include <iostream>
using namespace std;

#include "queue.h"

int main() {

	queue myLine;                        // myLine is a new queue object
	string userans, elmtoadd, elmtoget;  // local client variables

	cout << "Enter your choice Q to quit or something else: ";
	cin >> userans;

	// get input from user
	// ask what strings he wants to put in queue
	// continue to ask until user says to stop or queue is full
	while ( (userans != "Q") && (!myLine.isFull()) ) {
        
        cout << "Give me an element to add: ";
	    cin >> elmtoadd;
	    
	    try {
	    	myLine.add(elmtoadd);
        }
        catch(queue::Overflow) {
        	cout << "Cannot add any more entries.\nPlease press Q.";
        }

	    cout << "Enter your choice Q or something else: ";
        cin >> userans;
    }// end of while

    myLine.displayAll();
    
    int i, j, times;
    int n, queueLegth;

    // there are N sets of strings that can be generated from N input chars/strings
   	times = n = myLine.getSize();

   	string s[n]; // hold input strings
   	string x, y; // hold temporary strings
   	x = y = "";

    // move input strings into an array
    for (i = 0; i < n; ++i) {
   		myLine.remove(x);
   		s[i] = x;
    }

    // while there is still strings to be printed
    // find and print new strings
    int count = 0;
    while (count != times) {

    	// if first round of strings, print each input string
    	// else, find and print new strings
    	if (count == 0) {
    		for (i = 0; i < n; ++i) {
    			x = s[i];
    			cout << x << endl;
    			myLine.add(x); // add to queue for later use
    		}
    	}
    	else {
		// find length of queue (# of strings from last round)
    		queueLegth = myLine.getSize();
    		// for each string in last round (which was added to queue)
    		for (j = 0; j < queueLegth; ++j) {
	   		myLine.remove(x);	
	  		// for each original input string
	  		for (i = 0; i < n; ++i) {
	    			// combine strings, print, add to queue for next round
	    			y = s[i];
	    			cout << x + y << endl;
	    			myLine.add(x + y);
	    	    	}
	    	}
    	}
    	++count; // keep track of how many rounds have completed
	}

    // empty queue
    while (!myLine.isEmpty()) {
	myLine.remove(elmtoget); // receive deleted element
    }

}//end of main
