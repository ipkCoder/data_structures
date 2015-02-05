
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 24, 2014
 * Updated:      Dec 10, 2014
 * Compiler:     g++ 4.7
 * File Type:    header file (bintree.h)
 * Purpose:      implement binary search tree
 --------------------------------------------------------------------------------*/
#ifndef bst_H
#define bst_H

#include <iostream>
#include <cstdlib> // abs()
#include <cmath>   // pow()
#include <queue>   // queue
#include <iomanip> // setw
using namespace std;

template<typename T>
class Vertex {
public:
	Vertex<T>* left;
	T elem;
	Vertex<T>* right;
public:
	Vertex(const T&);
};   

template<typename T>
class BST {

public:

	// create BST from sorted array
	static BST<T>* createBST(const T list[], int n);
	static Vertex<T>* createFromArray(const T list[], int min, int max);
	bool subTree(Vertex<T>* main, Vertex<T>* sub_tree);
	bool containsSubTree(BST<T>*&);
	bool hasPathSum(T sum);
	bool bstHasPathSum(Vertex<T>* V, T& path_sum, T& sum);
	
	BST();
	~BST();  // destructor calls dtraverse to destroy the dynamic tree

	// get root's value
	T getRoot();

	/**
	 * Purpose: display elements using in-order traversal from the root
	 */
	void ShowInOrder();      

	/**
	 * Purpose: display elements using pre-order traversal from the root
	 * Note: same as Depth First Traversal
	 */
	void ShowPreOrder();

	/**
	 * Purpose: insert new element into tree
	 * @param: const T& - element to be inserted
	 */
	void InsertVertex(const T&);

	/**
	 * Purpose: deletes the vertex that has E as it's element.
	 * @param: const T& - element to be removed
	 * @return: true if E was found and deleted, else false
	 * Note: calls remove and findmax (see below)
	 */
	bool DeleteVertex(const T&);

	int count();
	int height();
	bool balanced();
	void breadthFirstTraversal();
	void straighten();
	void balanceBST();
	// turn tree into a heap tree
	void heapify();
	void insertRecursively(const T& elem);

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
	void dtraverse(Vertex<T>*& V);

	/**
	 * Purpose: removes vertex from tree
	 * @param: Vertex* V - pointer to vertex to be deleted
	 * @param: Vertex* P - pointer to V's parent
	 */
	void remove(Vertex<T>* V, Vertex<T>* P);
	
	/*
	 * Purpose: find, delete, and return max element of a given tree's left sub-tree
	 * @param: Vertex* V - root node of given tree
	 */
	T findMax(Vertex<T>* V);
	


	// left sub-tree of the vertex and also deletes it
	int treeHeight(Vertex<T>* V);
	int treeBalanced(Vertex<T>* V);
	int treeCount(Vertex<T>* V);
	void backbone(Vertex<T>*& root);
	void rotateRight(Vertex<T>*& grand, Vertex<T>*& parent, Vertex<T>*& left_child);
	void rotateLeft(Vertex<T>*& grand, Vertex<T>*& parent, Vertex<T>*& child);
	
	/*
	 * Purpose: turn BST into a Heap Tree (Treap)
	 */
	void heapifyTree(Vertex<T>* V);
	void recursiveInsert(Vertex<T>*& head, const T& elem);

private:
	Vertex<T>* root;  // pointer to the root vertex
	int _count;

};

template <typename T>
Vertex<T>::Vertex(const T& E) : left(NULL), right(NULL), elem(E) {}

/**
 * Purpose: default constructor
 */
template<typename T>
BST<T>::BST() {
	root = NULL;   // This is an empty tree
	_count = 0;
}

//BST<T>::BST(const BST<T>& source): BST() {
//    TODO
//}

/**
 * Purpose: destructor, delete all heap memory used
 */
template<typename T>
BST<T>::~BST() {
	dtraverse(root); // traverse to delete all vertices in post order
	root = NULL;     // make sure root is NULL  
}

template<typename T>
int BST<T>::count() {
	return _count;
}

/**
 * Purpose: delete all vertices in the tree, traverse in post-order
 * @param: Vertex*& V - pointer to root vertex of the tree to destroy
 */
