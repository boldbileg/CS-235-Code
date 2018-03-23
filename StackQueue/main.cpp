#include "Header.h"
#include <iostream>
#include <string>
#include <fstream>

Stack::Stack()
{
	prev = NULL;
}

Stack::Stack(int newNum, Stack *newLink)
{
	prev = newLink;
	val = newNum;
}

StackClass::StackClass()
{
	top = NULL;
}

void StackClass::push(int newNum)
{
	Stack *temp = top;

	//checks if the stack is null
	if (top == NULL)
	{
		top = new Stack(newNum);
		top->prev = NULL;
	}
	else //add new top with link to previous top (temp)
	{
		top = new Stack(newNum, temp);
	}
}

void StackClass::pop()
{
	//moves top to the next node down in the stack then deletes old top
	Stack *temp = top;
	top = top->prev;
	delete temp;
}

void StackClass::travPrt(void(*print)(Stack*))
{
	//traverses the linked list and prints values
	Stack *newNode = top;
	while (newNode != NULL)
	{
		(*print)(newNode);
		newNode = newNode->prev;
	}
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

void print(Stack *p)
{
	cout << p->val << endl;
}

Queue::Queue()
{
	next = NULL;
}

Queue::Queue(int newNum, Queue *nextLink)
{
	val = newNum;
	next = nextLink;
}

QueueClass::QueueClass()
{
	front = NULL;
	rear = NULL;
}

void QueueClass::append(int newNum)
{
	Queue *temp = rear;

	//adds node to empty queue
	if (front == NULL)
	{
		front = new Queue(newNum);
	}
	//adds second node and connects front to rear
	else if (front->next == NULL)
	{
		rear = new Queue(newNum);
		front->next = rear;
	}
	//adds node and moves rear
	else
	{
		rear = new Queue(newNum);
		temp->next = rear;
	}
}

void QueueClass::serve()
{
	//moves front one toward rear and deletes old front
	Queue *temp = front;
	front = front->next;
	delete temp;
}

bool QueueClass::frontNull()
{
	//checks if queue is empty for underflow
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void QueueClass::travPrint(void(*print)(Queue*))
{
	//traverses queue and prints values
	Queue* newNode = front;
	while (newNode != NULL)
	{
		(*print)(newNode);
		newNode = newNode->next;
	}
}

void print(Queue *p)
{
	cout << p->val << endl;
}

using namespace std;

int main()
{
	StackClass stack1;
	QueueClass queue1;
	ifstream infile;
	string filename;
	string command;
	int newNum;
	const int SPACES_1 = 10;
	const int SPACES_2 = 100;
	const int SPACES_3 = 1000;

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 3: Stacks and Queues" << endl << endl;

	//takes file name and exits program if file is not found
	cout << "Enter valid filename: ";
	getline(cin, filename);
	infile.open(filename.c_str());
	if (infile.fail())
	{
		cout << "File error" << endl;
		system("pause");
		return 1;
	}

	//beginning of output format
	cout << endl << "Operation Stack value  Result" << endl;

	while (!infile.eof())
	{
		//reads first command in file
		infile >> command;

		if (command == "push")
		{
			//takes value associated with command
			infile >> newNum;

			//output format continued
			cout << command << "      " << stack1.typeName << " " << newNum;
			
			//padding for number of decimals to make output look better
			if (newNum < SPACES_1)
			{
				cout << "      ";
			}
			else if (newNum >= SPACES_1 && newNum < SPACES_2)
			{
				cout << "     ";
			}
			else if (newNum >= SPACES_2 && newNum < SPACES_3)
			{
				cout << "    ";
			}
			else
			{
				cout << "   ";
			}
			
			//last of output format
			cout << "success" << endl;

			//perform command
			stack1.push(newNum);
		}
		else if (command == "pop")
		{
			//output format continued
			cout << command << "       " << stack1.typeName << " ---    ";

			//handles if queue is empty prior to pop command
			if (stack1.isNull())
			{
				cout << "underflow" << endl;
			}
			else
			{
				cout << "success" << endl;
				//if stack is not empty, performs pop
				stack1.pop();
			}
		}
		else if (command == "append")
		{
			//takes value associated with command
			infile >> newNum;

			//output format continued
			cout << command << "    " << queue1.typeName << " " << newNum;

			//padding for number of decimals to make output look better
			if (newNum < SPACES_1)
			{
				cout << "      ";
			}
			else if (newNum >= SPACES_1 && newNum < SPACES_2)
			{
				cout << "     ";
			}
			else if (newNum >= SPACES_2 && newNum < SPACES_3)
			{
				cout << "    ";
			}
			else
			{
				cout << "   ";
			}

			//last of output format
			cout << "success" << endl;

			//perform command
			queue1.append(newNum);
		}
		else if (command == "serve")
		{
			//output format continued
			cout << command << "     " << queue1.typeName << " ---    ";

			//handles if queue is empty prior to serve command
			if (queue1.frontNull())
			{
				cout << "underflow" << endl;
			}
			else
			{
				cout << "success" << endl;
				//if stack is not empty, performs serve
				queue1.serve();
			}
		}
		//if command is mispelled or garbage, program will output error message and exit
		else
		{
			cout << endl << "command \"" << command <<"\" not found" << endl << endl;
			system("pause");
			return 1;
		}
	}

	//print contents of stack
	cout << endl << "Stack" << endl;
	stack1.travPrt(print);

	//print contents of queue
	cout << endl << "Queue" << endl;
	queue1.travPrint(print);
	cout << endl;

	infile.close();

	system("pause");
	return 0;
}