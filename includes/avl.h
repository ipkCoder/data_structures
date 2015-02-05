
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 24, 2014
 * Updated:      Dec 10, 2014
 * Compiler:     g++ 4.7
 * File Type:    header file (bintree.h)
 * Purpose:      implement binary search tree
 --------------------------------------------------------------------------------*/
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <cstdlib> // abs()
#include <cmath>   // pow()
#include <cassert>
#include <queue>   // queue
#include <iomanip> // setw
using namespace std;

template<typename T>
class Vertex {
public:
	T elem;
	int height;
	Vertex<T>* left;
	Vertex<T>* right;
public:
	Vertex(const T&);
};   

template<typename T>
class AVL {

public:
	
	AVL();
	~AVL();  // destructor calls dtraverse to destroy the dynamic tree

	// get root's value
	T getRoot();

	/**
	 * Purpose: display elements using in-order traversal from the root
	 */
	void showInOrder();      

	/**
	 * Purpose: display elements using pre-order traversal from the root
	 * Note: same as Depth First Traversal
	 */
	void showPreOrder();

	/**
	 * Purpose: insert new element into tree
	 * @param: const T& - element to be inserted
	 */
	void insert(const T& elem);
	bool remove(const T& key);
	/**
	 * Purpose: deletes the vertex that has E as it's element.
	 * @param: const T& - element to be removed
	 * @return: true if E was found and deleted, else false
	 * Note: calls remove and findmax (see below)
	 */
	// bool delete(const T& elem);

protected: // utility functions follow - these are not for the clients to use
	// These were created to implement the public methods

	/**
	 * Purpose: recursively perform pre-order traversal starting from given tree vertex
	 * @param: Vertex* V - vertex to begin traversing from
	 */
	void PREorderTraversal(Vertex<T>* V);

	/**
	 * Purpose: recursively perform in-order traversal starting from given tree vertex
	 * @param: Vertex* V - vertex to begin traversing from
	 */
	void INorderTraversal(Vertex<T>* V);

	/**
	 * Purpose: delete all vertices in the tree, traverse in post-order
	 * @param: Vertex* V - pointer to root vertex of the tree to destroy
	 */
	void dtraverse(Vertex<T>* V);

	/**
	 * Purpose: removes vertex from tree
	 * @param: Vertex* V - pointer to vertex to be deleted
	 * @param: Vertex* P - pointer to V's parent
	 */
	// void remove(Vertex<T>* V, Vertex<T>* P);

	void recursiveInsert(Vertex<T>*& head, const T& elem);

	// AVL TREE
	void rotateRight(Vertex<T>*&);
	void rotateLeft(Vertex<T>*&);
	int getHeight(const Vertex<T>*);
	void updateHeight(Vertex<T>*&);
	int getBalance(const Vertex<T>*);
	void balance(Vertex<T>*&);
	bool removeVertex(Vertex<T>*&, const T& key);
	T deleteRightMost(Vertex<T>*&);

private:
	Vertex<T>* root;  // pointer to the root vertex
	int _count;
};

template <typename T>
Vertex<T>::Vertex(const T& E) : left(NULL), right(NULL), elem(E), height(0) {}

/**
 * Purpose: default constructor
 */
template<typename T>
AVL<T>::AVL() {
	root = NULL;   // This is an empty tree
	_count = 0;
}

/**
 * Purpose: destructor, delete all heap memory used
 */
template<typename T>
AVL<T>::~AVL() {
	dtraverse(root); // traverse to delete all vertices in post order
	root = NULL;     // make sure root is NULL  
}

/**
 * Purpose: delete all vertices in the tree, traverse in post-order
 * @param: Vertex* V - pointer to root vertex of the tree to destroy
 */
template<typename T>
void AVL<T>::dtraverse(Vertex<T>* V) {
	if (V != NULL) {
		dtraverse(V->left);        // visit left sub tree of V
		dtraverse(V->right);       // visit right sub tree of V
		delete V;                  // delete V
	}
}

template <typename T>
void AVL<T>::insert(const T& elem) {
	cout << "Inserting " << elem << endl;
	recursiveInsert(root, elem);
}

template <typename T>
void AVL<T>::recursiveInsert(Vertex<T>*& head, const T& elem) {
	
	if (head == NULL) {
		cout << ".. Inserted " << elem << endl;
		head = new typename Vertex<T>::Vertex(elem);
	} else if (elem < head->elem) {
		cout << ".. Going left of " << head->elem << endl;
		recursiveInsert(head->left, elem);
	} else {
		cout << ".. Going right of " << head->elem << endl;
		recursiveInsert(head->right, elem);
	}

	cout << "Height of " << head->elem << " was " << head->height << endl;
	updateHeight(head);
	cout << "Height of " << head->elem << " is now " << head->height << endl;

	balance(head); // check if needs to be balanced out
	showPreOrder();
}

template <typename T>
bool AVL<T>::remove(const T& key) {
	return removeVertex(root, key);
}

template <typename T>
bool AVL<T>::removeVertex(Vertex<T>*& V, const T& key) {
	
	if (V == NULL) {
		return false;
	}

	if (key < V->elem) {
		removeVertex(V->left, key);
	} else if (key > V->elem) {
		removeVertex(V->right, key);
	} else if (V->elem == key) {
		cout << ".. found " << V->elem;
		if (V->left == NULL && V->right == NULL) {
			cout << " with no children" << endl;
			cout << ".. deleting " << V->elem << endl;
			delete V;
			V = NULL;
		} else if (V->left != NULL && V->right == NULL) {
			cout << " with left child" << endl;
			cout << ".. deleting " << V->elem << endl;
			Vertex<T>* temp = V;
			V = temp->left;
			delete temp;
		} else if (V->left == NULL && V->right != NULL) {
			cout << " with right child" << endl;
			cout << ".. deleting " << V->elem << endl;
			Vertex<T>* temp = V;
			V = temp->right;
			delete temp;
		} else {
			cout << " with two children" << endl;
			cout << ".. deleting " << V->elem << endl;
			cout << ".... finding largest of left sub-tree" << endl;
			V->elem = deleteRightMost(V->left);
		}
		updateHeight(V);
		return true;
	}
	return false;
}