template<typename T>
void BST<T>::dtraverse(Vertex<T>*& V) {
	if (V != NULL) {
		dtraverse(V->left);        // visit left sub tree of V
		dtraverse(V->right);       // visit right sub tree of V
		delete V;                  // delete V
        V = NULL;
	}
}

/**
 * Purpose: display elements using in-order traversal from the root
 */
template<typename T>
void BST<T>::ShowInOrder() {
	cout << "elements in the IN order: " << endl;
	INorderTraversal(root);  // start in-order traversal from the root
}

/**
 * Purpose: recursively perform in-order traversal starting from given tree vertex
 * @param: Vertex* V - vertex to begin traversing from
 */
template<typename T>
void BST<T>::INorderTraversal(Vertex<T>* V) {
	if (V != NULL) {
		INorderTraversal(V->left);
		cout << V->elem << endl;
		INorderTraversal(V->right);
	}
}

/**
 * Purpose: display elements using pre-order traversal from the root
 * Note: same as Depth First Traversal
 */
template<typename T>
void BST<T>::ShowPreOrder() {
	cout << "elements in the PRE order:" << endl;
	PREorderTraversal(root);  // start pre-order traversal from the root
}

/**
 * Purpose: recursively perform pre-order traversal starting from given tree vertex
 * @param: Vertex* V - vertex to begin traversing from
 */
template<typename T>
void BST<T>::PREorderTraversal(Vertex<T>* V) {
	if (V != NULL) {
		cout << V->elem << endl; 
		PREorderTraversal(V->left);
		PREorderTraversal(V->right);
	}
}

/**
 * Purpose: insert new element into tree
 * @param: elem_t E - element to be inserted
 * Algorithm: perform insert iteratively
 *            - smaller than the current -> go to the left
 *            - bigger than the current  -> go to the right
 * 			  - cannot go any further    -> add it there
 */
template<typename T>
void BST<T>::InsertVertex(const T& E) {

	// When you are in a C++ template, the compiler doesn't know whether 
	// Container::iterator is a type or something else. So you need to 
	// explicitly say that its a type.
	Vertex<T>* N = new typename Vertex<T>::Vertex(E); // new vertex

	cout << "Trying to insert " << E << endl;
	
	// Special case: we have a brand new empty tree
	if (this->root == NULL) {
		this->root = N;      // the new vertex is added as the root
		cout << "...adding " << E << " as the root" << endl; 
	} 
	else { // the tree is not empty

		Vertex<T>* V = this->root;  // V will point to the current vertex
		Vertex<T>* Parent = NULL;        // Parent will point to V's parent

		while (V != NULL) { // go down the tree until you cannot go any further
			if (N->elem == V->elem) {
			 	cout << "...error: the element already exists" << endl;
				return;
			}
			else if (N->elem < V->elem) { // what I have is smaller than V
				cout << "...going to the left" << endl; 
				Parent = V;
				V = V->left; 
			}
			else { // what I have is bigger than V
				cout << "...going to the right" << endl;
				Parent = V;
				V = V->right; 
			}
		}//end of while

		// reached NULL -- Must add N as the Parent's child

		if (N->elem < Parent->elem) {  
			Parent->left = N;
			cout << "...adding " << E << " as the left child of " 
			     << Parent->elem << endl;
		}
		else  {
			Parent->right = N; 
			cout << "...adding " << E << " as the right child of " 
				 << Parent->elem << endl;
		}
	}// end of normal case
	++_count;
}// end of InsertVertex


/**
 * Purpose: deletes the vertex that has E as it's element.
 * @param: elem_t E - element to be removed
 * @return: true if E was found and deleted, else false
 * Algorithm: find the vertex, then call "remove"
 *            - Case 1: element is at root and root has no children
 * 			  - Case 2: element is at root and root only has left child
 * 			  - Case 3: element is at root and root only has right child
 *            - Case 4: element is somewhere else in the tree
 */
