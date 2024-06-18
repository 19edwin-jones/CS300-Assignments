#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>

#include <thread>
#include <chrono>

using namespace std;

struct CourseInfo {
    string code;
    string name;
    vector<string> prerequisites;
};
struct Node {
    CourseInfo course; 
    Node *left;
    Node *right;

    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(CourseInfo course) : Node() {
        this->course = course;
    }
};


class BinarySearchTree {
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    CourseInfo Search(string code);
    void Insert(CourseInfo course);
    void ValidateData();
    bool CheckIfRepeated(CourseInfo course);
private:
    Node *root;

    void addNode(Node *node, CourseInfo course);
    void inOrder(Node *node); //prints in order
    void validateData(Node *node);
    bool checkIfRepeated(CourseInfo course);
};


BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}


BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node

    while (root != nullptr) { // starting from root, traverse down left-most node until leaf node found
        Node *current = root; // alias of root to work with to maintain root as reference
        // improve readability by using bool flags to track search status
        bool foundLeft = true;
        bool foundRight = true;

        while (foundLeft || foundRight){ // current node is not a leaf node
            if (current->left != nullptr) { // only check for left node until no left node found
                current = current->left;
                continue;
            }
            foundLeft = false; // found no left node
            if (current->right != nullptr) { // check for right node
                current = current->right;
                continue;
            }
            foundRight = false; // no right node
        }
        delete current; // found leaf node, delete it
    }
}


void BinarySearchTree::InOrder() {
    inOrder(root);
}


CourseInfo BinarySearchTree::Search(string code) {
    Node *current = root;

    while (current != nullptr) {
        if (current->course.code == code) { // node's code matches search code
            return current->course;
        }
        else if (current->course.code > code) { // node's code is larger than search code
            current = current->left;
        }
        else { // node's code is smaller than search code
            current = current->right; 
        }
    }
    // can only be reached if course not found, otherwise this won't run
    CourseInfo course; // create an empty course
    return course;
}


void BinarySearchTree::Insert(CourseInfo course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}


void BinarySearchTree::ValidateData() {
    validateData(root);
}


bool BinarySearchTree::CheckIfRepeated(CourseInfo course) {
    return checkIfRepeated(course);
}


void BinarySearchTree::addNode(Node *node, CourseInfo course) {
    Node *current = node;
    while (current != nullptr) {
        // node's code is larger than search code
        if (current->course.code > course.code) {
            if (current->left == nullptr) {
                current->left = new Node(course);
                return; // found the location to insert the course
            }
            else {
                current = current->left; // restart search from that present left node
            }
        }
        // node's code is smaller than search code
        else {
            if (current->right == nullptr) {
                current->right = new Node(course);
                return; // found the location to insert the course
            }
            else {
                current = current->right; // restart search from that present right node
            }
        }
    }
}


void BinarySearchTree::inOrder(Node *node) {
    const int NUM_CHARS = 41;
    if (node != nullptr) {
        inOrder(node->left);

        // Output formatted course information
        cout << "\n\u2502 Course code: " << node->course.code << endl; // Unicode: u2502='┊'
        cout << "\u2502 Course name: " << node->course.name << endl; // Unicode: u2502='┊'
        cout << "\u2502 Prerequisites: "; // Unicode: u2502='┊'
        for (string prereq : node->course.prerequisites) {
            //check if prereq is the last element in the vector for formatting
            if (prereq == node->course.prerequisites.back()) {
                cout << prereq;
            }
            else {
                cout << prereq << ", ";
            }
        }
        cout << "\n\u251C"; // Unicode: u251c='├'
        for (int i = 0; i < NUM_CHARS; ++i) {
            cout << "\u2500"; // Unicode: u2500='─'
        }

        inOrder(node->right);
    }
}


