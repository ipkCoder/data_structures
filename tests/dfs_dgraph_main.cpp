
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         November 21, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ stack.cpp llist.cpp slist.cpp dgraph.cpp dfs_graph.cpp -o main
 * File Type:    source file (dfs_graph.cpp)
 * Purpose:      perform depth first search (DFS) on a graph
 --------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

#include "dgraph.h";
#include "slist.h";
#include "stack.h";
#include "queue.h";


void graphDFS(dgraph& graph) {
	
	slist adj;
	stack stack;
	int visit_num = 1; // visit number

	cout << "============= DFS =============" << endl;
	graph.visit('A', visit_num++); // visit starting vertex
	cout << "Visited A" << endl;
	adj = graph.findAdjacency('A');

	char x; // visiting vertex
	
	while (!adj.isEmpty()) { // push adjacent verticies onto stack
		adj.deleteFront(x);
		stack.push(x);
		cout << "Added " << x << " to stack" << endl;
	}

	while (!stack.isEmpty()) { // not finished printing graph
		stack.pop(x); // get the next vertex to print
		cout << "\nPopped " << x << " from stack" << endl;
		if (!graph.isMarked(x)) { // if haven't visited before
			graph.visit(x, visit_num++); // visit
			cout << "Visited " << x << endl;
			adj = graph.findAdjacency(x);
			while (!adj.isEmpty()) { // put all adjacent verticies on stack
				adj.deleteFront(x);
				stack.push(x);
				cout << "Added " << x << " to stack" << endl;
			}
		} else {
			cout << "Already visited " << x << endl;
		}
		cout << "====== Still on Stack ======" << endl;
		stack.displayAll();
	}
	cout << "\n============ Graph ============" << endl;
	graph.displayGraph();
}

// added on December 19, 2014
// just swap out stack for a queue <--
void graphBFS(dgraph& graph) {
	
	slist adj;
	queue q;
	int visit_num = 1; // visit number

	cout << "============= BFS =============" << endl;
	graph.visit('A', visit_num++); // visit starting vertex
	cout << "Visited A" << endl;
	adj = graph.findAdjacency('A');

	char x; // visiting vertex
	
	while (!adj.isEmpty()) { // push adjacent verticies onto stack
		adj.deleteFront(x);
		q.add(x);
		cout << "Added " << x << " to stack" << endl;
	}

	while (!q.isEmpty()) { // not finished printing graph
		q.remove(x); // get the next vertex to print
		cout << "\nPopped " << x << " from stack" << endl;
		if (!graph.isMarked(x)) { // if haven't visited before
			graph.visit(x, visit_num++); // visit
			cout << "Visited " << x << endl;
			adj = graph.findAdjacency(x);
			while (!adj.isEmpty()) { // put all adjacent verticies on stack
				adj.deleteFront(x);
				q.add(x);
				cout << "Added " << x << " to stack" << endl;
			}
		} else {
			cout << "Already visited " << x << endl;
		}
		cout << "====== Still on Stack ======" << endl;
		q.displayAll();
	}
	cout << "\n============ Graph ============" << endl;
	graph.displayGraph();
}

int main() {
	
	dgraph graph;

	graph.fillTable("data/graph/table.txt");
	cout << "============ Graph ============" << endl;
	graph.displayGraph();
	
	graphDFS(graph);
	graphBFS(graph);

}