template <typename T>
T AVL<T>::deleteRightMost(Vertex<T>*& head) {
	
	assert(head != NULL);

	if (head->right == NULL) {
		cout << "...... largest is " << head->elem << endl;
		cout << "........ deleting " << head->elem << endl;
		T val = head->elem;
		delete head;
		head = NULL;
		return val;
	} else {
		cout << "...... going right" << endl;
		T val = deleteRightMost(head->right);
		cout << "........ sending " << val << " up" << endl;
		cout << "........ Height of " << head->elem << " was " << head->height << endl;
		updateHeight(head);
		cout << "........ Height of " << head->elem << " is now " << head->height << endl;
		return val;
	}
}

template <typename T>
void AVL<T>::balance(Vertex<T>*& head) {
	if (getBalance(head) == 2) {
		// cout << head->elem << " balance factor is 2" << endl;
		if (getBalance(head->right) == -1) { 
			// cout << "Right rotate right elem " << head->right->elem << endl;
			rotateRight(head->right);	
		}
		// cout << "Left rotate current elem " << head->elem << endl;
		rotateLeft(head);
	} else if (getBalance(head) == -2) {
		// cout << head->elem << " balance factor is -2" << endl;
		if (getBalance(head->left) == 1) {
			// cout << "Left rotate left elem " << head->left->elem << endl;
			rotateLeft(head->left);
		}
		// cout << "Right rotate current elem " << head->elem << endl;
		rotateRight(head);
	}
}

template <typename T>
void AVL<T>::rotateLeft(Vertex<T>*& head) {
	Vertex<T>* pivot = head->right;
	cout << ".. pivot set to right elem " << pivot->elem << endl;
	head->right = pivot->left;
	if (head->right != NULL) {
		cout << ".. head->right set to pivot->left elem " << pivot->left->elem << endl;
	} else {
		cout << ".. head->right set to pivot->left elem NULL" << endl;
	}
	pivot->left = head;
	cout << ".. pivot->left is now " << head->elem << endl;
	head = pivot;
	cout << ".. head set to pivot elem " << pivot->elem << endl;
	cout << ".. Height of " << head->left->elem << " was " << head->left->height << endl;
	updateHeight(head->left);
	cout << ".. Height of " << head->left->elem << " is now " << head->left->height << endl;
}

template <typename T>
void AVL<T>::rotateRight(Vertex<T>*& head) {
	Vertex<T>* pivot = head->left;
	cout << ".. pivot set to right elem " << pivot->elem << endl;
	head->left = pivot->right;
	if (head->left != NULL) {
		cout << ".. head->left set to pivot->right elem " << pivot->right->elem << endl;
	} else {
		cout << ".. head->right set to pivot->left elem NULL" << endl;
	}
	pivot->right = head;
	cout << ".. pivot->right is now " << head->elem << endl;
	head = pivot;
	cout << ".. head set to pivot elem " << pivot->elem << endl;
	cout << ".. Height of " << head->right->elem << " was " << head->right->height << endl;
	updateHeight(head->right);
	cout << ".. Height of " << head->right->elem << " is now " << head->right->height << endl;
}

template <typename T>
void AVL<T>::updateHeight(Vertex<T>*& head) {
	if (head != NULL) {
		if (getHeight(head->left) > getHeight(head->right)) {
			head->height = getHeight(head->left) + 1;
		} else {
			head->height = getHeight(head->right) + 1;
		}
	}
}

template <typename T>
int AVL<T>::getHeight(const Vertex<T>* head) {
	return head == NULL ? -1 : head->height;
}

template <typename T>
int AVL<T>::getBalance(const Vertex<T>* V) {
	return getHeight(V->right) - getHeight(V->left);
}

/**
 * Purpose: display elements using in-order traversal from the root
 */
template<typename T>
void AVL<T>::showInOrder() {
	cout << "elements in the IN order: " << endl;
	INorderTraversal(root);  // start in-order traversal from the root
	cout << endl;
}

/**
 * Purpose: recursively perform in-order traversal starting from given tree vertex
 * @param: Vertex* V - vertex to begin traversing from
 */
template<typename T>
void AVL<T>::INorderTraversal(Vertex<T>* V) {
	if (V != NULL) {
		INorderTraversal(V->left);
		cout << V->elem << "(" << V->height << ") ";
		INorderTraversal(V->right);
	}
}

/**
 * Purpose: display elements using pre-order traversal from the root
 * Note: same as Depth First Traversal
 */
template<typename T>
void AVL<T>::showPreOrder() {
	cout << "elements in the PRE order:" << endl;
	PREorderTraversal(root);  // start pre-order traversal from the root
	cout << endl;
}

/**
 * Purpose: recursively perform pre-order traversal starting from given tree vertex
 * @param: Vertex* V - vertex to begin traversing from
 */
template<typename T>
void AVL<T>::PREorderTraversal(Vertex<T>* V) {
	if (V != NULL) {
		cout << V->elem << " "; 
		PREorderTraversal(V->left);
		PREorderTraversal(V->right);
	}
}

#endif

