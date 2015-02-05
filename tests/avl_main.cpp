
#include <iostream>
using namespace std;

#include "avl.h"

int main() {
	AVL<int> avl;

	for (int i = 0; i < 10; ++i) {
		avl.insert(i);
	}
	avl.showInOrder();
	avl.remove(3);
	avl.showPreOrder();
}