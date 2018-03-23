#include"Linked.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>

using namespace std;

//default constructor
node::node()
{
	next = NULL;
}

//constructor
node::node(string src, string dest, int mileage, int cost, node* newLink)
{
	source = src;
	destination = dest;
	miles = mileage;
	costVal = cost;
	next = newLink;
	count++;
}

Flights::Flights()
{
	count = 0;
	head = NULL;
}

void Flights::newNode(string src, string dest, int mileage, int cost)
{
	node* newNode = head;
	node* temp = NULL;

	//first node
	if (head == NULL)
	{
		head = new node(src, dest, mileage, cost);
		head->next = NULL;
	}
	//second node
	else if (head->next == NULL)
	{
		newNode = new node(src, dest, mileage, cost);
		head->next = newNode;
	}
	//all other new nodes
	else
	{
		while (newNode != NULL)
		{
			temp = newNode;
			newNode = newNode->next;
		}
		newNode = new node(src, dest, mileage, cost);
		temp->next = newNode;
	}
	count++;
}

void Flights::traverse()
{
	node* newNode;
	newNode = head;
	
	//displays all linked list information stored from file
	for (int i = 0; i < count; i++)
	{
		cout << setw(4) << newNode->source << setw(7) << newNode->destination << setw(6) << newNode->miles << setw(5) << "$" << newNode->costVal << endl;
		newNode = newNode->next;
	}
}

//takes airport abbreviation and returns the associated index value
int getIndex(const vector<string> citylist, string city, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (city == citylist[i])
		{
			return i;
		}
	}
}

//fills digraph matrix with 1's for all the connections
void Flights::fillArray(const vector<string> &cityList, vector<vector<int>> &array, int arrSize)
{
	int row = arrSize;
	int col = arrSize;
	node* newNode;
	newNode = head;

	for (int i = 0; i < count; i++)
	{		
		row = getIndex(cityList, newNode->source, cityList.size());
		col = getIndex(cityList, newNode->destination, cityList.size());

		array[row][col] = 1;
		newNode = newNode->next;
	}
}

//prints digraph matrix
void printArr(vector< vector<int> > & array, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "  " << array[i][j] ;
		}
		cout << endl;
	}
}

//takes index and returns associated airport abbreviation
string getName(const vector<string> citylist, int index)
{
	return citylist[index];
}

//displays best price report data
void Flights::bestPriceReport(const vector<string> citylist, vector<int> &connections, vector<int> &pTotals, vector<int> &mTotals, int index, int size)
{
	int row = size;
	int col = size;
	string city = getName(citylist, index);
	node* newNode;
	newNode = head;

	for (int i = 0; i < connections.size(); i++)
	{
		//if -1 then there is no connection to display
		if (connections[i] != -1)
		{
			cout << city << setw(8) << getName(citylist, i) << setw(3) << "$" << pTotals[i] << setw(7) << mTotals[i] << setw(7);
			
			//if connection is the same as the orgin then the flight is direct to the destination
			if (connections[i] == index)
			{
				cout << city << setw(5) << getName(citylist, i) << setw(3) << "$" << pTotals[i] << setw(6) << mTotals[i] << endl <<
					"------ ---- ----  ------- ---------------------------------------" << endl;
			}
			else //if the connection is not -1 or the origin value then it contains the node that it's connecting to
			{
				int price;
				int miles;

				for (int j = 0; j < count; j++)
				{
					//get the price and miles for origin to connection
					if (newNode->source == city && newNode->destination == getName(citylist, connections[i]))
					{
						price = newNode->costVal;
						miles = newNode->miles;
					}
					newNode = newNode->next;
				}
				cout << city << setw(5) << getName(citylist, connections[i]) << setw(3) << "$" << price << setw(6) << miles << endl;
				
				newNode = head;
				string city1 = getName(citylist, connections[i]);
				string city2 = getName(citylist, i);
				//display connection
				for (int j = 0; j < count; j++)
				{
					//get the price and miles for connection to destination
					if (newNode->source == city1 && newNode->destination == city2)
					{
						price = newNode->costVal;
						miles = newNode->miles;
					}
					newNode = newNode->next;
				}
				newNode = head;
				cout << setw(30) << getName(citylist, connections[i]) << setw(5) << getName(citylist, i) << setw(3) << "$" << price << setw(6) << miles
					<< endl << "------ ---- ----  ------- ---------------------------------------" << endl;
			}
		}
	}	
}

