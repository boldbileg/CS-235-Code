#pragma once
#include <iostream>
#include <string>
#include <sstream>

struct Node
{
	int num;
	int bf; //balance factor
	Node* rlink; //right link
	Node* llink; //left link
	//constructors
	Node();
	Node(int newNum, Node* rLink = NULL, Node* lLink = NULL);
};

class Tree
{
private:
	Node *parent; //parent of the fixed subtree
	Node *OBchild; //child of the out of balance node
	Node *OBgrandchild; //grandchild of the out of balance node
	Node *OBparent; //parent of the out of balance node (for reconnecting into the tree)
	Node *root; //root of the binary tree
	Node *OBnode; //short for out of balance node
	//variables to flag if the out of balance node is the left or right child of OBparent
	bool right; 
	bool left;
public:
	int count;
	Tree();
	bool insert(int newNum);
	void getRoot(); //gives the root of the tree to the traversal functions
	void travInOrder(Node *p);
	Node* findParent(Node* p); //finds the parent of the out of balance node
	void travPreOrder(Node *p);
	//professor's functions to calculate balance factor
	void balfactor(Node * p);
	void bfactor();
	void balance(Node *OBnode);
};