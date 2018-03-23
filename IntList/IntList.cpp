#include "Header.h"
#include <iostream>
#include <string>
#include <fstream> 

node::node()
{
	next = NULL;
}

node::node(int newNum, node* newLink)
{
	num = newNum;
	next = newLink;
}

IntList::IntList()
{
	count = 0;
	head = NULL;
}

void IntList::newNode(int newNum)
{
	node* newNode = head;
	node* temp = NULL;

	if (head == NULL)
	{
		head = new node(newNum);
		head->next = NULL;
	}
	else if (head->next == NULL)
	{
		newNode = new node(newNum);
		head->next = newNode;
	}
	else
	{
		while (newNode != NULL)
		{
			temp = newNode;
			newNode = newNode->next;
		}
		newNode = new node(newNum);
		temp->next = newNode;
	}
	count++;
}

int IntList::traverse(int index)
{
	node* newNode;
	newNode = head;
	for(int i = 0; i < index; i++)
	{
		newNode = newNode->next;
	}
	return newNode->num;
}

void IntList::travPrt(void(*print)(node*))
{
	node* newNode;
	newNode = head;
	while (newNode != NULL)
	{
		(*print)(newNode);
		newNode = newNode->next;
	}
}

void IntList::delLast()
{
	node* temp = NULL;
	node* badNode = head;

	while (badNode->next != NULL)
	{
		temp = badNode;
		badNode = badNode->next;
	}
	delete badNode;
	temp->next = NULL;
}

void print(node* p)
{
	cout << p->num << endl;
}

void print(Node* p)
{
	cout << p->num << endl;
}

Node::Node()
{
	next = NULL;
	prev = NULL;
}

Node::Node(int newNum, Node* prevLink, Node* nextLink)
{
	num = newNum;
	next = nextLink;
	prev = prevLink;
}

DubList::DubList()
{
	dHead = NULL;
}

void DubList::dubNode(int newNum)
{
	Node* newNode = dHead;
	Node* temp = NULL;

	if (dHead == NULL)
	{
		dHead = new Node(newNum);
		dHead->next = NULL;
		dHead->prev = NULL;
	}
	else if (dHead->next == NULL)
	{
		if (newNum >= dHead->num)
		{
			newNode = new Node(newNum, dHead);
			dHead->next = newNode;
			newNode->prev = dHead;
		}
		else
		{
			temp = dHead;
			dHead = new Node(newNum, NULL, temp);
			dHead->next = temp;
			temp->prev = dHead;
		}
	}
	else
	{
		if (newNode->num > newNum)
		{
			temp = dHead;
			dHead = new Node(newNum, NULL, temp);
			dHead->next = temp;
			temp->prev = dHead;
		}
		else
		{
			Node* newNode2 = NULL;
			while (newNode != NULL && newNode->num <= newNum)
			{
				temp = newNode;
				newNode = newNode->next;
			}
			newNode2 = new Node(newNum, temp, newNode);
			temp->next = newNode2;
			newNode2->prev = temp;
			if (newNode != NULL)
			{
				newNode2->next = newNode;
				newNode->prev = newNode2;
			}
		}
	}
	count++;
}

void DubList::dubTravPrt(void(*print)(Node*))
{
	Node* newNode;
	newNode = dHead;
	while (newNode != NULL)
	{
		(*print)(newNode);
		newNode = newNode->next;
	}
}

using namespace std;

int main()
{
	IntList singList;
	DubList dubList;
	ifstream infile;
	string filename;
	int newNum;

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 2: Linked Lists" << endl << endl;

	cout << "Enter valid filename: ";
	getline(cin, filename);
	infile.open(filename.c_str());
	if (infile.fail())
	{
		cout << "File error" << endl;
		system("pause");
		return 1;
	}

	while (!infile.eof())
	{
		infile >> newNum;
		singList.newNode(newNum);
	}

	singList.delLast();
	singList.count--;

	for(int i = 0; i < singList.count; i++)
	{
		dubList.dubNode(singList.traverse(i));
	}

	cout << endl << "Single Linked List contents: " << endl;
	singList.travPrt(print);

	cout << endl << "Double linked List contents: " << endl;
	dubList.dubTravPrt(print);

	system("pause");
	return 0;
}