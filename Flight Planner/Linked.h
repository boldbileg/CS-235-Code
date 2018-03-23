#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct node
{
	string source; //flight origin
	string destination; //flight destination
	int miles; // miles from origin to destination
	int costVal; //value for the cost of the flight
	int count = 0; //counts number of nodes
	node* next;
	node();
	node(string src, string dest, int mileage, int cost, node* newLink = NULL);
};

class Flights
{
private:
	node* head;
public:
	int count; //counts total nodes
	Flights(); // constructor
	void traverse(); //traverse and print contents of linked list
	void fillArray(const vector<string> &cityList, vector<vector<int>> &array, int arrSize); //fills digraph matrix with 1's for all the connections
	void newNode(string src, string dest, int mileage, int cost); //function to add nodes
	int dijkstra(string weightType, vector<int> &connections, vector<int> &totals, const vector<string> &cityList, vector<vector<int>> &array, string city, int size); //Dijkstra's Algorithm
	void bestPriceReport(const vector<string> citylist, vector<int> &connections, vector<int> &pTotals, vector<int> &mTotals, int index, int size); //displays best pricing data
};