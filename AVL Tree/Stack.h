#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Stack
{
	Node *ptr;
	Stack *prev;
	Stack();
	Stack(Node *newPtr, Stack *newLink = NULL);
};

class StackClass
{
private:
	Stack *top;
public:
	StackClass();
	Node* getTop(); //returns the top of the stack
	void push(Node *newPtr);
	void pop();
	bool isNull(); //checks if the stack is empty
};