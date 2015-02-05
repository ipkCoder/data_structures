
/*================================================================================

HW1P1 - stack client
Name:           Ian Kane
Date:           Sept. 10, 2014
Complier:       g++ 4.7
How to compile: g++ stack.cpp client1.cpp -o client1
File type:      stack client file
Purpose:        Calculate answer to post-fix expression. Limitation of 
                post-fix expression to integer digits (0-9)

================================================================================*/

#include <iostream>
#include <string>
using namespace std;

#include "stack.h"

int main() {
  
    stack postfixstack;  // integer stack
    string expression;

    cout << "type a postfix expression: " ;
    cin >> expression;

    int i = 0;  // character position within expression
    char item;

    int box1;  // receive things from pop
    int box2;  // receive things from pop
    int result;

    while (expression[i] != '\0') {

        try {
            // read an item from expression
            item = expression[i];
            
            // if it is an operand (number), push it 
            // (you might get Overflow exception)
            if (isdigit(item)) {
                postfixstack.push(item - '0');
            }
            // else if it is an operator,
            // pop the two operands (you might get Underflow exception),
            // and apply the operator to the two operands.
            // Push the result.
            else if ((item == '+') || (item == '-') || (item == '*')) {
                
                // get numbers to perform operation on
                postfixstack.pop(box1);
                postfixstack.pop(box2);
                
                // determine what operation to perform
                if (item == '+') {
                    result = box2 + box1;
                } else if (item == '-') {
                    result = box2 - box1;
                } else if (item == '*') {
                    result = box2 * box1;
                }
                
                postfixstack.push(result); // push result onto stack
            } else {
                throw "invalid item";
            } 

            postfixstack.displayAll(); // print current stack
            cout << "--------" << endl;
        } // this closes try
        // Catch exceptions and report problems and quit the program now. 
        catch (stack::Overflow) {
            cout << "Expresion is too long" << endl;
            exit(0);
        } catch (stack::Underflow) {
            cout << "too few operands" << endl;
            exit(0);
        } catch (char const* errorcode) { // for invalid item
            cout << errorcode << endl;
            exit(0);
        }
        
        ++i;
    }// end of while

    // After the loop successfully completes: 
    // The result will be at the top of the stack. Pop it and show it.
    // If anything is left on the stack, an incomplete expression was 
    // found. Inform the user.
    postfixstack.pop(result);
    cout << "result = " << result << endl;

    if (!postfixstack.isEmpty()) {
        cout << "Incomplete expression" << endl;
    }

    // clear stack
    postfixstack.clearIt();
}
