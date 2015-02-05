
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         November 10, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp slist.cpp dgraph.cpp main.cpp -o main
 * File Type:    source file (dgraph.cpp)
 * Purpose:      implement a directed graph using adjacency table
 --------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
using namespace std;

#include "dgraph.h";

/*
 * Purpose: graph vertex constructor
 * Inialization List: 
 *     name (char)      - vertex name
 *     out_degree (int) - number of adjacent verticies
 *     visit (int)      - mark if visited
 */
Gvertex::Gvertex(): name(' '), out_degree(0), visit(0) {}

/*
 * Purpose: graph constructor
 * Inialization List: 
 *     count (int) - number of verticies in graph
 */
dgraph::dgraph(): count(0) {}

/*
 * Purpose: graph constructor
 * Note: slist used in adjacency_table is automatically called
 */
dgraph::~dgraph() {} 

/*
 * Purpose: import graph into adjacency table
 * @param const string& file - file name storing graph
 */
void dgraph::fillTable(const string& file) {
	
	fstream fin(file.data()); // file containing graph to import

	if (!fin) {
		cout << "Error loading file." << endl;
		return;
	}

	// cout << "--------- Loading in graph ---------" << endl;

	char name; // name of a vertex

	while (fin >> name) { // while vertex to add to graph

		// add new vertex to table
		adjacency_table[count].name = name;

		// cout << "New vertex " << count << ": " << name << endl;
		
		// how many adjacent verticies?
		fin >> adjacency_table[count].out_degree;
		
		// cout << ".. Reading in " << adjacency_table[count].out_degree << " verticies" << endl;
		
		// for each adj vertex, add vertex name to list of adj verticies
		for (int i = 0; i < adjacency_table[count].out_degree; ++i) {
			fin >> name;
			adjacency_table[count].adjacent_vertex.addRear(name);
			// cout << ".... adj vetex ";
			// cout << adjacency_table[count].adjacent_vertex.back() << endl;
		}
		++count; // point to next available vertex position in table array

		if (count == SIZE) {
			cout << "Cannot add more vertices. Adjacency table is full." << endl;
			cout << "Last inserted vertex: " << name << endl;
			break;
		}
	}
	cout << "Finished loading graph." << endl;
	fin.close();
}

/*
 * Purpose: - display verticies in graph (in order they were entered)
 *          - each vertex's name, number of adjacents, and list names of adjacents
 */
void dgraph::displayGraph() {
	for (int i = 0; i < count; ++i) {
		cout << "Vertex Name: " << adjacency_table[i].name << endl
		     << "Out Degrees: " << adjacency_table[i].out_degree << endl
		     << "Adjacents: "; adjacency_table[i].adjacent_vertex.displayAll();
		if (isMarked(adjacency_table[i].name)) {
			cout << "Visited #: " << adjacency_table[i].visit << endl; 
		} else {
			cout << "Visited: false" << endl;
		}
		cout << endl;
	}
}

/*
 * Purpose: find and return number of adjacent verticies to a given vertex
 * @param const el_t& v_name - vertex to evaluate
 */
int dgraph::findOutDegree(const el_t& v_name) {
	
	for (int i = 0; i < count; ++i) { // for each vertex in graph
		if (adjacency_table[i].name == v_name) {
			return adjacency_table[i].out_degree; // adcjacent count
		}
	}
	return -1;
}

/*
 * Purpose: return list of adjacent vertex names
 * @param: const el_t& v_name - name of vertex to find adjacent vertices from
 */
slist dgraph::findAdjacency(const el_t& v_name) {
	for (int i = 0; i < count; ++i) {
		if (adjacency_table[i].name == v_name) {
			return adjacency_table[i].adjacent_vertex;
		}
	}
	return slist(); // empty list if vertex name not in graph
}

bool dgraph::visit(const char& v_name, int n) {
	for (int i = 0; i < count; ++i) {
		if (adjacency_table[i].name == v_name) {
			adjacency_table[i].visit = n;
			return true;
		}
	}
	return false;
}

bool dgraph::isMarked(const char& v_name) {
	for (int i = 0; i < count; ++i) {
		if (adjacency_table[i].name == v_name) {
			if (adjacency_table[i].visit != 0) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false; // not in table
}