template<typename T>
bool BST<T>::DeleteVertex(const T& E) {

	cout << "Trying to delete " << E << endl;

	Vertex<T>* V      = NULL;  // the current vertex
	Vertex<T>* Parent = NULL;  // its parent

	// if E is at the root and root has no children, just delete root (case 1)
	if ((E == root->elem) && (root->left == NULL) && (root->right == NULL)) {
		cout << "...deleting the lonely root" << endl;
		delete root; 
		root = NULL;
		--_count;
		return true;
	} // only the root was there and deleted it

	// if E is the root with one child, replace root with only child
	if ((E == root->elem) && ((root->left == NULL) || (root->right == NULL))) {  
		if (root->left != NULL) { // (case 2)
			cout << "...root has only left child. deleteing root and moving to the left." << endl;
			V = root;
			root = root->left;
			delete V;           // delete left child
		} else { // (case 3)
			cout << "...root has only right child. deleting root and moving to the right." << endl;
			V = root;
			root = root->right;
			delete V;           // delete right child
		}
		--_count;
		return true;
	}

	// Otherwise deleting root with two children or some other Vertex

	V = root;  // start with the root to look for E

	while (V != NULL) { // until E is not found
		if (E == V->elem) { // found element
			cout << "...removing " << V->elem << endl;
			remove(V, Parent); // remove V from tree
			--_count;
			return true;
		} else if (E < V->elem) { // element is to the left
			cout << "...going to the left" << endl;
			Parent = V;
			V = V->left; // go to the left
		} else { // element is to the right
			cout << "...going to the right" << endl;
			Parent = V;
			V = V->right; // go to the right
		}
	}// end of while

	// reached NULL  -- did not find it
	cout << "Did not find the key in the tree." << endl;
	return false;
}// end of DeleteVertex

/**
 * Purpose: remove vertex from tree
 * @param: Vertex* V - pointer to vertex to be deleted
 * @param: Vertex* P - pointer to V's parent
 */
template<typename T>
void BST<T>::remove(Vertex<T>* V, Vertex<T>* P) {

	// if V is a leaf (case 1)
	if ((V->left == NULL) && (V->right == NULL)) {
		cout << ".. removing a leaf" << endl;
		// set Parent's left or right side to NULL based on which side V is on
		// delete V
		if (V == P->left) {
			P->left = NULL;
		} else { 
			P->right = NULL;
		}
		delete V;
	}
	// else if V has only a left child (case 2)
	else if ((V->left != NULL) && (V->right == NULL)) {
		cout << "removing a vertex with just the left child" << endl;
		// Make Parent’s left or right point to V's left child and delete V
		if (V == P->left) {
			P->left = V->left;
		} else {
			P->right = V->left;
		}
		delete V;
	}
	// else if V has only a right child (part of case 2)
	else if ((V->left == NULL) && (V->right != NULL)) {
		cout << "removing a vertex with just the right child" << endl;
		// Make Parent’s left or right point to V's right child and delete V
		if (V == P->left) {
			P->left = V->right;
		} else {
			P->right = V->right;
		}
		delete V;
	}
	else { // V has two children (case 3)
		cout << "...removing an internal vertex with children" << endl;
		cout << ".....find the MAX of its left sub-tree" << endl;
		// find, delete, and return max element in V's left sub-tree
		T Melem = findMax(V);
		cout << ".....replacing " << V->elem << " with " << Melem << endl;
		V->elem = Melem; // set V's value to max value of left sub-tree
	}
 }// end of remove

/*
 * Purpose: find, delete, and return max element of a given tree's left sub-tree
 * @param: Vertex* V - root node of given tree
 */
template<typename T>
T BST<T>::findMax(Vertex<T>* V) {

	Vertex<T>* Parent = V;
	V = V->left;          // start with the left child of parent

	// while the right child of V is still available
	while (V->right != NULL) {
		// update Parent and V to go to the right
		Parent = V;
		V = V->right;
	}
	// reached NULL right - V now has the MAX element
	
	T X = V->elem;
	cout << ".....Max is " << X << endl;
	remove(V, Parent);    // remove the MAX vertex
	--_count; 
	return X;             // return the MAX element
}// end of FindMax


// ================================================================================

/**
 * Purpose: tell if tree is balanced
 * @return: true if balanced, else false
 */
template<typename T>
bool BST<T>::balanced() {
	if(treeBalanced(root) == -1){
		return false;
	} else {
		return true;
	}
}

/**
 * Purpose: tell if tree is balanced
 * @return: true if balanced, else false
 */
