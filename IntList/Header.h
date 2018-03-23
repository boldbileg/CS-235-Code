#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct node
{
	int num;
	node* next;
	node();
	node(int newNum, node* newLink = NULL);
};

class IntList
{
private:
	node* head;
public:
	int count;
	IntList();
	void newNode(int newNum);
	int traverse(int index);
	void travPrt(void(*print)(node*));
	void delLast();
};

struct Node
{
	int num;
	Node* next;
	Node* prev;
	Node();
	Node(int newNum, Node* prevLink = NULL, Node* nextLink = NULL);
};

class DubList //short for double linked list
{
private:
	const int NODE_MIN = 3;
	Node* dHead; //short for head of double linked list
public:
	int count;
	DubList();
	void dubNode(int newNum);
	void dubTravPrt(void(*print)(Node*));
};