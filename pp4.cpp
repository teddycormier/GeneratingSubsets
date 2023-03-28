#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <array>

// g++ -std=c++11 -o pp4 pp4.cpp
using namespace std;

void printCharArray(char array[], int r);					  // prints the r-subset
void printArray(string headerMessage, char s1[], int length); // fancy print of a rsubset

int findIndexInAlphabet(char letter, char alpha[]);					// finds the index in the alphabet for a letter, you complete this
void findRsubsetsChar(char array[], char arrayMax[], int n, int r); // finds the next rsubset, you complete this

int combination(int n, int r); // computes C(n,r)
long long fact(int n);		   // Returns factorial of n

int n, r;
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


int main()
{
	char c;
	int difference; // this quantity is REALLY useful...

	int length = end(alphabet) - begin(alphabet);

	printArray("these are the elements in the alphabet", alphabet, length);
	cout << "Enter a value for n: ";
	cin >> n;
	cout << "Enter a value for r: ";
	cin >> r;

	difference = n - r; // this quantity is REALLY useful...

	char arraySubsets[r]; // this will hold your r-subsets
	char arrayMax[r];

	int comb = combination(n, r);

	// Fills the array with {a,b,c,..,j}, the smallest r-subset
	for (int i = 0; i < r; i++)
	{
		arraySubsets[i] = alphabet[i];
	}

	// Fills the maxArray with the largest r-subset
	for (int i = difference; i < n; i++)
	{
		arrayMax[i - difference] = alphabet[i];
	}

	printArray("Max array is     ", arrayMax, r);
	printArray("Smallest array is", arraySubsets, r);

	cout << "There are " << comb;
	cout << " r-subsets, and here they are:\n";
	cout << "-----------------" << endl;
	printCharArray(arraySubsets, r); // prints the first r-subset (which is the smallest)

	for (int i = 1; i < comb; i++) // this calls the function to find the next r-subset
	{
		findRsubsetsChar(arraySubsets, arrayMax, n, r);
	}
	cout << "-----------------" << endl;
	return 0;
}

void findRsubsetsChar(char array[], char arrayMax[], int n, int r)
{
	// Initialize arrayMax to contain the largest r elements of alphabet
	for (
		int i = n - r, j = 0; i < n; i++, j++)
	{
		arrayMax[j] = alphabet[i];
	}
	// loop backwards to find the first element that can be incremented
	int i = r - 1;
	while (i >= 0 && array[i] == arrayMax[i])
	{
		i--;
	}

	// if all elements have been incremented, we are done
	if (i < 0)
	{
		return;
	}

	// increment the element at index i
	int index = findIndexInAlphabet(array[i], alphabet);
	array[i] = alphabet[index + 1];

	// update the rest of the elements to the right
	for (int j = i + 1; j < r; j++)
	{
		array[j] = alphabet[findIndexInAlphabet(array[j - 1], alphabet) + 1];
	}

	printCharArray(array, r);
}

int findIndexInAlphabet(char letter, char alpha[])
{
	for (int i = 0; i < 26; i++)
	{
		if (alpha[i] == letter)
		{
			return i;
		}
	}
	return -1; // letter not found
}

void printCharArray(char array[], int r)
{	
	for (int i = 0; i < r; i++)
	{
		cout << array[i] << "       ";
	}
	cout << endl;
}

int combination(int n, int r)
{
	return fact(n) / (fact(r) * fact(n - r));
}

long long fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return n * fact(n - 1);
	}
}


void printArray(string headerMessage, char s1[], int length)
{
	cout << headerMessage << ":\t";
	cout << "{";
	for (int index = 0; index < length; index++)
	{
		cout << s1[index]; // << " ";
	}
	cout << "}" << endl;
}