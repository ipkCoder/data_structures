
/*
 * Ian Kane
 * Dec 10, 2014
 * test creating BST from sorted array
 * test containing sub-tree
 */

#include <iostream>
using namespace std;

#include "bst.h"

int main() {

	int list[12] = {1,2,3,4,5,6,7,8,9,10,11,12}; // ordered
	int list2[2] = {1, 12}; // ordered
	int list3[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	
	// create BST from array
	BST<int>* bst1 = BST<int>::createBST(list, 12);
	BST<int>* bst2 = BST<int>::createBST(list2, 2);
	BST<int>* bst3 = BST<int>::createBST(list3, 12);
	// bst->ShowInOrder();

	if (bst1->containsSubTree(bst2)) {
		cout << "BST2 is a sub-tree of BST1" << endl;
	} else {
		cout << "BST2 is not a sub-tree of BST1" << endl;
	}

	if (bst1->containsSubTree(bst3)) {
		cout << "BST3 is a sub-tree of BST1" << endl;
	} else {
		cout << "BST3 is not a sub-tree of BST1" << endl;
	}
}