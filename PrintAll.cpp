// The printAll function will sort a hash table containing courses into alphanumeric order and print them in order

#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// Create global for default hash table size
const unsigned int DEFAULT_SIZE = 179;

// Define a structure to represent a course
struct Course {
    string courseId;          
    string courseName;        
    vector<string> prerequisites;  
};

// Create HashTable class
class HashTable {
private:

    // Node structure
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        // Defaults for Node
        Node() : key(UINT_MAX), next(nullptr) {}
        Node(Course c) : course(c), key(UINT_MAX), next(nullptr) {}
    };

    // Integer for hash table size
    unsigned int tableSize;

    // Array of buckets for nodes
    list<Node>* table;

    // Integer to track total number of courses
    unsigned int courseTotal;

public:
    // Constructor to initialize hash table size and set courseTotal to 0
    HashTable(unsigned int size = DEFAULT_SIZE) {
        tableSize = size;
        table = new list<Node>[tableSize];
        courseTotal = 0;
    }

    // Destructor to handle memory
    ~HashTable() {
        delete[] table;
    }

    // QuickSort partition function
    int partition(vector<Course>& courseList, int low, int high) {
        string pivot = courseList[high].courseId;
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (courseList[j].courseId <= pivot) {
                ++i;
                swap(courseList[i], courseList[j]);
            }
        }
        swap(courseList[i + 1], courseList[high]);
        return i + 1;
    }

    // QuickSort recursive function
    void quickSort(vector<Course>& courseList, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(courseList, low, high);
            quickSort(courseList, low, pivotIndex - 1);
            quickSort(courseList, pivotIndex + 1, high);
        }
    }

    // Print all courses in sorted order
    void printAll() {
        vector<Course> courseList;

        // Gather all courses from the hash table
        for (unsigned int i = 0; i < tableSize; ++i) {
            for (const Node& node : table[i]) {
                courseList.push_back(node.course);
            }
        }

        // Sort the courses by courseId using quickSort
        quickSort(courseList, 0, courseList.size() - 1);

        // Print the sorted list of courses
        cout << endl;
        cout << "Course list:" << endl;
        for (const Course& course : courseList) {
            cout << course.courseId << ", " << course.courseName << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const string& prereq : course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            } else {
                cout << "No prerequisites" << endl;
            }
            cout << endl;
        }
    }
};