// Validates data by traversing the tree in order and then searching the tree for each prerequisite
void BinarySearchTree::validateData(Node *node) {
    const int NUM_CHARS = 41;
    if (node != nullptr) {
        validateData(node->left); 

        // Output formatted course information
        if (node->course.prerequisites.size() != 0) {
            cout << "\u2502 Validating " << node->course.code << "'s prerequisites..." << endl; // Unicode: u2502='┊'
        }
        else {
            cout << "\u2502 No prerequisites for course " << node->course.code << endl; // Unicode: u2502='┊'
        }
        int currLoop = 1; // tracks the current loop iteration for formatting
        int numPrereqs = node->course.prerequisites.size();

        // Output formatted course prerequisites
        for (string prereq : node->course.prerequisites) {

            // Search for the prerequisite in the tree
            if (Search(prereq).code.empty()) {
                // Formats the output with a horizontal line
                cout << "\u251C"; // Unicode: u251c='├'
                for (int i = 0; i < NUM_CHARS; ++i) {
                    cout << "\u2500"; // Unicode: u2500='─'
                }
                cout << endl;
                cout << ("Prerequisite not found. Invalid data.\n");
                cout << "Exiting...\n";

                exit(1);
            }

            if (prereq.length() == 0 || !any_of(prereq.begin(), prereq.end(), ::isalnum)) {
                continue;
            }
            // Handles output formatting for the last prerequisite
            if (currLoop != numPrereqs && numPrereqs > 1) {
                cout << "\u2502" << string(14,' ') << "\u251C\u2500"<< prereq << "\u2500"; // Unicode: u251c='├' \u2500='─'
            }
            else if ((currLoop == 0 && numPrereqs == 1) || currLoop == numPrereqs) {
                cout << "\u2502" << string(14,' ') << "\u2514\u2500"<< prereq << "\u2500"; // Unicode: u2502='\u2502' u2514='└' u2500='─'
            }

            cout << "valid course" << endl;
            currLoop++;
        }
        // Formats the output with a horizontal line
        cout << "\u251C"; // Unicode: u251c='├'
        for (int i = 0; i < NUM_CHARS; ++i) {
            cout << "\u2500"; // Unicode: u2500='─'
        }
        cout << endl;

        validateData(node->right);
    }
}


bool BinarySearchTree::checkIfRepeated(CourseInfo aCourse) {
    CourseInfo course = Search(aCourse.code);
    if (course.code.empty() == false) {
        return true;
    }
    return false;
}


int loadInfo(string csvFile, BinarySearchTree *bst) {
    int numEntries = 0;
    // Open file
    ifstream file(csvFile);
    if (!file.is_open()){
        throw runtime_error("Could not open file");
    }
    // Read file line by line
    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        //adds comma to end of line if it doesn't exist for parsing
        if (line.back() != ',') {
            line += ',';
        }

        // Line parsing variables
        vector<string> tokens;
        stringstream ss(line);
        string token;

        // Parse line into tokens
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() < 2) {
            throw runtime_error("Invalid number of columns, minimum 2 columns required");
        }
        CourseInfo course;
        course.code = tokens[0];
        course.name = tokens[1];
        for (int i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        //check if course is repeated, prevents duplicates and loading same file multiple times
        if (bst->CheckIfRepeated(course)) {
            continue;
        }

        // Insert course into BST
        bst->Insert(course);

        numEntries++;
    }
    file.close();
    return numEntries;
}


void printSearchResults(CourseInfo course) {
    const int NUM_CHARS_TOP = 29;
    const int NUM_CHARS_BOTTOM = 41;
    if (!course.code.empty()) {
        // Formatting for the first line of box
        cout << "Found!\n";
        cout << "\u250C"; // Unicode: u250C='┌'
        for (int i = 0; i < NUM_CHARS_TOP; ++i) {
            if (i==1) {cout << "Course\u2500Info";}
            cout << "\u2500"; // Unicode: u2500='─'
        }
        cout << endl;

        // Formatting for the content of the box
        cout << "\u2502 Code: " << course.code << endl; // Unicode: u2502='┊'
        cout << "\u2502 Name: " << course.name << endl; // Unicode: u2502='┊'
        cout << "\u2502 Prerequisite(s): "; // Unicode: u2502='┊'
        for (string prereq : course.prerequisites) {
            //check if prereq is empty
            if (prereq.length() == 0) {
                continue;
            }
            //add comma if prereq is not the last element in the vector
            if (prereq == course.prerequisites.back()) {
                cout << prereq;
            }
            else {
                cout << prereq << ", ";
            }
        }
        cout << endl;

        // Formatting for the last line of the box
        cout << "\u2514"; // Unicode: u2514='└'
        for (int i = 0; i < NUM_CHARS_BOTTOM; ++i) {
            cout << "\u2500"; // Unicode: u2500='─'
        }
        cout << endl;
    } 
    else {
        cout << "\nNo results found.\n";
    }
}