template<typename T>
int BST<T>::treeBalanced(Vertex<T>* V) {
	if (V == NULL) {
		return 0;
	} else {
		int L = treeBalanced(V->left);
		if (L == -1) {
			// cout << "At element " << V->elem << endl;
			// cout << "...tree is not balanced" << endl;
			return -1;
		}
		int R = treeBalanced(V->right);
		if (R == -1) {
			// cout << "At element " << V->elem << endl;
			// cout << "...tree is not balanced" << endl;
			return -1;
		}
		// cout << "At element " << V->elem << endl;
		// cout << "...height of left  = " << L << endl;
		// cout << "...height of right = " << R << endl;
		// cout << "...difference between heights = " << abs(L - R) << endl;
		if (abs(L - R) > 1) { // diff between sub-trees > 1
			// cout << "......tree is not balanced" << endl;
			return -1;
		} else {
			// cout << "......tree is balanced" << endl;	
			return (L >= R) ? L + 1 : R + 1; // return height of larger sub-tree
		}
	}
}

template<typename T>
int BST<T>::height() {
	return treeHeight(root);
}

template<typename T>
int BST<T>::treeHeight(Vertex<T>* V) {
	if (V == NULL) {
		return 0;
	} else {
		int L = treeHeight(V->left);
		int R = treeHeight(V->right);
		// cout << "At element " << V->elem << endl;
		// cout << "...height of left  = " << L << endl;
		// cout << "...height of right = " << R << endl;
		if (L > R) {
			return L + 1;
		} else {
			return R + 1;
		}
	}
}

template<typename T>
void BST<T>::straighten() {
	backbone(root);
}

/*
 * take unbalanced tree and order the nodes from least to greatest 
 * all nodes are to the right of their parent (who has a smaller value)
 * (kind of like a linked list)
 */
template<typename T>
void BST<T>::backbone(Vertex<T>*& root) {

	if (root != NULL) {
		
		Vertex<T>* grand = NULL;
		Vertex<T>* parent = root;
		Vertex<T>* left_child;
		
		cout << "Grand is NULL" << endl;
		
		while (parent != NULL) {
			
			left_child = parent->left;
			
			cout << ".. Parent is " << parent->elem << endl;
			
			// if parent has element less than it
			if (left_child != NULL) {                    
				
				cout << ".... Left child is " << left_child->elem << endl;
				
				// move smaller element above parent
				rotateRight(grand, parent, left_child);
				
				// left_child was moved above parent, need to reset parent
				parent = left_child;
				
				// if parent is still the root
				if (grand == NULL) {     
					this->root = parent; // update root to parent
				}

			} else { // there is no element less than parent
				cout << ".... Left child is NULL" << endl;
				// move grand and parent down the right side of the tree
				grand = parent;
				parent = parent->right;
			}

			cout << "--------------------------" << endl;
			if (grand != NULL) {
				cout << "Grand is " << grand->elem << endl;
			} else {
				cout << "Grand is NULL" << endl;
			}
		}
		cout << ".. Parent is NULL" << endl << "STOP!" << endl;
	}
}

/*
 * Purpose: rotate smaller element (child) around higher element (parent)
 *          in order to move smaller element up the tree and straighten tree out
 * Example: g - child's grandparent (parent's parent)
 *          p - child's parent
 *          c - child
 * --------------------------------------------------------------------------
 *        g (NULL or 0)
 *         \
 *          p (5)
 *         /
 *        c (3)
 *       /  \
 *  (2) r    left (4)
 * grandparent's right points to child
 * parent's left points to child's right
 * child's right points to parent
 *        g (NULL or 0)
 *         \
 *          c (3)
 *         /  \
 *    (2) r    p (5)
 *           /
 *       left (4)
 */
template<typename T>
void BST<T>::rotateRight(Vertex<T>*& grand, Vertex<T>*& parent, Vertex<T>*& child) {

	if (grand != NULL) { // "parent" has a parent ("parent" is not root) 
		grand->right = child;        // grand becomes child's parent
	}
	parent->left = child->right; // parent's left inherts child's right
	child->right = parent;       // child is now parent of "parent"
}

