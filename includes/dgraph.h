
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         November 10, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp slist.cpp dgraph.cpp main.cpp -o main
 * File Type:    header file (dgraph.h)
 * Purpose:      implement a directed graph using adjacency table
 --------------------------------------------------------------------------------*/

#ifndef dgraph_H
#define dgraph_H

#include "slist.h";

const int SIZE = 20;

// this will be in each GTable slot
struct Gvertex {

	char name;              // the vertex Name
	int out_degree;	        // the Out degree
	slist adjacent_vertex;  // the adjecent vertices in an slist of chars
	int visit;              // This will hold the visit number in HW7

	Gvertex(); 
};

// directed graph
class dgraph {

private:
	
	Gvertex adjacency_table[SIZE];
	int count;             // how many slots of the table are actually used

public:

	dgraph();
	~dgraph();   

	// read from the input file table.txt and fill GTable
	void fillTable(const string& file);

	void displayGraph();  // displays in an easy to read format 

	int findOutDegree(const el_t&);  // returns the out degree of a given vertex

	slist findAdjacency(const el_t&);  // returns the adjacency list of a given vertex

	// mark that a vertex has been visited using the number in which it is visited
	bool visit(const char& v_name, int n);

	// has the vertex v_name been visited?
	bool isMarked(const char& v_name);
};

#endif