void clearPrevOutput() {
    std::cout << "\0338"; // ANSI escape code to restore cursor position
    cout << "\033[J"; // ANSI escape code to clear screen
}


int main() {
    clock_t ticks;
    int numEntries;
    string searchName;
    string csvFile = "courses.csv";
    BinarySearchTree *bst= new BinarySearchTree();
    CourseInfo course;

    cout << "\u250C"; for (int i=0; i<40; i++){cout << "\u2500";} cout << "\u2510" << endl; // Unicode: u250C='┌' u2500='─' u2510='┐'
    cout << "\u2502Welcome to the Course Information System\u2502\n";
    cout << "\u2514"; for (int i=0; i<40; i++){cout << "\u2500";} cout << "\u2518" << endl; // Unicode: u250C='┌' u2500='─' u2518='┘'

    int userChoice = 0;
    cout << "\0337"; // ANSI escape code to save cursor position
    while (userChoice != 9) {
        // Display menu
        cout << endl;
        for (int i=0; i<10; i++){cout << "\u2500";} // Unicode: u2500='─'
        cout << "Please enter an option";
        for (int i=0; i<10; i++){cout << "\u2500";} // Unicode: u2500='─'
        cout << "\n1. Load CSV file" << endl;
        cout << "2. Search using course code" << endl;
        cout << "3. Sort in order by course code" << endl;
        cout << "9. Quit" << endl;
        cout << "Enter choice: ";
        cin >> userChoice;

        // Delete lines prior to user input
        clearPrevOutput();

        // Process user choice
        switch (userChoice) {
            // Load CSV file
            case 1:
                cout << "\nLoading CSV file...\n";
                ticks = clock();
                numEntries = loadInfo(csvFile, bst);
                ticks = clock() - ticks;
                printf("%d new entries loaded.\n", numEntries);
                printf("Loaded CSV file in %5f seconds.\n", (clock() - ticks)*1.0/CLOCKS_PER_SEC);

                // validate data after loading
                cout << "\n\nValidating courses...\n";
                
                this_thread::sleep_for(chrono::milliseconds(1500)); // pause for 1.5 seconds

                cout << "\u250C"; for (int i=0; i<41; i++){cout << "\u2500";} cout << endl; // Unicode: u250C='┌' u2500='─'
                ticks = clock();
                bst->ValidateData();
                ticks = clock() - ticks;
                printf("Validated courses %5f seconds.\n", (clock() - ticks)*1.0/CLOCKS_PER_SEC);
                break;
            // Search using course code
            case 2:
                cout << endl << "Please enter a code to Search: \n";
                cin >> searchName;
                clearPrevOutput();

                printf("\nSearching for \"%s\"...", searchName.c_str());
                ticks = clock();
                course = bst->Search(searchName);
                ticks = clock() - ticks;
                printSearchResults(course);
                printf("Search took %5f seconds.\n", (clock() - ticks)*1.0/CLOCKS_PER_SEC);
                break;
            // Sort in order by course code
            case 3:
                cout << "Printing all data...\n";
                ticks = clock();
                bst->InOrder();
                printf("Courses sorted %5f seconds.\n", (clock() - ticks)*1.0/CLOCKS_PER_SEC);
                break;
        }
    }
    return 0;
}