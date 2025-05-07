/*
F24 : 
        "Company maintains employee information as employee ID, name, designation and salary. Allow user to add, delete information of employee. Display information of particular employee. If employee does not exist an appropriate message is displayed. If it is, then the system displays the employee details. Use index sequential file to maintain the data."
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Employee structure
struct Employee {
    int employeeID;
    string name;
    string designation;
    double salary;

    // Function to write employee data to a file
    void writeToFile(ofstream &outFile) {
        outFile.write(reinterpret_cast<char*>(&employeeID), sizeof(employeeID));
        
        // Write name
        size_t nameLength = name.length();
        outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        outFile.write(name.c_str(), nameLength);
        
        // Write designation
        size_t designationLength = designation.length();
        outFile.write(reinterpret_cast<char*>(&designationLength), sizeof(designationLength));
        outFile.write(designation.c_str(), designationLength);
        
        // Write salary
        outFile.write(reinterpret_cast<char*>(&salary), sizeof(salary));
    }

    // Function to read employee data from a file
    void readFromFile(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(&employeeID), sizeof(employeeID));
        
        // Read name
        size_t nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        char* nameBuffer = new char[nameLength + 1];
        inFile.read(nameBuffer, nameLength);
        nameBuffer[nameLength] = '\0';  // Null-terminate the string
        name = string(nameBuffer);
        delete[] nameBuffer;

        // Read designation
        size_t designationLength;
        inFile.read(reinterpret_cast<char*>(&designationLength), sizeof(designationLength));
        char* designationBuffer = new char[designationLength + 1];
        inFile.read(designationBuffer, designationLength);
        designationBuffer[designationLength] = '\0';
        designation = string(designationBuffer);
        delete[] designationBuffer;

        // Read salary
        inFile.read(reinterpret_cast<char*>(&salary), sizeof(salary));
    }
};

// Function to add a new employee
void addEmployee() {
    ofstream outFile("data.dat", ios::app | ios::binary); // Open the data file in append mode
    ofstream indexFile("index.dat", ios::app | ios::binary); // Open the index file in append mode

    if (!outFile || !indexFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.employeeID;
    cin.ignore();  // Ignore newline left by previous input
    cout << "Enter employee name: ";
    getline(cin, emp.name);
    cout << "Enter employee designation: ";
    getline(cin, emp.designation);
    cout << "Enter employee salary: ";
    cin >> emp.salary;

    // Write the employee data to the data file
    long pos = outFile.tellp();  // Get the position of the new record in the data file
    emp.writeToFile(outFile);

    // Write the index data (employee ID and position in data file)
    indexFile.write(reinterpret_cast<char*>(&emp.employeeID), sizeof(emp.employeeID));
    indexFile.write(reinterpret_cast<char*>(&pos), sizeof(pos));

    cout << "Employee record added successfully." << endl;

    outFile.close();
    indexFile.close();
}

// Function to display an employee's information
void displayEmployee(int empID) {
    ifstream inFile("data.dat", ios::in | ios::binary);
    ifstream indexFile("index.dat", ios::in | ios::binary);

    if (!inFile || !indexFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    Employee emp;
    long dataPos;
    int id;

    // Search the index file for the employee ID
    while (indexFile.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        indexFile.read(reinterpret_cast<char*>(&dataPos), sizeof(dataPos));
        if (id == empID) {
            found = true;
            // Read the employee data from the data file
            inFile.seekg(dataPos);
            emp.readFromFile(inFile);
            // Display employee information
            cout << "Employee ID: " << emp.employeeID << endl;
            cout << "Name: " << emp.name << endl;
            cout << "Designation: " << emp.designation << endl;
            cout << "Salary: " << emp.salary << endl;
            break;
        }
    }

    if (!found) {
        cout << "Employee record not found." << endl;
    }

    inFile.close();
    indexFile.close();
}

// Function to delete an employee record
void deleteEmployee(int empID) {
    ifstream inFile("data.dat", ios::in | ios::binary);
    ifstream indexFile("index.dat", ios::in | ios::binary);
    ofstream tempDataFile("temp_data.dat", ios::out | ios::binary);
    ofstream tempIndexFile("temp_index.dat", ios::out | ios::binary);

    if (!inFile || !indexFile || !tempDataFile || !tempIndexFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    Employee emp;
    long dataPos;
    int id;

    // Read the index file and filter out the employee to be deleted
    while (indexFile.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        indexFile.read(reinterpret_cast<char*>(&dataPos), sizeof(dataPos));
        if (id != empID) {
            // Write the record to temp files if it's not the one to be deleted
            tempIndexFile.write(reinterpret_cast<char*>(&id), sizeof(id));
            tempIndexFile.write(reinterpret_cast<char*>(&dataPos), sizeof(dataPos));
        } else {
            found = true;
        }
    }

    if (!found) {
        cout << "Employee with ID " << empID << " not found." << endl;
        inFile.close();
        indexFile.close();
        tempDataFile.close();
        tempIndexFile.close();
        remove("temp_data.dat");
        remove("temp_index.dat");
        return;
    }

    // Write the remaining records from the data file to the temporary data file
    inFile.clear();
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&emp.employeeID), sizeof(emp.employeeID))) {
        inFile.read(reinterpret_cast<char*>(&dataPos), sizeof(dataPos));
        if (emp.employeeID != empID) {
            inFile.seekg(dataPos);
            emp.readFromFile(inFile);
            emp.writeToFile(tempDataFile);
        }
    }

    cout << "Employee record deleted successfully." << endl;

    inFile.close();
    indexFile.close();
    tempDataFile.close();
    tempIndexFile.close();

    // Replace old files with the new ones
    remove("data.dat");
    remove("index.dat");
    rename("temp_data.dat", "data.dat");
    rename("temp_index.dat", "index.dat");
}

int main() {
    int choice, empID;

    do {
        cout << "\nEmployee Information System" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Delete employee" << endl;
        cout << "3. Display employee information" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                cout << "Enter employee ID to delete: ";
                cin >> empID;
                deleteEmployee(empID);
                break;
            case 3:
                cout << "Enter employee ID to display: ";
                cin >> empID;
                displayEmployee(empID);
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
