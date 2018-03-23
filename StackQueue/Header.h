#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Stack
{
	int val;
	Stack *prev;
	Stack();
	Stack(int newNum, Stack *newLink = NULL);
};

class StackClass
{
private:
	Stack *top;
public:
	const string typeName = "stack";
	StackClass();
	void push(int newNum);
	void travPrt(void(*print)(Stack*));
	void pop();
	bool isNull();
};

struct Queue
{
	int val;
	Queue *next;
	Queue();
	Queue(int newNum, Queue *nextLink = NULL);
};

class QueueClass
{
private:
	Queue *front;
	Queue *rear;
public:
	const string typeName = "queue";
	QueueClass();
	void append(int newNum);
	void serve();
	bool frontNull();
	void travPrint(void(*print)(Queue*));
};