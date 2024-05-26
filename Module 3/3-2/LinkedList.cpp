//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 3-2 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

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
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

    private:
        //Internal structure for list entries, housekeeping variables
        struct Node {
            Bid bid;
            Node *next;

            // default constructor
            Node() {
                next = nullptr;
            }

            // initialize with a bid
            Node(Bid aBid) {
                bid = aBid;
                next = nullptr;
            }
        };

        Node* head;
        Node* tail;
        int size = 0;

    public:
        LinkedList();
        virtual ~LinkedList();
        void Append(Bid bid);
        void Prepend(Bid bid);
        void PrintList();
        void Remove(string bidId);
        Bid Search(string bidId);
        int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to nullptr
    head = nullptr;
    tail = nullptr;

}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (2): Implement append logic
    //Create new node
    //if there is nothing at the head...
            // new node becomes the head and the tail
    //else
        // make current tail node point to the new node
        // and tail becomes the new node
    //increase size count

    // Define a new node in the linked list
    Node *newNode = new Node(bid);

    // Linked list is empty, newNode must be head and tail
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    // Linked list is not empty, add newNode to the end of the list
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (3): Implement prepend logic
    // Create new node

    // if there is already something at the head...
        // new node points to current head as its next node

    // head now becomes the new node
    //increase size count

    // Define a new node in the linked list
    Node *newNode = new Node(bid);

    // Point newNode to the current head node
    if (head != nullptr) {
        newNode->next = head;
    }
    // Define the new node as the head of the linked list
    head = newNode;
    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (4): Implement print logic
    // start at the head

    // while loop over each node looking for a match
        //output current bidID, title, amount and fund
        //set current equal to next
    
    // Start at the head of the list
    Node *current = head;
    
    // current is a temporary node that will be used to traverse the linked list
    while (current != nullptr) { // Traversing the linked list with "head" would lose the reference to the head node
        // Output the bid information of the current node
        cout << current->bid.bidId << ": "
             << current->bid.title << " | "
             << current->bid.amount << " | "
             << current->bid.fund << endl;
        // Move to the next node
        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (5): Implement remove logic
    // special case if matching node is the head
        // make head point to the next node in the list
        //decrease size count
        //return

    // start at the head
    // while loop over each node looking for a match
        // if the next node bidID is equal to the current bidID
        	// hold onto the next node temporarily
            // make current node point beyond the next node
            // now free up memory held by temp
            // decrease size count
            //return

        // current node is equal to next node

    // Special case if the matching node is the head    
    if (bidId == head->bid.bidId) {
        head = head->next; // move the head to the next node
        size--;
        return;
    }

    Node *current = head; // Start at the head of the list
    while (current->next != nullptr) { // Traverse the linked list
        if (current->next->bid.bidId == bidId) { // If the next node bidID is equal to the current bidID
            Node *tempNode = current->next; // Without this, data pointed to by current->next will be lost causing a memory leak
            current->next = current->next->next; // Assign the next node to the node after it
            delete tempNode; // Deletes the orphan node
            size--;
            return;
        }

        current = current->next; // Move to the next node
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (6): Implement search logic

    // special case if matching bid is the head

    // start at the head of the list

    // keep searching until end reached with while loop (current != nullptr)
        // if the current node matches, return current bid
        // else current node is equal to next node

    //(the next two statements will only execute if search item is not found)
        //create new empty bid
        //return empty bid

    Node *current = head; // Start at the head of the list

    if (current->bid.bidId == bidId) { // Special case if the matching bid is the head
        return head->bid;
    }
    else {
        while (current != nullptr) { // Traverse the linked list
            if (current->bid.bidId == bidId) { // If the current node matches, return the current bid
                return current->bid;
            }
            current = current->next; // Move to the next node
        }
    }
    
    // Accessible only if the search item is not found
    Bid emptyBid;
    return emptyBid; // Return an empty bid if the search item is not found
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
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
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath //= "CS 300 eBid_Monthly_Sales_Dec_2016.csv"; // 76 entries
                = "CS 300 eBid_Monthly_Sales.csv"; // 12023 entries
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
