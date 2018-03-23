#include "HashTable.h"
#include "Chaining.h"
#include <iostream>
#include <string>
#include <fstream>
#include <array>

using namespace std;

//constructors
node::node()
{
	next = NULL;
}

node::node(int newVal, node* newLink)
{
	val = newVal;
	next = newLink;
}

ChainedList::ChainedList()
{
	for (int i = 0; i < SIZE; i++)
	{
		ChainedTable[i] = NULL;
	}
}

//Inserts itme into chained hash table
void ChainedList::insert(int value, int key)
{
	//sets first node in the list if not occupied
	if (ChainedTable[key] == NULL)
	{
		ChainedTable[key] = new node(value);
	}
	else
	{
		node *p = ChainedTable[key];
		node *q = p;

		//finds empty spot in the list
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}

		//adds new item to last link
		q->next = new node(value);
	}
}

void ChainedList::print()
{
	cout << endl << "Chained Hash Table Contents" << endl << "Node Key   Values";

	//traverses the list and prints the index and values of each node
	for (int i = 0; i < SIZE; i++)
	{
		cout << endl << i << "	   ";

		if (ChainedTable[i] != NULL)
		{
			node *p = ChainedTable[i];
			node *q = p;
			cout << q->val;
			p = p->next;
			while (p != NULL)
			{
				q = p;
				p = p->next;
				cout << ", " << q->val;
			}
		}
		else
		{
			cout << "NULL";
		}
	}

	cout << endl << endl;
}

//constructor
Hash::Hash()
{
	for (int i = 0; i < 20; i++)
	{
		HashTable[i] = INIT;
	}
}

//Inserts itme into open address hash table
bool Hash::insert(int value, int location)
{
	bool inserted = false;

	if (HashTable[location] != INIT)
	{
		if (!full)
		{
			printf("Collision detected at location %d, for value %d", location, value);
			cout << endl;
		}
		else //if full flag is raised a message will display
		{
			cout << "List is full" << endl;
		}
		inserted = false;
	}	
	else //if list is not full and the space is empty, adds item to the list
	{
		HashTable[location] = value;
		inserted = true;
	}

	if (full)
	{
		inserted = false;
	}

	return inserted;
}

bool Hash::resolveCollision(int value, int originalLoc)
{
	bool resolved = false;
	const int MAX_INDEX = 19;
	int countSize = 0;

	//traverses the entire list once to find an empty space
	while (countSize < MAX_INDEX && HashTable[originalLoc] != INIT)
	{
		originalLoc++;
		if (originalLoc == SIZE)
		{
			originalLoc = 0;
		}
		countSize++;
	}
	//if all indexes haven't been checked then the list isn't full
	if (countSize != MAX_INDEX)
	{
		HashTable[originalLoc] = value;
		resolved = true;
	}
	else
	{
		full = true;
	}

	return resolved;
}

//traverses the hash table and prints the contents
void Hash::show()
{
	cout << endl << "HASH TABLE contents" << endl << "Element   Value";
	for (int i = 0; i < 20; i++)
	{
		cout << endl << i << "	  " << HashTable[i];
	}
	cout << endl << endl;
}

//creates a key for the hash table value
int getHashValue(int value)
{
	const int SIZE = 20;
	const int FULL = -2;
	int locale = 0;

	locale = value % SIZE;

	return locale;
}

int main()
{
	ChainedList ChainTable;
	Hash HashTable;
	ifstream infile;
	string filename;
	int data = 0;
	int loc = 0;
	int count = 1;
	bool resolve = false;

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 5: Hashing" << endl << endl;

	//takes file name and exits program if file is not found
	cout << "enter valid filename: ";
	getline(cin, filename);
	infile.open(filename.c_str());
	if (infile.fail())
	{
		cout << "file error" << endl;
		system("pause");
		return 1;
	}

	while (!infile.eof())
	{
		infile >> data;
		loc = getHashValue(data); //saves key to variable loc
		//checks if the insert was successful; if not, resolves the collision
		if (!(HashTable.insert(data, loc)))
		{
			HashTable.resolveCollision(data, loc);
		}
		//inserts into the chained hash table
		ChainTable.insert(data, loc);
	}

	infile.close();

	//print contents
	HashTable.show();
	ChainTable.print();

	system("pause");
	return 0;
}