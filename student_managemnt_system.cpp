//
// Created by Prince on 29-10-2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Function to add a new student record
void addStudent() {
    int student_id;
    cout << "Enter the ID of the student: ";
    cin >> student_id;
    string student_name;
    cout << "Enter the name of the student: ";
    cin.ignore();
    getline(cin, student_name);
    string student_grade;
    cout << "Enter the grade of the student: ";
    getline(cin, student_grade);

    ofstream myfile("D:/B-tech/c++/student_data.txt", ios::app);
    if (myfile.is_open()) {
        myfile << student_id << "," << student_name << "," << student_grade << endl;
        myfile.close();
        cout << "Data added successfully!\n";
    } else {
        cout << "Error: File could not be opened!\n";
    }
}

// Function to view all student records
void viewStudents() {
    ifstream myfile("D:/B-tech/c++/student_data.txt");
    if (myfile.is_open()) {
        string line;
        cout << "ID\t          Name\t             Grade\n";
        cout << "---------------------------------------\n";
        while (getline(myfile, line)) {
            stringstream ss(line);
            string student_id, student_name, student_grade;
            getline(ss, student_id, ',');
            getline(ss, student_name, ',');
            getline(ss, student_grade, ',');

            cout << student_id << "\t    " << student_name << "\t    " << student_grade <<"%" << endl;
        }
        myfile.close();
    } else {
        cout << "Error: File could not be opened!\n";
    }
}

const int MAX_STUDENTS = 100; // Maximum number of students

// Function to update a student record
void updateStudent(int studentID) {
    ifstream inFile("D:/B-tech/c++/student_data.txt");
    string lines[MAX_STUDENTS]; // Fixed-size array to store lines
    int count = 0; // Count of lines read

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line) && count < MAX_STUDENTS) {
            stringstream ss(line);
            string student_id, student_name, student_grade;
            getline(ss, student_id, ',');
            getline(ss, student_name, ',');
            getline(ss, student_grade, ',');

            if (student_id == to_string(studentID)) {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, student_name);
                cout << "Enter new grade: ";
                getline(cin, student_grade);
                line = student_id + "," + student_name + "," + student_grade; // Update line with new data
            }
            lines[count++] = line; // Store the line in the array
        }
        inFile.close();

        // Write back the updated lines to the file
        ofstream outFile("D:/B-tech/c++/student_data.txt");
        for (int i = 0; i < count; ++i) {
            outFile << lines[i] << "\n"; // Write each line
        }
        outFile.close();
        cout << "Student record updated successfully!\n";
    } else {
        cout << "Error: Unable to open file for updating.\n";
    }
}

// Function to delete a student record
void deleteStudent(int studentID) {
    ifstream inFile("D:/B-tech/c++/student_data.txt");
    string lines[MAX_STUDENTS]; // Fixed-size array to store lines
    int count = 0; // Count of lines read

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line) && count < MAX_STUDENTS) {
            stringstream ss(line);
            string student_id, student_name, student_grade;
            getline(ss, student_id, ',');
            getline(ss, student_name, ',');
            getline(ss, student_grade, ',');

            if (student_id != to_string(studentID)) { // Only keep records that don't match the ID
                lines[count++] = line; // Store the line in the array
            }
        }
        inFile.close();

        // Write back the remaining lines to the file
        ofstream outFile("D:/B-tech/c++/student_data.txt");
        for (int i = 0; i < count; ++i) {
            outFile << lines[i] << "\n"; // Write each line
        }
        outFile.close();
        cout << "Student record deleted successfully!\n";
    } else {
        cout << "Error: Unable to open file for deletion.\n";
    }
}

// Linear search function to find a student by ID
void Linear_search(int studentID) {
    ifstream myfile("D:/B-tech/c++/student_data.txt");
    if (myfile.is_open()) {
        string line;

        while (getline(myfile, line)) {
            stringstream ss(line);
            string student_id, student_name, student_grade;
            getline(ss, student_id, ',');
            getline(ss, student_name, ',');
            getline(ss, student_grade, ',');

            // Check if the student ID matches the input
            if (student_id == to_string(studentID)) {
                cout << "Student Found:\n";
                cout << "ID: " << student_id << "\n";
                cout << "Name: " << student_name << "\n";
                cout << "Grade: " << student_grade <<"%"<< "\n";
                break;
            }
        }
        myfile.close();
    } else {
        cout << "Error: File could not be opened!\n";
    }
}

// Binary search function to find a student's details by ID using a fixed-size array
void Binary_search(int studentID) {
    ifstream myfile("D:/B-tech/c++/student_data.txt");

    string lines[MAX_STUDENTS]; // Fixed-size array for storing records
    int count = 0;

    // Read all records into an array
    if (myfile.is_open()) {
        while (getline(myfile, lines[count]) && count < MAX_STUDENTS) {
            count++;
        }

        myfile.close();


        int left = 0;
        int right = count - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            stringstream ss(lines[mid]);
            string id_str;
            getline(ss, id_str, ',');

            int midID = stoi(id_str);

            if (midID == studentID) {
                cout << "Student Found:\n"
                     << lines[mid]
                     << "\n";
                return;
            }

            if (midID < studentID)
                left = mid + 1;
            else
                right = mid - 1;
        }

        cout << "Student with ID " << studentID << " not found.\n";
    } else {
       cout << "Error: File could not be opened!\n";
   }
}

int main() {
    int choice, studentID;

    while (true) {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Linear Search to find Student\n";
        cout << "6. Binary Search to find Student\n";
        cout << "7. Exit\n";

         cout<< "\nEnter your choice: ";
         cin >> choice;

         switch (choice) {
             case 1:
                 addStudent();
                 break;
             case 2:
                 viewStudents();
                 break;
             case 3:
                 cout<< "\nEnter Student ID to update: ";
                 cin >>studentID;
                 updateStudent(studentID);
                 break;
             case 4:
                 cout<< "\nEnter Student ID to delete: ";
                 cin >>studentID;
                 deleteStudent(studentID);
                 break;
             case 5:
                 cout<< "\nEnter Student ID to find details using Linear Search: ";
                 cin >>studentID;
                 Linear_search(studentID);
                 break;
             case 6:
                 cout<< "\nEnter Student ID to find details using Binary Search: ";
                 cin >>studentID;
                 Binary_search(studentID);
                 break;
             case 7:
                 cout<< "\nExiting...\n";
                 return 0;
             default:
                 cout<< "\nInvalid choice! Please try again.\n";
         }
     }
}