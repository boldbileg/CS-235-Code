#pragma once
#include <iostream>
#include <string>

class Hash
{
private:
	bool full = false; //flag for when open address list is full
	int value;
	int location; //location in the table
	int originalLoc;
	int HashTable[20];
	static const int SIZE = 20;
	static const int INIT = -999;
public:
	Hash();
	bool insert(int value, int location);
	bool resolveCollision(int value, int originalLoc);
	void show();
};