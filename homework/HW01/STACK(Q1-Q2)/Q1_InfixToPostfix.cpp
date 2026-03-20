/*
1.[CODING QUESTION 5 points]: 
Write a C++ program that can take in a mathematical expression in "infix" notation and converts it to 'postfix' notation. 
*/
// Example:
// Input: "A + B * C - D"
// Output: "A B C * + D -"
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
int precedence(char o) {
    if(o == '+' || o == '-') return 1;
    else if(o == '*' || o == '/') return 2;
    else if(o == '^') return 3;
    else return 0;//non-operator or "(" 
}
bool isLeftAssociative(char o) {
    return o != '^'; // '^' is right associative
}
string infixToPostfix(const string& infix) {
    stack<char> myStack;
    string postfix = "";
    for(int i = 0; i < infix.length(); i++) {
        char token = infix[i];
        if (token == ' ') {
            continue; // Skip spaces
        }
        //If next token is '(':
        if (token == '(') {
            myStack.push(token);//Push it onto S.
        }
        //Else if next token is an operand:
        else if (isalnum(token)) {//isalnum is an inline function in ctype.h to check if character is alphanumeric, eg: A-Z, a-z, 0-9
            postfix += token;//Output it.
        }
        
        //Else if next token is ')':
        else if (token == ')') {
            //Discard ')'.
            while (!myStack.empty() && myStack.top() != '(') {//while top != '(':
                postfix += myStack.top();//output top of stack
                myStack.pop();
            }
            if (!myStack.empty()){
                myStack.pop();//pop '(' from stack
            }
        }
        else if (isOperator(token)) {
            //while stack not empty and 
            //(precedence(top) > precedence(t) OR
            //(precedence(top) == precedence(t) and t is left-associative)):
            while(!myStack.empty() && (precedence(myStack.top()) > precedence(token) || (precedence(myStack.top()) == precedence(token) && isLeftAssociative(token)))) {
                postfix += myStack.top();//output pop
                myStack.pop();//pop stack
            }
            myStack.push(token);//push t onto stack
        }
        //clean up after reading all tokens:
    }
    while (!myStack.empty()) {
        postfix += myStack.top();
        myStack.pop();
    }
    return postfix;
}

int main() {
    // 测试用例
    string test1 = "A + B * C - D";
    string test2 = "(A + B) * C";
    string test3 = "A * (B + C)";
    string test4 = "A + B + C + D";
    
    cout << "Test 1:" << endl;
    cout << "Input:  " << test1 << endl;
    cout << "Output: " << infixToPostfix(test1) << endl << endl;
    // Expected Output: "A B C * + D -"
    //过程如下：
    //1. 读入 'A'，是操作数，输出 "A"
    //2. 读入 '+'，是运算符，栈空，压入 '+'
    //3. 读入 'B'，是操作数，输出 "B"
    //4. 读入 '*'，是运算符，栈顶是 '+'，'*' 的优先级高于 '+', 压入 '*'
    //5. 读入 'C'，是操作数，输出 "C"
    //6. 读入 '-'，是运算符，栈顶是 '*'，'-' 的优先级低于 '*', 弹出 '*' 输出 "C *"，栈顶现在是 '+'，'-' 的优先级等于 '+', 因为 '-' 是左结合的，所以弹出 '+' 输出 "B +", 然后压入 '-'
    //7. 读入 'D'，是操作数，输出 "D"
    //8. 读入结束，弹出栈中剩余的 '-' 输出 "D -"
    
    cout << "Test 2:" << endl;
    cout << "Input:  " << test2 << endl;
    cout << "Output: " << infixToPostfix(test2) << endl << endl;
    // Expected Output: "A B + C *"
    //过程如下：
    //1. 读入 '(', 是左括号，压入 '('
    //2. 读入 'A', 是操作数，输出 "A"
    //3. 读入 '+', 是运算符，栈顶是 '(', '(' 的优先级为 0, '+' 的优先级为 1,所以压入 '+'
    //4. 读入 'B', 是操作数，输出 "B"
    //5. 读入 ')', 是右括号，弹出栈顶直到遇到 '('，弹出 '+' 输出 "B +", 弹出 '('但不输出
    //6. 读入 '*', 是运算符，栈空，压入 '*'
    //7. 读入 'C', 是操作数，输出 "C"
    //8. 读入结束，弹出栈中剩余的 '*' 输出 "C *"
    
    cout << "Test 3:" << endl;
    cout << "Input:  " << test3 << endl;
    cout << "Output: " << infixToPostfix(test3) << endl;
    // Expected Output: "A B C + *"
    //过程如下：
    //1. 读入 'A', 是操作数，输出 "A"
    //2. 读入 '*', 是运算符，栈空，压入 '*'
    //3. 读入 '(', 是左括号，压入 '('
    //4. 读入 'B', 是操作数，输出 "B"
    //5. 读入 '+', 是运算符，栈顶是 '(', '(' 的优先级为 0, '+' 的优先级为 1,所以压入 '+'
    //6. 读入 'C', 是操作数，输出 "C"
    //7. 读入 ')', 是右括号，弹出栈顶直到遇到 '('，弹出 '+' 输出 "C +", 弹出 '('但不输出
    //8. 读入结束，弹出栈中剩余的 '*' 输出 "B C + *"

    cout << "Test 4:" << endl;
    cout << "Input:  " << test4 << endl;
    cout << "Output: " << infixToPostfix(test4) << endl;
    // Expected Output: "A B + C + D +"
    //过程如下：
    //1. 读入 'A', 是操作数，输出 "A"
    //2. 读入 '+', 是运算符，栈空，压入 '+'
    //3. 读入 'B', 是操作数，输出 "B"
    //4. 读入 '+', 是运算符，栈顶是 '+', '+' 的优先级等于 '+', 因为 '+' 是左结合的，所以弹出 '+' 输出 "B +", 然后压入 '+'
    //5. 读入 'C', 是操作数，输出 "C"
    //6. 读入 '+', 是运算符，栈顶是 '+', '+' 的优先级等于 '+', 因为 '+' 是左结合的，所以弹出 '+' 输出 "C +", 然后压入 '+'
    //7. 读入 'D', 是操作数，输出 "D"
    //8. 读入结束，弹出栈中剩余的 '+' 输出 "D +"
    
    return 0;
}