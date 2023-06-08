#include "OGgradebook.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[]){
    //create object of the student class
    Student student1("Nathaniel Brown");

    //extract filename from CLA
    std::string fileName = argv[1];

    // initiate intake of student1 txt file; to fill student obj's vectors
    student1.intakeDataFile(fileName, student1);

    // calculate coursegrade for student1's output
    double courseGrade = student1.calculateCourseGrade(student1.homeworkGradesVector,
                                                       student1.assignmentGradesVector,
                                                       student1.labGradesVector,
                                                       student1.examGradesVector,
                                                       student1.projectGradesVector);

    // Output Values
    std::cout << "Student Name: " << student1.getStudentName() << "\n";
    std::cout << "Overall Course Grade: " << courseGrade << "\n";
}


