//============================================================================
// Name        : VectorSorting.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

#include <string>



#include <fstream>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
			<< bid.fund << endl;
	return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	cout << "Loading CSV file " << csvPath << endl;

	// Define a vector data structure to hold a collection of bids.
	vector<Bid> bids;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bids.push_back(bid);
		}
	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
	}
	return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title -- DONE

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	//=======================================================
	//set low and high equal to begin and end
	// Calculate the middle element as middlePoint (int)
	// Set Pivot as middlePoint element title to compare (string)
	// while not done 
		// keep incrementing low index while bids[low].title < Pivot
		// keep decrementing high index while Pivot < bids[high].title
		/* If there are zero or one elements remaining,
			all bids are partitioned. Return high */
		// else swap the low and high bids (built in vector method)
			// move low and high closer ++low, --high
	// return high
	//=======================================================

	//defines lowerIndex and high as integers and sets them equal to begin and end
	int lowerIndex = begin;
	int biggerIndex = end;
	
	//finds the middle point of the bids vector and sets it to middlePoint
	int middlePoint = begin + (end - begin) / 2;
	string pivot = bids[middlePoint].title;

	//while loop to partition the bids vector into lowerIndex and biggerIndex
	while (lowerIndex < biggerIndex) {

		//search for the first element that is greater than the pivot
		while (bids[lowerIndex].title < pivot) {
			++lowerIndex;
		}
		//search for the first element that is less than the pivot
		while (pivot < bids[biggerIndex].title) {
			--biggerIndex;
		}

		//checks if there are zero or one elements remaining
		if (lowerIndex >= biggerIndex) {
			return biggerIndex;
		}

		//swaps the lowerIndex and biggerIndex bids
		else {
			swap(bids.at(lowerIndex), bids.at(biggerIndex));
			++lowerIndex;
			--biggerIndex;
		}
	}
	return biggerIndex;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	//=======================================================
	//set mid equal to 0
	/* Base case: If there are 1 or zero bids to sort,
	partition is already sorted otherwise if begin is greater
	than or equal to end then return*/
	/* Partition bids into low and high such that
	midpoint is location of last element in low */
	// recursively sort low partition (begin to mid)
	// recursively sort high partition (mid+1 to end)
	//=======================================================

	//defines midPoint as int and sets it to 0 as the starting index
	int midPoint = 0;

	//checks if there are 1 or zero bids to sort
	if (begin >= end) {
		return;
	}

	//sets midPoint equal to the partition function that finds the midpoint
	midPoint = partition(bids, begin, end);

	//recursively sorts the first half of the vector
	quickSort(bids, begin, midPoint);
	//recursively sorts the second half of the vector
	quickSort(bids, midPoint + 1, end);

}

// FIXME (1a): Implement the selection sort logic over bid.title -- DONE

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	//=======================================================
	//define min as int (index of the current minimum bid)
	// check size of bids vector
	// set size_t platform-neutral result equal to bids.size()
	// pos is the position within bids that divides sorted/unsorted
	// for size_t pos = 0 and less than size -1 
		// set min = pos
		// loop over remaining elements to the right of position
			// this element becomes the minimum
		// swap the current minimum with smaller one found
			// swap is a built in vector method
	//=======================================================

	//will store current minimum element
	int indexOfCurrentMinimum;
	//define totalBids as unassigned and set it equal to the size of the bids vector
	size_t totalBids = bids.size();

	//loop from start of unsorted to end of bids vector
	for (size_t smallestIndexUnsorted = 0; smallestIndexUnsorted < totalBids - 1; smallestIndexUnsorted++) {
		//set indexOfCurrentMinimum equal to the current position
		indexOfCurrentMinimum = smallestIndexUnsorted;
		
		//loop over remaining elements to the right of position
		for (size_t currentIndex = smallestIndexUnsorted + 1; currentIndex < totalBids; currentIndex++) {
			//check if the current element is less than the current minimum
			if (bids[currentIndex].title < bids[indexOfCurrentMinimum].title) {
				indexOfCurrentMinimum = currentIndex;
			}
		}

		//swap the current minimum with the smaller one found
		if (indexOfCurrentMinimum != smallestIndexUnsorted) {
			swap(bids.at(smallestIndexUnsorted), bids.at(indexOfCurrentMinimum));
		}
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	default:
		//csvPath = "CS 300 eBid_Monthly_Sales_Dec_2016.csv";
		csvPath = "CS 300 eBid_Monthly_Sales.csv";
	}

	// Define a vector to hold all the bids
	vector<Bid> bids;

	// Define a timer variable
	clock_t ticks;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Selection Sort All Bids" << endl;
		cout << "  4. Quick Sort All Bids" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			cout << endl; // for readability

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			bids = loadBids(csvPath);

			cout << bids.size() << " bids read" << endl;

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			cout << endl;

			break;

		case 2:
			cout << endl << endl; // Add extra space for readability

			// Loop and display the bids read
			for (int i = 0; i < bids.size(); ++i) {
				displayBid(bids[i]);
			}
			cout << endl; // for readability
			

			break;

		// FIXME (1b): Invoke the selection sort and report timing results -- DONE
		case 3:
			cout << endl; // for readability

			// Initialize a timer variable before sorting bids
			ticks = clock();

			// Complete the method call to selection sort
			bids = loadBids(csvPath);

			// Perform selection sorting algorithm on bid titles
			selectionSort(bids);
			
			// Display time to sort bids.size() bids
			cout << bids.size() << " bids sorted" << endl;
			ticks = clock() - ticks;
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			cout << endl; // for readability
			break;

		// FIXME (2b): Invoke the quick sort and report timing results -- DONE
		case 4:
			cout << endl; // for readability

			// Initialize a timer variable before sorting bids
			ticks = clock();
			
			// Complete the method call to quick sort
			bids = loadBids(csvPath);

			// Perform quick sorting algorithm on bid titles
			quickSort(bids, 0, bids.size() - 1);

			// Display time to sort bids.size() bids
			cout << bids.size() << " bids sorted" << endl;
			ticks = clock() - ticks;
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			cout << endl; // readability

			break;
		}
	
	}

	cout << "Good bye." << endl;

	return 0;
}
