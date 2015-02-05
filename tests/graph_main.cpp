
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         November 10, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp slist.cpp dgraph.cpp main.cpp -o main
 * File Type:    main source file (dgraph.cpp)
 * Purpose:      test directed graph implemented using adjacency table
 --------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

#include "dgraph.h";
#include "slist.h";

int main() {

	dgraph g;
	
	g.fillTable("data/graph/table.txt");
	cout << "-------- Displaying Graph Info --------" << endl;
	g.displayGraph();

	int out;
	char name;
	// find number of adjacent vertices for a given vertex
	while (true) {
		cout << "--------- Find Out Degree ------------\n" 
		     << "Enter vertex char name (X to Quit loop): ";
		cin >> name;
		if (name == 'X') {
			break;
		} else {
			out = g.findOutDegree(name);
			cout << "Vertex " << name << " out_degree = ";
			if (out != -1) {
			    cout << out << endl;
			} else {
				cout << "none. " << "Vertex " << name << " doesn't exist." << endl;
			}
		}
	}

	slist adj; // temp list

	// find name of adjacent vertices
	while (true) {
		cout << "\n--------- Find Adjacency -------------\n" 
		     << "Enter vertex char name (X to Quit loop): ";
		cin >> name;
		if (name == 'X') {
			break;
		} else {
			adj = g.findAdjacency(name);
			cout << "Vertex " << name << " adjacents: ";
			adj.displayAll();
		}
	}
}
