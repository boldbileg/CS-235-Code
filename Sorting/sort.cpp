#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <iostream>
#include <string>
#include <fstream> 
#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <iomanip>

using namespace std;

//makes a copy of the array to be sorted so an unsorted copy remains
void copyArray(int array[], int arrCopy[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arrCopy[i] = array[i];
	}
}

void insertion(int array[], int size, clock_t &clk, clock_t &time)
{
	int temp, j;
	clock_t start;
	clock_t end;

	start = clock();
	
	for (int i = 1; i < size; i++)
	{
		temp = array[i];
		j = i - 1;

		//moves the elements up after a swap
		while (j >= 0 && array[j] > temp)
		{
			array[j + 1] = array[j];
			j--;
		}

		//puts comparison value in proper place
		array[j + 1] = temp;
	}
	end = clock();
	clk = end - start;
	time = ((end - start) / CLK_TCK);
}

//typical swap function
void swap(int array[], int i, int j)
{
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void quickSort(int array[], int lSide, int rSide)
{
	int part;
	int pivot = array[lSide];
	int i = lSide;
	int j;

	if (lSide < rSide)
	{
		//moves values to the side of the pivot point
		for (j = lSide + 1; j < rSide; j++)
		{
			if (array[j] <= pivot)
			{
				i++;
				swap(array, i, j);
			}
		}

		swap(array, i, lSide);

		part = i; //partition position
		quickSort(array, lSide, part); //recursion for left side of the pivot
		quickSort(array, part + 1, rSide); //recursion for right side of the pivot
	}
}

void shellSort(int array[], int size, clock_t &clk, clock_t &time)
{
	clock_t start;
	clock_t end;
	const int DIVISOR = 2;

	start = clock();

	//separates the data into smaller and smaller gaps
	for (int gap = size / DIVISOR; gap > 0; gap = gap / DIVISOR)
	{
		//do insertion sort for current gap size
		for (int i = gap; i < size; i++)
		{
			//preserve the value at element i
			int temp = array[i];

			//make spot for element i by shifting sorted elements up
			int j;
			for (j = i; j >= gap && array[j - gap] > temp; j = j - gap)
			{
				array[j] = array[j - gap];
			}

			//puts value of element i into proper place in the array
			array[j] = temp;
		}
	}

	end = clock();
	clk = end - start;
	time = ((end - start) / CLK_TCK);
}

int main()
{
	int numLines = 0; //counts the number of lines for array elements
	int val;
	int fileCount = 1;
	clock_t clk1; //clock ticks for insertion sort
	clock_t clk2; //clock ticks for shell sort
	clock_t clk3; //clock ticks for quick sort
	clock_t t1; //total time for insertion sort
	clock_t t2; //total time for shell sort
	clock_t t3; //total time for quick sort
	string of1; //output file name for insertion sort
	string of2; //output file name for shell sort
	string of3; //output file name for quick sort
	string line; //dummy variable for line counter
	ifstream infile;
	ofstream outfile;
	string filename;

	cout << "Nate Bothwell" << endl << "CS 2420, Section 601" << endl << "Program 6: Sorting";

	//takes file name and exits program if file is not found or user enters Q to quit
	while (filename != "Q")
	{
		cout << endl << endl << "Enter valid filename or Q to quit: ";
		getline(cin, filename);
		infile.open(filename.c_str());
		if (infile.fail() || filename == "Q")
		{
			if (filename == "Q")
			{
				cout << endl << "Goodbye!" << endl;
			}
			else
			{
				cout << "File error" << endl;
			}
			system("pause");
			return 1;
		}

		//counts number of elements needed for array
		while (getline(infile, line))
		{
			++numLines;
		}
		infile.close();

		//reopens the file for reading
		infile.open(filename.c_str());

		int * array = NULL;
		array = new int[numLines];

		//initializes array
		for (int i = 0; i < numLines; i++)
		{
			array[i] = 0;
		}

		//stores file values in array
		for (int ind = 0; ind < numLines; ind++)
		{
			infile >> val;
			array[ind] = val;
		}

		int * arrCopy = NULL;
		arrCopy = new int[numLines];

		/***********INSERTION SORT***********/
		copyArray(array, arrCopy, numLines); //makes copy of unsorted array
		insertion(arrCopy, numLines, clk1, t1); //runs sort

		of1 = "I" + to_string(fileCount) + ".txt"; //concatenates file name with filecount number
		outfile.open(of1);

		//writes values to output file
		for (int i = 0; i < numLines; i++)
		{
			outfile << arrCopy[i] << endl;
		}
		outfile.close();

		/***********SHELL SORT***********/
		copyArray(array, arrCopy, numLines); //makes copy of unsorted array
		shellSort(arrCopy, numLines, clk2, t2); //runs sort

		of2 = "S" + to_string(fileCount) + ".txt"; //concatenates file name with filecount number
		outfile.open(of2);

		//writes values to output file
		for (int i = 0; i < numLines; i++)
		{
			outfile << arrCopy[i] << endl;
		}
		outfile.close();

		/***********QUICK SORT***********/
		copyArray(array, arrCopy, numLines); //makes copy of unsorted array

		//moved clock to outside of function because the recursion was causing problems
		clock_t start;
		clock_t end;
		start = clock();

		quickSort(arrCopy, 0, numLines); //runs sort
		
		end = clock();
		clk3 = end - start;
		t3 = ((end - start) / CLK_TCK);

		of3 = "Q" + to_string(fileCount) + ".txt"; //concatenates file name with filecount number
		outfile.open(of3);

		//writes values to output file
		for (int i = 0; i < numLines; i++)
		{
			outfile << arrCopy[i] << endl;
		}
		outfile.close();

		//Statistical output (can't get higher precision to show for sort times)
		cout << endl << "                    NUMBER    ELAPSED     ELAPSED    SORTED" << endl <<
			"  SORT      FILE#   ITEMS      CLOCK       TIME     FILE NAME" << endl <<
			"--------   ------  --------   --------   --------  ----------" << endl 
			<< "Insertion     " << fileCount << setw(11) << numLines << setw(10) << showpoint << setprecision(3) << clk1 << setw(12) << t1 << setw(11) << of1 << endl
			<< "Shellsort     " << fileCount << setw(11) << numLines << setw(10) << showpoint << setprecision(3) << clk2 << setw(12) << t2 << setw(11) << of2 << endl
			<< "Quicksort     " << fileCount << setw(11) << numLines << setw(10) << showpoint << setprecision(3) << clk3 << setw(12) << t3 << setw(11) << of3 << endl 
			<< endl;
		
		numLines = 0; //reset number of lines
		fileCount++; //keeps track of the number of files sorted for file name concatenation
		delete[] array;
		delete[] arrCopy;
		infile.close();
		cin.clear(); //clears cin buffer to read in new file name
	}
	
	system("pause");
	return 0;
}