template<typename T>
void BST<T>::rotateLeft(Vertex<T>*& grand, Vertex<T>*& parent, Vertex<T>*& child) {
	if (grand != NULL) {
		grand->right = child;
	}
	parent->right = child->left;
	child->left = parent;
}

template<typename T>
void BST<T>::balanceBST() {
	// nodes in closest perfectly balanced tree
	int m = pow(2, floor(log2(_count + 1))) - 1;
	
	cout << "Count: " << _count << endl
	      << "m: " << m << endl;

	Vertex<T>* grand = NULL;
	Vertex<T>* parent = root;
	Vertex<T>* child = root->right;

	cout << "Grand = NULL" << endl;
	cout << ".. Parent = " << parent->elem << endl;
	cout << ".... Child = " << child->elem << endl;
	
	for (int i = _count-m; i > 0; --i) {
		
		rotateLeft(grand, parent, child);
		
		if (grand == NULL) {
			root = child;
		}

		grand = child;
		parent = child->right;
		child = parent->right;

		cout << "\nAfter rotation: " << endl;
		cout << ".. Grand = " << grand->elem << endl;
		cout << ".... Parent = " << parent->elem << endl;
		cout << "...... Child = " << child->elem << endl;
	}

	while (m > 1) {
		
		grand = NULL;
		parent = root;
		child = parent->right;
		
		cout << ".. Grand = NULL" << endl;
		cout << ".... Parent = " << parent->elem << endl;
		cout << "...... Child = " << child->elem << endl;

		m /= 2;
		cout << "rotate " << m << " times" << endl;
		for (int i = 0; i < m; ++i) {
			
			rotateLeft(grand, parent, child);
			
			if (grand == NULL) {
				root = child;
			}

			grand = child;
			parent = grand->right;
			child = parent->right;

			cout << "\nAfter rotation: " << endl;
			if (grand != NULL) {
				cout << ".. Grand = " << grand->elem << endl;
			} else {
				cout << ".. Grand = NULL" << endl;
			}
			if (parent != NULL){
				cout << ".... Parent = " << parent->elem << endl;
			} else {
				cout << ".... Parent = NULL" << endl;
			}
			if (child != NULL) {
				cout << "...... Child = " << child->elem << endl;
			} else {
				cout << "...... Child = NULL" << endl;
			}
		}
	}
}

/*
 * Purpose: print tree by level
 */
template<typename T>
void BST<T>::breadthFirstTraversal() {
	queue<Vertex<T>*> q;
	Vertex<T>* V = root;
	if (V != NULL) {
		q.push(V);
		while (!q.empty()) {
			V = q.front();
			q.pop();
			cout << V->elem << " ";
			if (V->left != NULL) {
				q.push(V->left);
			}
			if (V->right != NULL) {
				q.push(V->right);
			}
			cout << endl;
		}
		
	}
}

/**
 * Purpose: turn BST into a Heap Tree (Treap)
 */
template <typename T>
void BST<T>::heapifyTree(Vertex<T>* sub_root) {
	
	Vertex<T>* min = sub_root; // find min elem between parent and left, right children

	if (sub_root->left != NULL) {
		heapifyTree(sub_root->left); // heapify left sub-tree
		if (sub_root->left->elem < min->elem) { // is left child smaller?
			min = sub_root->left;
		}
	}

	if (sub_root->right != NULL) { 
		heapifyTree(sub_root->right); // heapify right sub-tree
		if (sub_root->right->elem < min->elem) { // is right child smaller?
			min = sub_root->right;
		}
	}

	if (sub_root->elem != min->elem) { // move min elem up the sub-tree
		// cout << "swapping" << sub_root->elem << " with " << min->elem << endl;
		T tmp = sub_root->elem;
		sub_root->elem = min->elem;
		min->elem = tmp;
	}
}

/**
 * Purpose: public interface to heapifyTree function
 */
template <typename T>
void BST<T>::heapify() {
	heapifyTree(root);
}

/**
 * Purpose: get root's value
 */
template <typename T>
T BST<T>::getRoot() {
	return root->elem;
}

/*
 * Given an ordered array, create a BST
 */
template <typename T>
BST<T>* BST<T>::createBST(const T list[], int n) {
	BST<T>* bst = new BST<T>();
	bst->root = BST<T>::createFromArray(list,0,n-1);
	return bst;
}

