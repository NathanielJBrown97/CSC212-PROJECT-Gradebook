#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// General idea - I think

// Create TXT Files
// Develop intake to sort data into some form of arrays for each: HW grades, Assignment Grades, Exam Grades, Lab Grades.
// ^^ These need to be associated with a specific student.
// See sample txt for idea
// possible varying scenarios - students never submitted an assignment. Say 5 assignments are expected, there is only 4 values taken in, average would be on 4 grades? Auto fill remainder of storage container with 0 if != expected size?


// Helper function to calculate average of array sent to it (i.e. can pass it HW or assignments and get respective average back)
// store this average in a studentName associated array for future weighted grade calculation

// helper for students weighted grade calculation (will basically call the above helper)


// make a 'GradeBook Class' assign it following public values
// - Each Category of Grade (HW, Assignment, Grade, Exam, Lab) Floats - Array of some kind?
// - Float values to store each individual categories average; as well as an overall average value.

// make a 'Student Class inherit from Gradebook class
// add 1 additional public? private? variable for students name as it is the only varying piece of information.


// create a vector? to store objects created vai the TXT intake
// this should allow us to call specific student objects; and request specific information off of them i.e. category specific grade, overall, ect.




int main(int argc, char* argv[]){
    //create object of the student class
    GradeBook gradeBook("");

    //extract filename from CLA
    //std::string fileName = argv[1];
    std::string fileName = "../test_full.txt";
//    std::string fileName = "../test_empty.txt";
    // initiate intake of student1 txt file; to fill student obj's vectors
    gradeBook.intakeDataFile(fileName, gradeBook);
    /*std::ifstream inputFile;
    inputFile.open(fileName);
    if (inputFile.is_open()){
        std::string line;
        std::string category;
        std::string fname;
        std::string lname;
        float grade;


        while (inputFile){
            std::istringstream extractValue(line);

//            inputFile >> category;
            extractValue >> category;
            if (category == "Name"){
//                inputFile >> fname >> lname;
                extractValue >> fname >> lname;
                gradeBook.SetStudentName(fname + " " + lname);
            } else if (category == "Lab"){
                while(extractValue >> grade){
                    gradeBook.labGradesVector.emplace_back(grade);
                }
            } else if (category == "Assignment"){
                while(extractValue >> grade){
                    gradeBook.assignmentGradesVector.emplace_back(grade);
                }
            } else if (category == "Project"){
                while(extractValue >> grade){
                    gradeBook.projectGradesVector.emplace_back(grade);
                }
            } else if (category == "Exam"){
                while(extractValue >> grade){
                    gradeBook.examGradesVector.emplace_back(grade);
                }
            }
            getline(inputFile, line);
        }
        inputFile.close();

    }else{
        std::cout << "Error opening file.";
        return 1;
    }*/
    std::cout << "Labs:\n";
    for (int i = 0; i < gradeBook.labGradesVector.size(); i++){
        std::cout << std::to_string(gradeBook.labGradesVector[i]);
        std::cout << std::endl;
    }
    double labAverage = gradeBook.calculateSpecificAverage(gradeBook.labGradesVector, gradeBook.maxSizeLab);
    std::cout << labAverage << "\n";
    std::cout << "Assignments:\n";
    for (int i = 0; i < gradeBook.assignmentGradesVector.size(); i++){
        std::cout << std::to_string(gradeBook.assignmentGradesVector[i]);
        std::cout << std::endl;
    }
    double assAverage = gradeBook.calculateSpecificAverage(gradeBook.assignmentGradesVector, gradeBook.maxSizeAss);
    std::cout << assAverage << "\n";

    // calculate coursegrade for student1's output
    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.assignmentGradesVector,
                                                       gradeBook.labGradesVector,
                                                       gradeBook.examGradesVector,
                                                       gradeBook.projectGradesVector);

    // Output Values
    std::cout << "Student Name: " << gradeBook.getStudentName() << "\n";
    std::cout << "Overall Course Grade: " << courseGrade << "\n";
}


