#include <iostream> 
#include <fstream> // file I/O for reading CSV file
#include <vector> 
#include <string> 
#include <algorithm> // transform() for case-insensitive search
#include <time.h> // clock() for timing
#include <sstream> // stringstream for parsing

#include <thread> // for sleep_for function 
#include <chrono> // for milliseconds

//Last compiled successfully on June 23, 2024
//Last tested successfully on June 23, 2024
//Compiled and tested using: C++17 and gcc-14 (Homebrew GCC 14.1.0_1) 14.1.0

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
    void ValidateData(bool printLog);
    bool CheckIfRepeated(CourseInfo course);
private:
    Node *root;

    void bstDeconstructor(Node *node);
    void addNode(Node *node, CourseInfo course);
    void inOrder(Node *node); //prints in order
    void validateData(Node *node, bool printLog);
    bool checkIfRepeated(CourseInfo course);

};


BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}



BinarySearchTree::~BinarySearchTree() {
    bstDeconstructor(root);
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


void BinarySearchTree::ValidateData(bool printLog) {
    validateData(root, printLog);
}


bool BinarySearchTree::CheckIfRepeated(CourseInfo course) {
    return checkIfRepeated(course);
}


// Recursive function to delete all nodes in the tree
void BinarySearchTree::bstDeconstructor(Node *node) {
    if (node != nullptr) {
        bstDeconstructor(node->left);
        bstDeconstructor(node->right);
        delete node;
    }
}

// Recursive function to add a node to the tree
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

// Recursive function to print the tree in order (least to greatest)
void BinarySearchTree::inOrder(Node *node) {
    const int NUM_CHARS = 41;
    if (node != nullptr) {
        inOrder(node->left);

        // Output formatted course information
        cout << "\n│ Course code: " << node->course.code << endl; // Unicode: '│'=u2502
        cout << "│ Course name: " << node->course.name << endl; // Unicode: '│'=u2502
        cout << "│ Prerequisites: "; // Unicode: '│'=u2502
        for (string prereq : node->course.prerequisites) {
            //check if prereq is the last element in the vector for formatting
            if (prereq == node->course.prerequisites.back()) {
                cout << prereq;
            }
            else {
                cout << prereq << ", ";
            }
        }
        cout << "\n├─────────────────────────────────────────";

        inOrder(node->right);
    }
}


// Validates data by traversing the tree in order and then searching the tree for each prerequisite
void BinarySearchTree::validateData(Node *node, bool printLog) {
    // Will not print any output if printLog is false, will only output for invalid prerequisites
    if (!printLog) {
        if (node != nullptr) {
            validateData(node->left, printLog);
            for (string prereq : node->course.prerequisites) {
                if (Search(prereq).code.empty()) {
                    cout << "Prerequisite " << prereq << " not listed as course.\nExiting...\n";
                    exit(1);
                }
            }
            validateData(node->right, printLog);
        }
        return;
    }

    // More verbose output for validation
    if (node != nullptr) {
        validateData(node->left, printLog);

        // Output formatted course information
        if (node->course.prerequisites.size() != 0) {
            cout << "│ Validating " << node->course.code << "'s prerequisites..." << endl; // Unicode: '│'=u2502
        }
        else {
            cout << "│ No prerequisites for course " << node->course.code << endl; // Unicode: '│'=u2502
        }
        int currLoop = 1; // tracks the current loop iteration for formatting
        int numPrereqs = node->course.prerequisites.size();

        // Output formatted course prerequisites
        for (string prereq : node->course.prerequisites) {

            // Search for the prerequisite in the tree
            if (Search(prereq).code.empty()) {
                // Formats the output with a horizontal line
                cout << "├─────────────────────────────────────────\n"; // Unicode: '├'=u251C
                printf("└─ Prerequisite %s not listed as course.\nExiting...\n", prereq.c_str());

                exit(1);
            }

            if (prereq.length() == 0 || !any_of(prereq.begin(), prereq.end(), ::isalnum)) {
                continue;
            }
            // Handles output formatting for the last prerequisite
            if (currLoop != numPrereqs && numPrereqs > 1) {
                cout << "│" << string(14,' ') << "├─"<< prereq << "─"; // Unicode: '│'=u2502 u251c='├' \u2500='─'
            }
            else if ((currLoop == 0 && numPrereqs == 1) || currLoop == numPrereqs) {
                cout << "│" << string(14,' ') << "└─"<< prereq << "─"; // Unicode: '│'=u2502 '─'=u2500 '└'=u2514
            }

            cout << "valid course" << endl;
            currLoop++;
        }

        cout << "├─────────────────────────────────────────\n"; // Unicode: '├'=u251C '─'=u2500

        validateData(node->right, printLog);
    }
}


// Checks if a course is already in the tree
bool BinarySearchTree::checkIfRepeated(CourseInfo aCourse) {
    CourseInfo course = Search(aCourse.code);
    if (course.code.empty() == false) {
        return true;
    }
    return false;
}


// Load course information from a CSV file into the BST
int loadInfo(string csvFile, BinarySearchTree *bst) {
    int numEntries = 0;
    // Open file
    ifstream file(csvFile);
    if (!file.is_open()){
        throw runtime_error("\nCould not open file");
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
        // Tokens 0 and 1 are course code and name respectively
        course.code = tokens[0];
        course.name = tokens[1];
        // Tokens 2 and onwards are prerequisites
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


// Print search results in a box format
void printSearchResults(CourseInfo course) {
    const int NUM_CHARS_TOP = 30;
    const int NUM_CHARS_BOTTOM = 41;
    if (!course.code.empty()) {
        // Formatting for the first line of box
        cout << "Found!\n";
        cout << "┌─Course─Info─────────────────────────────"; // Unicode: '┌'=u250C '─'=u2500
        cout << endl;

        // Formatting for the content of the box
        cout << "│ Code: " << course.code << endl; // Unicode: '│'=u2502
        cout << "│ Name: " << course.name << endl; // Unicode: '│'=u2502
        cout << "│ Prerequisite(s): "; // Unicode: '│'=u2502
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
        cout << "└─────────────────────────────────────────"; // Unicode: '└'=u2514 '─'=u2500
        cout << endl;
    }
    else {
        cout << "\nNo results found.\n";
    }
}


// ANSI escape codes for cursor position
void cursorPos(string cursorPos = "start") {
    if (cursorPos == "start") {
        cout << "\0337"; // ANSI escape code to save cursor position
    }
    else if (cursorPos == "delete") { // delete lines up to where the cursor was saved
        cout << "\0338"; // ANSI escape code to restore cursor position
        cout << "\033[J"; // ANSI escape code to clear screen
    }
}


    /*
    ANSI color codes(from https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
    30: Black
    31: Red
    32: Green
    33: Yellow
    34: Blue
    35: Magenta1
    36: Cyan
    37: White
    @param text: text to color
    @param color: ANSI escape code for color
    */
void colorText(string text, int color) {
    printf("\x1b[1m\x1b[%dm%s\x1b[0m\n", color, text.c_str()); // ANSI escape codes to change text color then reset
}


// Function to delay execution and print periods
void delayExecution(string message, int numPeriods = 3) {
    int delayTime = 1000/3 * numPeriods; // third of a second delay to print each period
    cout << endl << message << flush;
    for (int i=0; i<numPeriods; i++) {;
        cout << "." << flush;
        this_thread::sleep_for(chrono::milliseconds(delayTime));
    }
    cout << endl;
}


void printMenu() {
    cout << "──────────Please select an option──────────" << endl;  // Unicode: '─'=u2500
    cout << "1. Load CSV file" << endl;
    cout << "2. Search using course code" << endl;
    cout << "3. Sort in order by course code" << endl;
    cout << "4. Change CSV file" << endl;
    cout << "9. Quit" << endl;
    cout << "Enter choice[1-4/9]: \n❯ ";
}

int main() {
    if (__cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";
    
    // Valid user choices
    int validChoices[] = {1, 2, 3, 4, 9};
    // For logging purposes
    clock_t ticks;
    int numEntries;
    bool printLog = false;
    // User input variables
    string searchName;
    string csvFile;
    string fileExtension = ".csv";
    // Create data structure
    BinarySearchTree *bst= new BinarySearchTree();
    CourseInfo course;

    // Display welcome message
    cout << "┌────────────────────────────────────────┐" << endl; // Unicode: '┌'=u250C '─'=u2500 '┐'=u2510
    cout << "│Welcome to the Course Information System│\n"; // Unicode: '│'=u2502
    cout << "└────────────────────────────────────────┘" << endl; // Unicode: u2514= '─'=u2500 '┘'=u2518

    cursorPos(); // Save cursor position
    
    cout << "To begin, please enter the name of the CSV file: \n❯ "; // Unicode: '❯'=u276F
    cin >> csvFile;

    cursorPos("delete"); // Delete previous lines

    int userChoice = 0;

    cursorPos();
    cout << flush;
    //Enter main menu loop
    while (userChoice != 9) {

        //check if '.csv' is in the file name
        if (csvFile.find(fileExtension) == string::npos) {
            csvFile += fileExtension;
        }

        cout << "\n\nCurrent working CSV file: ";
        colorText(csvFile, 32); // Makes output green

        printMenu();
        cin >> userChoice;

        // Check if user input is valid
        if (find(begin(validChoices), end(validChoices), userChoice) == end(validChoices) || cin.fail()) {
            // Clear cin buffer and ignore invalid input
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cursorPos("delete");
            cout << endl << endl;
            cout << "==========================================\n"; 
            cout << "Invalid input. Please enter a valid choice" << endl;
            cout << "==========================================\n";
            continue;
        }

        cursorPos("delete");
        
        // Process user choice
        switch (userChoice) {
            // Load CSV file
            case 1:
                cout << "\n\nLoading CSV file...\n";

                ticks = clock();
                numEntries = loadInfo(csvFile, bst);
                ticks = clock() - ticks;

                printf("%d new entries loaded.\n", numEntries);
                printf("Loaded CSV file in %5f seconds.\n\n", (clock() - ticks)*1.0/CLOCKS_PER_SEC);
                
                if (numEntries == 0) {
                    cout << "No new entries. Skipping validation...\n";
                    break;
                }

                // Delay to read previous messages since validation can fill the console
                delayExecution("About to start validation", 3);

                if (printLog) { // Only prints if true for formatting
                    cout << "┌─────────────────────────────────────────" << endl; // Unicode: '┌'=u250C '─'=u2500
                }

                ticks = clock();
                bst->ValidateData(printLog); // Validate data, printLog bool determines if verbose output is printed. Default is "true".
                ticks = clock() - ticks;

                printf("Validated courses in %5f seconds.\n", ticks*1.0/CLOCKS_PER_SEC);
                break;
            // Search using course code
            case 2:
                cout << "\n\nPlease enter a code to Search: \n❯ ";
                cin >> searchName;

                cursorPos("delete");

                // Convert searchName to uppercase for case-insensitive search
                transform(searchName.begin(), searchName.end(), searchName.begin(), ::toupper);

                printf("\n\nSearching for \"%s\"...", searchName.c_str());

                ticks = clock();
                course = bst->Search(searchName);
                ticks = clock() - ticks;

                printSearchResults(course);
                printf("Search took %5f seconds.\n", ticks*1.0/CLOCKS_PER_SEC);
                break;
            // Sort in order by course code
            case 3:
                cout << "\n\nPrinting all course data...\n";
                cout << "┌─────────────────────────────────────────"; // Unicode: '┌'=u250C '─'=u2500

                ticks = clock();
                bst->InOrder();
                ticks = clock() - ticks;

                printf("\nCourses sorted in %5f seconds.\n", ticks*1.0/CLOCKS_PER_SEC);
                break;
            // Change CSV file
            case 4:

                cout << endl << endl;
                cout << "=================WARNING!=================\n"; 
                cout << "The CSV file will need to be loaded again.\n";
                cout << "This will add any new courses from the CSV\n";
                cout << "file to the existing data.\n";
                cout << "==========================================\n";
                cout << "Are you sure you want to continue? [y/n]: \n❯ "; // Unicode: '❯'=u276F

                char choice;
                cin >> choice;

                cursorPos("delete");

                if (choice == 'y') {
                    cout << "Please enter the name of the CSV file: \n❯ ";
                    cin >> csvFile;
                    cursorPos("delete");
                    break;
                }
                else {
                    cursorPos("delete");
                    cout << "\n\nReturning to main menu...\n";
                    break;
                }
                
        }
    }
    return 0;
}