int Flights::dijkstra(string weightType, vector<int> &connections, vector<int> &totals, const vector<string> &cityList, vector<vector<int>> &array, string city, int size)
{
	vector<int> d;
	vector<int> P;
	vector<int> L;
	vector<int> reachedSet;
	vector<int> J;
	int row = size;
	int col = size;
	int least = 10000;
	int index = 0;
	node* newNode;
	newNode = head;

	for (int i = 0; i < count; i++)
	{
		
		row = getIndex(cityList, newNode->source, cityList.size());
		col = getIndex(cityList, newNode->destination, cityList.size());

		if (weightType == "cost")
		{
			array[row][col] = newNode->costVal;
		}
		else
		{
			array[row][col] = newNode->miles;
		}

		newNode = newNode->next;
	}

	row = getIndex(cityList, city, cityList.size()); //row of the array that corresponds to the origin airport in the matrix

	/********STEP 1********/
	//(see Prof's "High-level description of shortest path algorithm" handout)
	//assigns starting row of array to d vector 
	for (int i = 0; i < size; i++)
	{
		d.push_back(array[row][i]);
	}

	//Set P[i] to start for all i adjacent from start
	for (int i = 0; i < d.size(); i++)
	{
		if (d[i] == -1)
		{
			P.push_back(-1);
		}
		else
		{
			P.push_back(row);
		}
	}

	//add start to reached set
	reachedSet.push_back(row);

	//create a list L of all verticess for which p[i] != -1
	for (int i = 0; i < P.size(); i++)
	{
		if (P[i] != -1)
		{
			L.push_back(i);
		}
	}

	/********STEP 2********/
	while (!L.empty())
	{
		/********STEP 3********/
		int del = 0;
		//finds the L vertex with the least d value
		for (int k = 0; k < L.size(); k++)
		{
			if (d[L[k]] < least)
			{
				least = L[k];
				del = k;
			}
		}

		//sets i to least for later use
		int I = least;
		reachedSet.push_back(I); //add i to reached set
		L.erase(L.begin() + del); //delete the vertex I from L

		/********STEP 4********/
		//push all vertices adjacent from I onto J
		for (int k = 0; k < size; k++)
		{
			if (array[I][k] != -1)
			{
				J.push_back(k);
			}
		}

		//update d[J] to min for all unreached vertices J
		while (!J.empty())
		{
			int temp1 = 10000;
			int temp2 = d[I] + array[I][J[0]];
			bool found = false;

			if (d[J[0]] != -1)
			{
				temp1 = d[J[0]];
			}

			d[J[0]] = min(temp1, temp2);
			P[J[0]] = I; //set p[J] to I

			//move on to next J
			J.erase(J.begin());
		}
	}

	connections = P; //save all connections (P) to an external vector
	totals = d; //save all total weights to external vector

	return row; //return the origin vertex we were working on
}

int main()
{
	Flights info; //hold all the flight inforamation from the file
	ifstream infile;
	string filename;
	string source; //origin of flight
	string dest; //desination of flight
	string airAbbr; //abbreviation for airport
	vector<string> cities; //list of all airports from file
	int citiesNum = 0; //number of elements in above vector
	int mileage = 0;
	int cost = 0;
	bool found = false; //flag for if the airport abbreviation is already in the cities vector

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 7: Graph" << endl << endl;

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

	while (!infile.eof())
	{
		infile >> source >> dest >> mileage >> cost;

		//adds all origin airport abbreviations once in cities list
		for (int i = 0; i < cities.size(); i++)
		{
			if (source == cities[i])
			{
				found = true;
			}
		}
		if (!found)
		{
			cities.push_back(source);
		}

		found = false;

		//adds all destination airport abbreviations once in cities list
		for (int i = 0; i < cities.size(); i++)
		{
			if (dest == cities[i])
			{
				found = true;
			}
		}
		if (!found)
		{
			cities.push_back(dest);
		}

		//creates new node with all flight informmation
		info.newNode(source, dest, mileage, cost);
	}

	//counts the total number of airport abbreviations
	for (int i = 0; i < cities.size(); i++)
	{
		citiesNum++;
	}

	int row = citiesNum;
	int col = citiesNum;
	int init = -1;

	//declaration for 2D vector
	vector< vector<int> > array;
	//resize to be n by n matrix where n is the number of airport abbreviations
	array.resize(col, vector<int>(row, init));

	//fills all connections in the digraph matrix
	info.fillArray(cities, array, citiesNum);

	//displays direct flights data
	cout << endl << "Direct Flights" << endl <<
		"Source Dest Mileage Cost" << endl <<
		"------ ---- ------  -----" << endl;
	info.traverse();

	//takes an abbreviation until quit is entered
	do
	{
		cout << endl << "Please enter a airport abbreviation or the word \"quit\" to exit: ";
		cin >> airAbbr;
		if (airAbbr != "quit")
		{
			vector<int> connections; //final resting place of all the connections found via Dijkstra's algorithm
			vector<int> pTotals; //price totals found from Dijkstras
			int origin; //origin vertex from which all connections are evaluated.
			int pos = getIndex(cities, airAbbr, cities.size()); //index associated with user input airport

			origin = info.dijkstra("cost", connections, pTotals, cities, array, airAbbr, citiesNum);

			vector<int> mTotals;
			origin = info.dijkstra("miles", connections, mTotals, cities, array, airAbbr, citiesNum);

			cout << endl << "Best Price Report		Connecting Flight Information" << endl <<
				"Source Dest Cost  Mileage  Src  Dest Cost  Mileage" << endl <<
				"------ ---- ----  ------- ---------------------------------------" << endl;
			info.bestPriceReport(cities, connections, pTotals, mTotals, origin, citiesNum);
		}
	} while (airAbbr != "quit");

	cout << endl << "Goodbye!" << endl << endl;

	infile.close();

	system("pause");
	return 0;
}