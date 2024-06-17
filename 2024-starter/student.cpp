#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm> // for std::transform
#include <cctype>    // for std::toupper, std::tolower
#include <set>
using namespace std;

// Student structure to hold student details
struct Student {
    string name;
    int age;
    string address;
    list<string> courses; // Linked list to store courses
};

// List of available courses
const string availableCourses[] = {"DSA", "SAD", "NETWORKING", "FOP", "ENGLISH", "MATH", "KINY"};
const int numAvailableCourses = sizeof(availableCourses) / sizeof(availableCourses[0]);

//Set to store student names
set<string> studentNames;

//Function to check if a name already exists
bool isNameExists(const string& name) {
    return studentNames.find(name) != studentNames.end();
}

// Function to convert a string to uppercase
string toUpper(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Function to check if a course exists in the availableCourses array (case insensitive)
bool isValidCourse(const string& course) {
    string courseUpper = toUpper(course);

    for (int i = 0; i < numAvailableCourses; ++i) {
        if (toUpper(availableCourses[i]) == courseUpper) {
            return true;
        }
    }
    return false;
}

// Function to add a course to the student's course list if valid
void addCourseToStudent(Student& student, const string& course) {
    if (isValidCourse(course)) {
        // Check if the course is already in the student's list
        if (find(student.courses.begin(), student.courses.end(), course) == student.courses.end()) {
            student.courses.push_back(course);
        } else {
            cout << "Warning: Course '" << course << "' is already added. Skipping duplicate." << endl;
        }
    } else {
        cout << "Error: Course '" << course << "' is not available." << endl;
    }
}

// Function to save student data to a file
void saveStudentToFile(const Student& student) {
    ofstream outFile("student_data.txt", ios::app); // Open file in append mode

    if (outFile.is_open()) {
        // Write student details to file
        outFile << "Name: " << student.name << endl;
        outFile << "Age: " << student.age << endl;
        outFile << "Address: " << student.address << endl;
        outFile << "Courses:" << endl;

        // Write each course to file using traditional iterator-based loop
        for (list<string>::const_iterator it = student.courses.begin(); it != student.courses.end(); ++it) {
            outFile << " - " << *it << endl;
        }

        outFile << endl;
        outFile.close();

        cout << "Student data has been saved to 'student_data.txt'." << endl;
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

// Function to get student details from the user
void getStudentDetails(Student& student) {
    cout << "Enter student's name: ";
    getline(cin, student.name);

    cout << "Enter student's age: ";
    cin >> student.age;
    cin.ignore(); // Ignore newline left in input buffer

    cout << "Enter student's address: ";
    getline(cin, student.address);
}

// Function to get courses for the student from the user
void getStudentCourses(Student& student) {
    int numCourses;
    cout << "How many courses will the student take? ";
    cin >> numCourses;
    cin.ignore(); // Ignore newline left in input buffer

    cout << "List of available courses: DSA, SAD, NETWORKING, FOP, ENGLISH, MATH, KINY" << endl;

    int i = 0;
    while (i < numCourses) {
        string course;
        cout << "Enter course " << i + 1 << ": ";
        getline(cin, course);

        // Convert course to uppercase before checking validity
        transform(course.begin(), course.end(), course.begin(), ::toupper);

        if (isValidCourse(course)) {
            addCourseToStudent(student, course);
            i++; // Only increment i if the course is valid
        } else {
            cout << "Invalid course. Please enter a valid course." << endl;
        }
    }
}

void saveStudentToCSV(const Student& student) {
    ofstream outFile("student_data.csv", ios::app); // Open file in append mode

    if (outFile.is_open()) {
        // Write student details to file
        outFile << student.name << ",";
        outFile << student.age << ",";
        outFile << student.address << ",";

        // Write each course to file using traditional iterator-based loop
        for (list<string>::const_iterator it = student.courses.begin(); it != student.courses.end(); ++it) {
            outFile << *it;
            if (next(it) != student.courses.end()) {
                outFile << "|"; // Use a different delimiter for courses
            }
        }

        outFile << endl;
        outFile.close();

        cout << "Student data has been saved to 'student_data.csv'." << endl;
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

int main() {
    char addAnother = 'Y';

    while (toupper(addAnother) == 'Y') {
        Student student;

        // Get student details from the user
        getStudentDetails(student);

        // Get student courses from the user
        getStudentCourses(student);

        // Save student data to file
        saveStudentToFile(student);

        // Save student data to CSV file
        saveStudentToCSV(student);

        // Ask user if they want to add another student
        cout << "Do you want to add another student? (Y/N): ";
        cin >> addAnother;
        cin.ignore(); // Ignore newline left in input buffer
    }

    cout << "Program exited." << endl;

    return 0;
}