template <typename T>
Vertex<T>* BST<T>::createFromArray(const T list[], int min, int max) {
	
	if (max < min) {
		return NULL;
	}

	int mid = (min+max)/2;
	Vertex<T>* V = new typename Vertex<T>::Vertex(list[mid]);
	// cout << "Created " << V->elem << endl;
	V->left = createFromArray(list, min, mid-1);
	V->right = createFromArray(list, mid+1, max);
	return V;
}

template <typename T>
bool BST<T>::containsSubTree(BST<T>*& sub_tree) {
	// if (this->root == NULL) {
	// 	cout << "No big tree: returning false" << endl;
	// 	return false;
	// } else if (sub_tree->root == NULL) {
	// 	cout << "Subtree is NULL: returning true" << endl;
	// 	return true;
	// } else {
		return subTree(this->root, sub_tree->root);
	// }
}

template <typename T>
bool BST<T>::subTree(Vertex<T>* main, Vertex<T>* sub_tree) {
	
	if (main == NULL && sub_tree == NULL) {
		// cout << "Both at end: returning true" << endl;
		return true;
	} else if (main == NULL || sub_tree == NULL) {
		// cout << "Main or Sub is empty, but not both, (sub-trees not the same): returning false" << endl;
		return false;
	} else if (main->elem == sub_tree->elem) {
		// cout << main->elem << " == " << sub_tree->elem << endl;

		// cout << main->elem << ": Looking in left sub-tree" << endl;
		bool L = subTree(main->left, sub_tree->left);

		// cout << main->elem << ": Looking in right sub-tree" << endl;
		bool R = subTree(main->right, sub_tree->right);

		if (L && R) { // left and right also the same trees
			// cout << main->elem << ": left and right are the same: return true" << endl;
			return true;
		} else { // not the same
			// cout << main->elem << ": left and right are not the same: return false" << endl;
			return false;
		}
	} else {
		// cout << main->elem << " != " << sub_tree->elem << endl;
		// cout << main->elem << ": checking if left lower main sub-tree is a match" << endl;
		if (subTree(main->left, sub_tree)) {
			// cout << "was a match" << endl;
			return true;
		} 
		// cout << main->elem << ": checking if right lower main sub-tree is a match" << endl;
		if (subTree(main->right, sub_tree)) {
			// cout << "was a match" << endl;
			return true;
		} else {
			// cout << "wasn't a match" << endl;
			return false;
		}
	}
}

template <typename T>
void BST<T>::insertRecursively(const T& elem) {
	recursiveInsert(root, elem);
}

template <typename T>
void BST<T>::recursiveInsert(Vertex<T>*& head, const T& elem) {
	if (head == NULL) {
		head = new typename Vertex<T>::Vertex(elem); // new vertex
	} else if (elem < head->elem) {
		cout << "Going left of " << head->elem << endl;
		recursiveInsert(head->left, elem);
	} else {
		cout << "Going right of " << head->elem << endl;
		recursiveInsert(head->right, elem);
	}
}

/*
 * Check to see if path from root to a leaf has a path sum of X
 */
template <typename T>
bool BST<T>::hasPathSum(T sum) {
	int path_sum = 0;
	return bstHasPathSum(root, path_sum, sum);
}

/*
 * Helper function to hasPathSum
 */
template <typename T>
bool BST<T>::bstHasPathSum(Vertex<T>* V, T& path_sum, T& sum) {
	if (V == NULL) {
		// cout << ".. At leaf: Path sum is " << path_sum << endl;
		return (path_sum == sum) ? true : false;
	} else {
		path_sum += V->elem;
		// cout << path_sum << " - Added " << V->elem << " to path_sum" << endl;
		if (bstHasPathSum(V->left,path_sum,sum) || bstHasPathSum(V->right,path_sum,sum)) {
			// cout << path_sum << " - Removed " << V->elem << " from path_sum" << endl;
			path_sum -= V->elem;
			return true;
		} else {
			// cout << path_sum << " - Removed " << V->elem << " from path_sum" << endl;
			path_sum -= V->elem;
			return false;
		}
	}
}

#endif

