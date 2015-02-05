
#include <iostream>
using namespace std;

#include "bst.h"
// #include "heap.h"

void insertRecursivelyTest() {
	BST<int> bst;
	for(int i = 1; i <=9 ; i=i+2)   // inserting 1,3,5,7,9 into the tree
		bst.insertRecursively(i);

	for(int i = 10; i >=2 ; i=i-2)     // inserting 10,8,6,4,2 into the tree
		bst.insertRecursively(i);

	bst.ShowInOrder();  // should show in the sorted order
}

void createFromArrayTest() {
	int list[5] = {1,2,3,4,5};
	BST<int> bst = *BST<int>::createBST(list, 5);
	bst.ShowPreOrder();
}

void printHasPath(BST<int>& bst, int key) {
	if (bst.hasPathSum(key)) 
		cout << ".. Has path sum " << key << endl;
	else 
		cout << ".. Does not have path sum of " << key << endl;
}
void pathSumTest() {
	
	// BST<int> bst;
	// cout << "Testing empty tree" << endl;
	// printHasPath(bst,10);
	
	// cout << "Testing tree with one node" << endl;
	// bst.InsertVertex(7);
	// printHasPath(bst, 7);
	// cout << endl;
	// printHasPath(bst, 20);

	int list[7] = {1,3,4,5,6,7,8};
	BST<int> bst = *BST<int>::createBST(list, 7);
	for (int i = 0; i < 40; ++i) {
		printHasPath(bst, i);
		cout << "-----------------------------------" << endl;
	}	
}


int main() {

	// insertRecursivelyTest();
	createFromArrayTest();
	pathSumTest();

	// BST<int> MyTree;  // my first binary search tree
	// // heap_tree<float> MyTree;  // my first binary search tree

	// for(int i = 1; i <=9 ; i=i+2)   // inserting 1,3,5,7,9 into the tree
	// 	MyTree.InsertVertex(i+.9);  // make float

	// for(int i = 10; i >=2 ; i=i-2)     // inserting 10,8,6,4,2 into the tree
	// 	MyTree.InsertVertex(i);

	// MyTree.ShowInOrder();  // should show in the sorted order

	// MyTree.ShowPreOrder(); // should show the parent before children


	// //********************************************************
	// cout << "===  Starting a new tree with 3 nodes ===="<< endl;
	// BST<int> Nums1;  // Nums1 is the second binary search tree

	// Nums1.InsertVertex(1);
	// Nums1.InsertVertex(2);
	// Nums1.InsertVertex(3);
	// Nums1.DeleteVertex(1); // delete the root
	// Nums1.ShowInOrder();

	// //********************************************************
	// cout << "===  Starting a new tree with 3 nodes ===="<< endl;
	// BST<int> Nums2;  // Nums2 is another binary search tree

	// Nums2.InsertVertex(10);
	// Nums2.InsertVertex(9);
	// Nums2.InsertVertex(8);
	// Nums2.DeleteVertex(10);  // delete the root
	// Nums2.ShowInOrder();

	// //**********************************************************
	// cout << "===  Starting a new tree with 7 nodes ===="<< endl;
	// BST<int> Nums;  // Nums is the last binary search tree

	// // creates a shallowest 7 node tree (draw this)
	// Nums.InsertVertex(3);  // root
	// Nums.InsertVertex(1);  // level 1 L
	// Nums.InsertVertex(2);    // level 2 R
	// Nums.InsertVertex(0);    // level 2 L
	// Nums.InsertVertex(5);  // level 1 R
	// Nums.InsertVertex(6);    // level 2 R
	// Nums.InsertVertex(4);    // level 2 L
	// // Nums.InsertVertex(-1);
	// // Nums.InsertVertex(-2);

	// // cout << "height: " << Nums.height() << endl;
	// // if (Nums.balanced()) {
	// //   cout << "tree is balanced" << endl;
	// // } else {
	// //   cout << "tree is not balanced" << endl;
	// // }

	// // Nums.straighten();  // create backbone tree (all nodes are to the right)
	// // // Nums.ShowInOrder();

	// // cout << "height: " << Nums.height() << endl;
	// // if (Nums.balanced() != -1) {
	// //   cout << "tree is balanced" << endl;
	// // } else {
	// //   cout << "tree is not balanced" << endl;
	// // }

	// // // cout << "height: " << Nums.height() << endl;
	// // Nums.balanceBST();
	// // // Nums.ShowInOrder();
	// // cout << "height: " << Nums.height() << endl;

	// // if (Nums.balanced()) {
	// //   cout << "tree is balanced" << endl;
	// // } else {
	// //   cout << "tree is not balanced" << endl;
	// // }

	// // Nums.breadthFirstTraversal();

	// // cout << "height: " << Nums.height() << endl;
	// // if (Nums.balanced() != -1) {
	// //   cout << "tree is balanced" << endl;
	// // } else {
	// //   cout << "tree is not balanced" << endl;
	// // }

	// // //and show the nodes in sorted order
	// // Nums.ShowInOrder();

	// // //and then delete some nodes 

	// // //  - level 2 right most leaf
	// // Nums.DeleteVertex(6);
	// // cout << "height: " << Nums.height() << endl;
	// // // Nums.ShowInOrder();
	// // // - level 1 right mode node with one left child
	// // Nums.DeleteVertex(5);
	// // cout << "height: " << Nums.height() << endl;
	// // // Nums.ShowInOrder();
	// // // - level 0 root with two children
	// // Nums.DeleteVertex(3);
	// // cout << "height: " << Nums.height() << endl;
	// // // - deleting a non-existing one
	// // Nums.DeleteVertex(7);
	// // cout << "height: " << Nums.height() << endl;

	// //and then show the remaining nodes in sorted order
	// // Nums.ShowInOrder();
	// // Nums.heapify();
	// // cout << endl;
	// // Nums.ShowInOrder();

	// // cout << Nums.getRoot() << endl; // min elem

	// Nums.depthFirstSearch(4);
	// cout << "----------" << endl;
	// Nums.ShowPreOrder();
}


