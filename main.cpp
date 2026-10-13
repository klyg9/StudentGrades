#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student
{
    string lastName;
    int studentID;
    double* scores;
    double average;
    char letterGrade;
};
void releaseMemory(Student*& students, int studentCount);
bool readGradeData(Student*& students, int& studentCount, int& testsCount){
    ifstream inputFile("student_data.txt");

    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return false;
    }
    inputFile >> studentCount >> testsCount;

    if (!inputFile || studentCount <= 0 || testsCount <= 0) {
        cout << "Invalid student or test count!" << endl;
        return false;
    }
    students = new Student[studentCount];
    for (int i = 0; i < studentCount; i++) {
        students[i].scores = new double[testsCount];
    }
    for (int i = 0; i < studentCount; i++) {
        inputFile >> students[i].lastName >> students[i].studentID;
        for (int j = 0; j < testsCount; j++) {
            inputFile >> students[i].scores[j];
        }
        if (!inputFile) {
                cout << "Error reading student data!" << endl;
                releaseMemory(students, studentCount);
                return false;
            }
        }
    return true;
}

void releaseMemory(Student*& students, int studentCount) {
    if (students == nullptr) {
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        delete [] students[i].scores;
        students[i].scores = nullptr;
    }
    delete[] students;
    students = nullptr;
}

void calculateAverage(Student* students, int studentCount, int testsCount) {
    for (int i = 0; i < studentCount; i++) {
        double total = 0;
        for (int j = 0; j < testsCount; j++) {
            total += students[i].scores[j];
        }
        students[i].average = total / testsCount;
    }
}

void assignLetterGrades(Student* students, int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        double average = students[i].average;

        if (average >= 90) {
            students[i].letterGrade = 'A';
        }
        else if (average >= 80) {
            students[i].letterGrade = 'B';
        }
        else if (average >= 70) {
            students[i].letterGrade = 'C';
        }
        else if (average >= 60) {
            students[i].letterGrade = 'D';
        }
        else {
            students[i].letterGrade = 'F';
        }
    }
}

void displayReport (Student* students, int studentCount) {
    cout << "\nSTUDENT GRADE REPORT\n";
    cout << "-------------------------------------\n";
    cout << left << setw(15) << "Last Name"
    << setw(12) << "Student ID"
    << setw(10) << "Average"
    << "Grade" << endl;

    cout << "--------------------------------------------------\n";
    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(15) << students[i].lastName
        << setw(12) << students[i].studentID
        << setw(10) << fixed << setprecision(2)
        << students[i].average
        << students[i].letterGrade << endl;
    }
}

int main() {
    Student* students = nullptr;
    int studentCount = 0;
    int testsCount = 0;

    if (!readGradeData(students, studentCount, testsCount)) {
        return 1;
    }
    calculateAverage(students, studentCount, testsCount);
    assignLetterGrades(students, studentCount);
    displayReport(students, studentCount);

    releaseMemory(students, studentCount);

    return 0;
}