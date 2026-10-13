#include <iostream>
#include <string>
#include <fstream>

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



int main() {
    return 0;
}