
/*--------------------------------------------------------------------------------
 * Author:       Ian Kane
 * Date:         October 18, 2014
 * Compiler:     g++ 4.7
 * Command:      g++ llist.cpp slist.cpp compare_slists.cpp -o main
 * File Type:    source file (compare_slists.cpp)
 * Dependencies: llist.cpp llist.h
 *               slist.cpp slist.h
 * Purpose:      test linked list's "==" comprison operator
 --------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

#include "slist.h"

int main() {

	slist L1, L2;
	int tmp;

	// ====================== case 1 ============================
	cout << "L1 is empty and L2 is empty" << endl;
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll(); 
	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 2 ============================
	cout << "L1 is empty and L2 has 2 elements" << endl;
	L2.addRear(1).addRear(2);
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();
	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 3 ============================
	cout << "L1 has 2 elements and L2 is empty" << endl;
	L1.addRear(1).addRear(2);
	L2.deleteAllFromRear();
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();

	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 4 ============================
	cout << "L1 has 1,2,3 and L2 has 1,2,3" << endl;
	L1.addRear(3);
	L2.addRear(1).addRear(2).addRear(3);
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();
	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 5 ============================
	cout << "L1 has 1,2,3 and L2 has 1,2" << endl;
	L2.deleteRear(tmp);
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();
	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 6 ============================
	cout << "L1 has 1,2,3 and L2 has 1,2,3,4" << endl;
	L2.addRear(3).addRear(4);
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}
	cout << endl;
	
	// ====================== case 7 ============================
	cout << "L1 has 1,2,3 and L2 has 1,2,4" << endl;
	L2.deleteIth(3, tmp);
	cout << "L1: "; L1.displayAll();
	cout << "L2: "; L2.displayAll();
	if (L1 == L2) {
		cout << "L1 == L2" << endl;
	} else {
		cout << "L1 != L2" << endl;
	}

}