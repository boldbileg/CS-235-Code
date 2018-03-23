#pragma once
#include <iostream>
#include <string>
#include <sstream>

struct node
{
	int val;
	node* next;
	node();
	node(int newVal, node* newLink = NULL);
};

class ChainedList
{
private:
	static const int SIZE = 20;
	node* ChainedTable[20];
public:
	ChainedList();
	void insert(int value, int key);
	void print();
};