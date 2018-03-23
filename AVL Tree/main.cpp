#include "Header.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <cmath>

using namespace std;

Stack::Stack()
{
	prev = NULL;
}

Stack::Stack(Node* newPtr, Stack *newLink)
{
	prev = newLink;
	ptr = newPtr;
}

StackClass::StackClass()
{
	top = NULL;
}

//checks if the stack is empty
Node* StackClass::getTop()
{
	if (top != NULL)
	{
		return top->ptr;
	}
}

void StackClass::push(Node* newPtr)
{
	Stack *temp = top;

	//checks if the stack is null
	if (top == NULL)
	{
		top = new Stack(newPtr);
		top->prev = NULL;
	}
	else //add new top with link to previous top (temp)
	{
		top = new Stack(newPtr, temp);
	}
}

void StackClass::pop()
{
	//moves top to the next node down in the stack then deletes old top
	Stack *temp = top;
	top = top->prev;
	delete temp;
}

bool StackClass::isNull()
{
	//checks if stack is empty for underflow condition
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Node::Node()
{
	llink = NULL;
	rlink = NULL;
	bf = 0;
}

Node::Node(int newNum, Node* newrLink, Node* newlLink)
{
	num = newNum;
	rlink = newrLink;
	llink = newlLink;
	bf = 0;
}

//Professor's Balance Factor functions he said we could use
int max(int a, int b)
{

	int m = a;
	if (b > a)
		m = b;
	return m;

}

int height(Node * p)
{
	if (p == NULL)
		return 0;
	if ((p->llink == NULL) && (p->rlink == NULL))
		return 1;
	return 	1 + max(height(p->llink), height(p->rlink));
}

void Tree::balfactor(Node * p)
{
	if (p != NULL)
	{
		p->bf = height(p->llink) - height(p->rlink);
		balfactor(p->llink);
		balfactor(p->rlink);
		
			balance(root);
		
	}
}

void Tree::bfactor()
{
	if (root != NULL)
	{
		root->bf = height(root->llink) - height(root->rlink);
		balfactor(root->llink);
		balfactor(root->rlink);
	}
}
//end of Prof's functions

Tree::Tree()
{
	root = NULL;
}

bool Tree::insert(int newNum)
{
	bool dup = false;

	//if tree is empty, inserts a node as root
	if (root == NULL)
	{
		root = new Node(newNum);
	}
	else
	{
		Node *newNode = root;
		Node *temp = NULL;

		//finds where the number belongs in the tree
		while (newNode != NULL && newNode->num != newNum)
		{
			temp = newNode;
			if (newNum < newNode->num)
			{
				newNode = newNode->llink;
			}
			else
			{
				newNode = newNode->rlink;
			}
		}

		//flags duplicate data
		if (newNode != NULL)
		{
			cout << "Duplicate Data" << endl;
			dup = true;
		}
		else
		{
			//places num in proper node on the tree
			if (newNum < temp->num)
			{
				temp->llink = new Node(newNum);
			}
			else
			{
				temp->rlink = new Node(newNum);
			}
		}
	}
	//rebalances the tree
	bfactor();
	return dup; //returns whether or not the data was duplicate
}

//Root can't be set to p in the travInOrder function because it is recursive. This function gets the root to travInOrder and travPreOrder
void Tree::getRoot()
{
	if (root != NULL)
	{
		travInOrder(root);

		cout << endl << "Contents of tree (preorder):" << endl;
		travPreOrder(root);
	}
	else
	{
		cout << "Nothing in tree" << endl;
	}
}

void Tree::travInOrder(Node *p)
{
	if (p != NULL)
	{
		travInOrder(p->llink);
		cout << "Value: " << p->num << " Balance Factor: " << p->bf << endl;
		travInOrder(p->rlink);
	}
}

void Tree::travPreOrder(Node *p)
{
	StackClass stack; 
	Node *q = root;

	//solution for nonrecursive traversal is to use a stack to keep track of values in a LIFO order
loop: while (q != NULL)
{
	cout << "Value: " << q->num << " Balance Factor: " << q->bf << endl;
	stack.push(q);
	q = q->llink;
}
	if (!(stack.isNull()))
	{
		q = stack.getTop();
		stack.pop();
		q = q->rlink;
		goto loop;
	}
}

Node* Tree::findParent(Node* p)
{
	Node *found = NULL;
	OBparent = p;
	left = false;
	right = false;

	if (OBnode != NULL && OBparent != NULL)
	{
		//returns the parent link of the node that is out of balance
		//so the fixed portion of the tree can be reconnected
		if (OBparent->llink == OBnode)
		{
			left = true;
			return OBparent;
		}
		else if (OBparent->rlink == OBnode)
		{
			right = true;
			return OBparent;
		}
		//recursively searches for the parent of OBnode
		if (OBparent->llink != NULL)
		{
			return findParent(OBparent->llink);
		}
		if (OBparent->rlink != NULL)
		{
			found = findParent(OBparent->rlink);
		}
		if (found != NULL)
		{
			return found;
		}
	}
}

void Tree::balance(Node *OBnodeTemp)
{
	Node *temp1 = NULL;
	Node *temp2 = NULL;
	Node *temp3 = NULL;
	Node *p = root->llink;
	const int MAX_BAL = 2;
	const int MIN_BAL = -2;
	const int CHILD_BAL1 = 1;
	const int CHILD_BAL2 = -1;

	OBnode = OBnodeTemp; //sets OBnode to the out of balance node pass in from the balfactor function

	OBparent = findParent(root); //finds the parent of the out of balance node

	if (OBnode->bf == MAX_BAL)
	{
		if (OBnode->llink->bf == CHILD_BAL1) //LL case
		{
			//designates the children of the out of balance node currently
			OBchild = OBnode->llink;
			OBgrandchild = OBnode->llink->llink;

			if (OBnode->llink->rlink != NULL) //stores OBnode's child's right link
			{
				temp1 = OBnode->llink->rlink;
			}

			//preserves the root of the tree by rotating it and reassigning root
			if (OBnode == root)
			{
				temp2 = root;
				root = OBchild;
				root->rlink = temp2;
				temp2->llink = temp1;
			}
			else
			{
				parent = OBchild; //make child of OBnode the new parent
				parent->rlink = OBnode; //rotate OBnode right
				parent->llink = OBgrandchild; //set new parent's left link
				parent->rlink->llink = temp1; //move OBnode's child's right link to proper place

				//reconnects fixed portion of the subtree back into the original tree
				if (right && OBparent != NULL)
				{
					OBparent->rlink = parent;
				}
				else if (left && OBparent != NULL)
				{
					OBparent->llink = parent;
				}
			}
		}
		else if (OBnode->llink->bf == CHILD_BAL2) //LR case
		{
			//designates the children of the out of balance node currently
			OBchild = OBnode->llink;
			OBgrandchild = OBnode->llink->rlink;

			//stores OBnode's grandchild's subtrees
			if (OBnode->llink->rlink->llink != NULL)
			{
				temp1 = OBnode->llink->rlink->llink;
			}
			if (OBnode->llink->rlink->rlink != NULL)
			{
				temp2 = OBnode->llink->rlink->rlink;
			}

			//preserves the root of the tree by rotating it and reassigning root
			if (OBnode == root)
			{
				temp3 = root;
				root = OBgrandchild;
				root->llink = OBchild;
				root->llink->rlink = temp1;
				root->rlink = temp3;
				root->rlink->llink = temp2;
			}
			else
			{
				parent = OBgrandchild;
				parent->llink = OBchild;
				parent->rlink = OBnode;
				parent->llink->rlink = temp1;
				parent->rlink->llink = temp2;

				//reconnects fixed portion of the subtree back into the original tree
				if (right && OBparent != NULL)
				{
					OBparent->rlink = parent;
				}
				else if (left && OBparent != NULL)
				{
					OBparent->llink = parent;
				}
			}

			OBnode = NULL;
		}
		else if (OBnode->bf == MIN_BAL)
		{
			if (OBnode->rlink->bf == CHILD_BAL1) //RL case
			{
				//designates the children of the out of balance node currently
				OBchild = OBnode->rlink;
				OBgrandchild = OBnode->rlink->llink;

				//stores OBnode's grandchild's subtrees
				if (OBnode->rlink->llink->llink != NULL)
				{
					temp1 = OBnode->rlink->llink->llink;
				}
				if (OBnode->rlink->llink->rlink != NULL)
				{
					temp2 = OBnode->rlink->llink->rlink;
				}

				//preserves the root of the tree by rotating it and reassigning root
				if (OBnode == root)
				{
					temp3 = root;
					root = OBgrandchild;
					root->rlink = OBchild;
					root->rlink->llink = temp2;
					root->llink = temp3;
					root->llink->rlink = temp1;
				}
				else
				{
					parent = OBgrandchild;
					parent->rlink = OBchild;
					parent->llink = OBnode;
					parent->llink->rlink = temp1;
					parent->rlink->llink = temp2;

					//reconnects fixed portion of the subtree back into the original tree
					if (right && OBparent != NULL)
					{
						OBparent->rlink = parent;
					}
					else if (left && OBparent != NULL)
					{
						OBparent->llink = parent;
					}
				}
			}
			else if (OBnode->rlink->bf == CHILD_BAL2) //RR case
	
			{
				//designates the children of the out of balance node currently
				OBchild = OBnode->rlink;
				OBgrandchild = OBnode->rlink->rlink;

				if (OBnode->rlink->llink != NULL) //stores OBnode's child's left link
				{
					temp1 = OBnode->rlink->llink;
				}

				//preserves the root of the tree by rotating it and reassigning root
				if (OBnode == root)
				{
					temp2 = root;
					root = OBchild;
					root->llink = temp2;
					temp2->rlink = temp1;
				}
				else
				{
					parent = OBchild; //make child of OBnode the new parent
					parent->llink = OBnode; //rotate OBnode left
					parent->rlink = OBgrandchild; //set new parent's right link
					parent->llink->rlink = temp1; //move OBnode's child's left link to proper place

					//reconnects fixed portion of the subtree back into the original tree
					if (right && OBparent != NULL)
					{
						OBparent->rlink = parent;
					}
					else if (left && OBparent != NULL)
					{
						OBparent->llink = parent;
					}
				}
			}
			OBnode = NULL; //resets OBnode
		}
	}
}

int main()
{
	Tree newTree;
	ifstream infile;
	string filename;
	int newNum;

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 4: AVL Tree" << endl << endl;

	cout << "Enter valid filename: ";
	getline(cin, filename);
	infile.open(filename.c_str());
	if (infile.fail())
	{
		cout << "File error" << endl;
		system("pause");
		return 1;
	}

	cout << "Content of Data File" << endl;
	while (!infile.eof())
	{
		while (infile >> newNum) //avoids printing "Duplicate Data" twice if the last number is a duplicate
		{
			if (!newTree.insert(newNum)) //prevents number from being printed if duplicate
			{
				cout << newNum << endl;
			}
		}
	}

	cout << endl << "Contents of tree (in order):" << endl;

	newTree.getRoot(); //sends root to traversal functions that print the contents

	infile.close();
	system("pause");
	return 0;
}