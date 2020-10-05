
//Imports
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////
/////////////////////STACK_CLASS/////////////////////////
/////////////////////////////////////////////////////////

class MyStack {
private:
	int top;
	char stack[20];
public:
	MyStack(int top);
	void push(char item);
	void pop();
	bool isEmpty();
	int getTop();
	int getTopInt();
	char getCharTop();
	void showStack();
};
//Constructor
MyStack::MyStack(int top) {
	this->top = top;
	char stack[20];

}
//Functs
void MyStack::push(char item) {
	if (getTop() == 19) {
		cout << "Overflow" << endl;
	}
	else {
		top += 1;
		stack[top] = item;
	}
}
void MyStack::pop() {
	if (getTop() == -1) {
		cout << "Underflow" << endl;
		
	}
	else {
		char ch;
		ch = stack[top];
		top -= 1;
	}
}
bool MyStack::isEmpty() {
	if (top == -1) return true;
	else return false;
}
int  MyStack::getTop() {
	return top;
}
int  MyStack::getTopInt() {
	return stack[top];
}
char MyStack::getCharTop() {
	return stack[top];
}
void MyStack::showStack() {
	cout << stack[top] << endl;
}
//END OF STACK

/////////////////////////////////////////////////////////
/////////////////////FUNCTIONALITY///////////////////////
/////////////////////////////////////////////////////////

//IS THE STRING VALID//PROGRAM 1.
bool isBalanced(string s) {
	MyStack stack1(-1);
	for (int i = 0; i < s.length(); i++) {
		char ch = s[i];
		
		if ((ch == '(') || (ch == '{') || (ch == '[')) {
			stack1.push(ch);
		}
		else if ((ch == ')') || (ch == '}') || (ch == ']')) {
			if (stack1.getTop() == -1) {
				return false;
			}
			else stack1.pop();
		}
	}
	//Returns 1 if valid and 0 if invalid!!!
	return stack1.isEmpty() ? true : false;
}

//checks if operand
bool isOperand(char i) {
	
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i>= '0' && i <= '9')) {
		return true;
	}
	else {
		return false;
	}
};

//checks if operator
bool isOperator(char i) {
	if (i == '+' || i == '-' || i == '*' || i == '/' || i == '^') {
		return true;
	}
	else return false;
}
//checks charackter for order of operation(precedence)
int precedence(char i) {
	if		(i == '^')				return 3;
	else if (i == '*' || i == '/')	return 2;
	else if (i == '+' || i == '-')	return 1;
	else							return -1;
}
//Funct to translate infix to postfix. returns a string.// PROGRAM 3.
string infixTOpostfix(string infix, MyStack stack) {
	string postfix;
	int i; 

	for (i = 0; i < infix.length(); i++) {
		if (isOperand(infix[i])) {
			postfix += infix[i];
		}
		else if (infix[i] == '(') {
			stack.push(infix[i]);
		}
		else if (infix[i] == ')') {
			while ((stack.getCharTop() != '(') && (!stack.isEmpty())) {
				char t = stack.getCharTop();
				postfix += t;
				stack.pop();
			}
			if (stack.getCharTop() == '(') {
				stack.pop();
			}
		}
		else if (isOperator(infix[i])) {
			if (stack.isEmpty()) {
				stack.push(infix[i]);
			}
			else if (!stack.isEmpty()) {
				if (precedence(infix[i]) > precedence(stack.getCharTop())) {
					stack.push(infix[i]);
				}
				else if (precedence(infix[i]) == precedence(stack.getCharTop()) && infix[i]=='^') {
					stack.push(infix[i]);
				}
				else {
					while (!stack.isEmpty() && (precedence(infix[i]) <= precedence(stack.getCharTop()))) {
						char t = stack.getCharTop();
						postfix += t;
						stack.pop();
					}
					stack.push(infix[i]);
				}
			}
		}
	}
	while (!stack.isEmpty()) {
		postfix += stack.getCharTop();
		stack.pop();
	}
	return postfix;
}

//EVALUATES A POSTFIX EXPRESSION: returns an int.
int postfixEval(string postfix, MyStack stack) {
	int result;
	int i;

	for (i = 0; i < postfix.length(); i++) {
		if (postfix[i] == ' ') {
			continue;
		}
		if (isOperand(postfix[i])) {
			stack.push(postfix[i] - '0');
		}
		else if (!stack.isEmpty() && postfix[i] != ' ') {
			int topValue = stack.getTopInt();
			stack.pop();
			int secValue = stack.getTopInt();
			stack.pop();
			switch (postfix[i]) {
				case '+': stack.push(secValue + topValue); 
					break;
				case '-': stack.push(secValue - topValue);
					break;
				case '*': stack.push(secValue * topValue);
					break;
				case '/': stack.push(secValue / topValue);
					break;
				case '^': stack.push(secValue ^ topValue);
					break;
			}
		}
		else {
			return -1;
		}
	}
	return result=(stack.getTopInt());
}

/////////////////////////////////////////////////////////
////////////////////////MAIN/////////////////////////////
/////////////////////////////////////////////////////////

int main() {
	ifstream file;
	file.open("Buff.txt");
	if (!file.is_open()) {
		cout << "Error while opening file!";
	}
	else {
		string line;
		string infix;
		string postfix;
		int result;
		MyStack stack(-1);
		
		cout << "\t" << "Reading from the file." << endl;
		cout << "\n";
		while (file.good()) {
			getline(file, line);
			cout <<"infix: "<< line << endl;
			if (isBalanced(line)) {
				cout << "!!! Valid !!!" << endl;
				cout << endl;
				postfix = infixTOpostfix(line, stack);
				cout << "Postfix: " << postfix << endl;
				cout << endl;
				result = postfixEval(postfix, stack);
				cout << "Result: "<< result << endl;
				cout << endl;
				cout << "------------------------" << endl;
			}
			else {
				cout << "!!! Invalid expression !!!" << endl;
			}
		}
	}
}

//Main instructions for program 1.
	/*
	string s;
	getline(cin, s);
	cout << isBalanced(s) << endl;
	*/

	//MAin for prog 3.
	/*
	MyStack stack(-1);
	string infix;
	getline(cin, infix);
	cout << infixTOpostfix(infix, stack) << endl;
	*/



	/*Main instructions for program 2.

	string postfix;
	getline(cin, postfix);
	int result;
	result = postfixEval(postfix, stack);
	cout << result << endl;
	*/

/*
cout << "Result: " << isBalanced(line) << endl;
			cout << "----------------------" << endl;
			cout << "\n" << endl;
*/
