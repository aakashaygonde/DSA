/*
F23 : 
        "Department maintains a student information. The file contains roll number, name, division and address. Allow user to add, delete information of student. Display information of particular employee. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to main the data."
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define the student structure
struct Student {
    int rollNumber;
    string name;
    string division;
    string address;

    // Function to write student information to file as binary
    void writeToFile(ofstream &outFile) {
        outFile.write(reinterpret_cast<char*>(&rollNumber), sizeof(rollNumber));
        size_t nameLen = name.length();
        outFile.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));  // Store length of name
        outFile.write(name.c_str(), nameLen);  // Write name
        size_t divLen = division.length();
        outFile.write(reinterpret_cast<char*>(&divLen), sizeof(divLen));  // Store length of division
        outFile.write(division.c_str(), divLen);  // Write division
        size_t addrLen = address.length();
        outFile.write(reinterpret_cast<char*>(&addrLen), sizeof(addrLen));  // Store length of address
        outFile.write(address.c_str(), addrLen);  // Write address
    }

    // Function to read student information from file
    void readFromFile(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(&rollNumber), sizeof(rollNumber));

        size_t nameLen;
        inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        char* nameBuffer = new char[nameLen + 1];
        inFile.read(nameBuffer, nameLen);
        nameBuffer[nameLen] = '\0';  // Null terminate the string
        name = string(nameBuffer);
        delete[] nameBuffer;

        size_t divLen;
        inFile.read(reinterpret_cast<char*>(&divLen), sizeof(divLen));
        char* divBuffer = new char[divLen + 1];
        inFile.read(divBuffer, divLen);
        divBuffer[divLen] = '\0';
        division = string(divBuffer);
        delete[] divBuffer;

        size_t addrLen;
        inFile.read(reinterpret_cast<char*>(&addrLen), sizeof(addrLen));
        char* addrBuffer = new char[addrLen + 1];
        inFile.read(addrBuffer, addrLen);
        addrBuffer[addrLen] = '\0';
        address = string(addrBuffer);
        delete[] addrBuffer;
    }
};

// Function to add a student record
void addStudent() {
    ofstream outFile("students.txt", ios::app | ios::binary); // Open the file in append mode

    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter student roll number: ";
    cin >> student.rollNumber;
    cin.ignore();  // To ignore the newline character after entering roll number
    cout << "Enter student name: ";
    getline(cin, student.name);
    cout << "Enter student division: ";
    getline(cin, student.division);
    cout << "Enter student address: ";
    getline(cin, student.address);

    // Write the student data to the file
    student.writeToFile(outFile);

    cout << "Student record added successfully." << endl;

    outFile.close();
}

// Function to delete a student record
void deleteStudent(int rollNumber) {
    ifstream inFile("students.txt", ios::in | ios::binary);
    ofstream outFile("temp.txt", ios::out | ios::binary);

    if (!inFile || !outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    Student student;

    while (inFile) {
        student.readFromFile(inFile);

        if (inFile) {
            if (student.rollNumber == rollNumber) {
                found = true;
            } else {
                student.writeToFile(outFile);  // Write to temp file
            }
        }
    }

    if (found) {
        cout << "Student record deleted successfully." << endl;
    } else {
        cout << "Student record not found." << endl;
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the temp file
    remove("students.txt");
    rename("temp.txt", "students.txt");
}

// Function to display a student record
void displayStudent(int rollNumber) {
    ifstream inFile("students.txt", ios::in | ios::binary);

    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    Student student;

    while (inFile) {
        student.readFromFile(inFile);

        if (inFile) {
            if (student.rollNumber == rollNumber) {
                found = true;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Name: " << student.name << endl;
                cout << "Division: " << student.division << endl;
                cout << "Address: " << student.address << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "Student record not found." << endl;
    }

    inFile.close();
}

// Main function to interact with the user
int main() {
    int choice, rollNumber;

    do {
        cout << "\nStudent Information System" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Delete student" << endl;
        cout << "3. Display student information" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter roll number of student to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 3:
                cout << "Enter roll number of student to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
