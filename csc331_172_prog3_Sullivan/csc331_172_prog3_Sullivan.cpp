//*********************************************************************************
// Course Id: CSC331
// Section: 172
// Programmer: Daniel Sullivan
// Program Name: Stack Implementation
// Program Purpose: This program will: 
// 1. Implement a stack data structure using C++. 
// 2. It will be interactive. 
// 3. a. A transaction will be entered at the command line after a short prompt, 
//    b. output will be displayed on the console, and 
//    c. then another transaction is requested.
//    **Note: a batch of input transactions in a plain text file can and will be processed using redirection.
// Due Date: 10/30/2026
//*********************************************************************************
//*********************************************************************************
// Course Id: CSC331
// Section: 172
// Programmer: Daniel Sullivan
// Program Name: Stack Implementation
// Program Purpose: This program will: 
// 1. Implement a stack data structure using C++. 
// 2. It will be interactive. 
// 3. a. A transaction will be entered at the command line after a short prompt, 
//    b. output will be displayed on the console, and 
//    c. then another transaction is requested.
//    **Note: a batch of input transactions in a plain text file can and will be processed using redirection.
// Due Date: 10/30/2026
//*********************************************************************************
#include <iostream>
#include <string>
#include <cmath>
#include "Stack_f26.h"
#include "myDefs_f26p3.h"
#include "myMethods_f26p3.h"

using namespace std;

// Evaluate a single postfix expression using Stack_f26.
// Returns the result and sets ok = false if an error occurs.
double evaluatePostfix(const string& expr, bool& ok) {
    Stack_f26 stack;   // assumes Stack_f26 supports push(double), pop(double&), isEmpty()
    ok = true;

    for (char ch : expr) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            // single-digit operand
            double value = ch - '0';
            stack.push(value);
        }
        else {
            // operator: need two operands
            double right, left;

            if (stack.isEmpty()) { ok = false; return 0.0; }
            stack.pop(right);
            if (stack.isEmpty()) { ok = false; return 0.0; }
            stack.pop(left);

            double result = 0.0;

            switch (ch) {
            case '+':
                result = left + right;
                break;
            case '-':
                result = left - right;
                break;
            case '*':
                result = left * right;
                break;
            case '/':
                if (right == 0.0) {
                    cout << "error: division by zero" << endl;
                    ok = false;
                    return 0.0;
                }
                result = left / right;
                break;
            case '%': {
                // check integer operands
                if (right == 0.0) {
                    cout << "error: division by zero" << endl;
                    ok = false;
                    return 0.0;
                }
                bool leftInt = floor(left) == left;
                bool rightInt = floor(right) == right;
                if (!leftInt || !rightInt) {
                    cout << "error: non-integer operand for %" << endl;
                    ok = false;
                    return 0.0;
                }
                long long li = static_cast<long long>(left);
                long long ri = static_cast<long long>(right);
                result = static_cast<double>(li % ri);
                break;
            }
            case '^':
                result = pow(left, right);
                break;
            default:
                // unknown operator (should not happen per spec)
                ok = false;
                return 0.0;
            }

            stack.push(result);
        }
    }

    // final result
    double finalResult = 0.0;
    if (!stack.isEmpty()) {
        stack.pop(finalResult);
    }
    return finalResult;
}

int main() {
    string transaction;

    while (true) {
        cout << "enter transaction: ";
        if (!getline(cin, transaction)) {
            // EOF from input (e.g., redirection)
            break;
        }

        if (transaction == "end-of-file") {
            break;
        }

        bool ok = true;
        double result = evaluatePostfix(transaction, ok);

        if (ok) {
            cout << result << endl;
        }
        // if not ok, error message already printed; just prompt again
    }

    return 0;
