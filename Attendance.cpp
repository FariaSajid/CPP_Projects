#include <iostream>
#include <string>
using namespace std;

// Constant
const int MAX_STUDENTS = 100;

// Variables
string studentNames[MAX_STUDENTS];
int attendance[MAX_STUDENTS];
int studentCount = 0;

// Function Prototypes
void addStudent();
void markAttendance();
void viewAttendance();
void searchStudent();
void displayMenu();

int main() {
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                markAttendance();
                break;
            case 3:
                viewAttendance();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions

// Display the menu
void displayMenu() {
    cout << "\n--- Attendance System ---\n";
    cout << "1. Add Student\n";
    cout << "2. Mark Attendance\n";
    cout << "3. View Attendance\n";
    cout << "4. Search Student\n";
    cout << "5. Exit\n";
}

// Add a new student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Cannot add more students. Maximum limit reached.\n";
        return;
    }
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, studentNames[studentCount]);
    attendance[studentCount] = 0; // Initialize attendance
    studentCount++;
    cout << "Student added successfully.\n";
}

// Mark attendance for a student
void markAttendance() {
    if (studentCount == 0) {
        cout << "No students available. Please add students first.\n";
        return;
    }
    cout << "Enter student number (1 to " << studentCount << "): ";
    int studentNumber;
    cin >> studentNumber;
    if (studentNumber < 1 || studentNumber > studentCount) {
        cout << "Invalid student number.\n";
        return;
    }
    attendance[studentNumber - 1]++;
    cout << "Attendance marked for " << studentNames[studentNumber - 1] << ".\n";
}

// View attendance of all students
void viewAttendance() {
    if (studentCount == 0) {
        cout << "No students available.\n";
        return;
    }
    cout << "\n--- Attendance List ---\n";
    for (int i = 0; i < studentCount; i++) {
        cout << i + 1 << ". " << studentNames[i] << " - " << attendance[i] << " days\n";
    }
}

// Search for a student
void searchStudent() {
    if (studentCount == 0) {
        cout << "No students available.\n";
        return;
    }
    cout << "Enter student name to search: ";
    cin.ignore();
    string name;
    getline(cin, name);

    for (int i = 0; i < studentCount; i++) {
        if (studentNames[i] == name) {
            cout << "Student found: " << studentNames[i] << " - " << attendance[i] << " days\n";
            return;
        }
    }
    cout << "Student not found.\n";
}