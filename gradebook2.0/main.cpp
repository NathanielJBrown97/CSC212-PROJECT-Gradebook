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
//    std::string fileName = "../test_full.txt";
//    std::string fileName = "../test_empty.txt";
    std::string fileName = "../test_varying_grades.txt";
    // initiate intake of student1 txt file; to fill student obj's vectors
    gradeBook.intakeDataFile(fileName, gradeBook);

    //// ADD ADDITIONAL OUTER LAYER TO DETERMINE UPDATE GRADES - OR REPORTS
    int report_update;
    std::string studentName;
    std::ofstream outputFile;

    while (gradeBook.getStudentName() == ""){
        std::cout << "Please enter student name: \n";
        std::cin >> studentName;
        gradeBook.SetStudentName(studentName);
    }

    int userChoice;
    while (userChoice != 5) {
        std::cout << "Please look at the menu of choices and input the number correlated to your choice: \n\n"
                     "1.) Manual Intake \n"
                     "2.) Report Student's Name and Overall Course Grade \n"
                     "3.) Report Specific Category Grades \n"
                     "4.) Full Course Report \n"

                     "5.) End Program \n";

        std::cin >> userChoice;
        std::cout << "\n";

        int innerUserChoice = 0;
        if (userChoice == 1){
            std::cout << "Manual Intake; Please input the number correlated with the category you would like to update: \n\n"
                         "1.) Labs \n"
                         "2.) Assignments \n"
                         "3.) Projects \n"
                         "4.) Exam \n"
                         "5.) Save Changes \n"
                         "6.) Return to Main Menu \n";
            std::cin >> innerUserChoice;

            while (innerUserChoice != 6){
                std::string gradeInput;
                if (innerUserChoice == 1){
                    std::cout << "Please enter Lab grades: \n\n";
                    while(gradeInput != "Q" && gradeBook.labGradesVector.size() != gradeBook.maxSizeLab){
                        std::cin >> gradeInput;
                        if (gradeInput != "Q"){
                            int(gradeInput);
                            gradeBook.labGradesVector.emplace_back(gradeInput);
                        }
                    }
                }
                else if (innerUserChoice == 2){
                    std::cout << "Please enter Assignment grades: \n\n";
                    while(gradeInput != "Q" && gradeBook.assignmentGradesVector.size() != gradeBook.maxSizeAss){
                        std::cin >> gradeInput;
                        int(gradeInput);
                        gradeBook.assignmentGradesVector.emplace_back(gradeInput);
                    }
                }
                else if (innerUserChoice == 3){
                    std::cout << "Please enter Project grades: \n\n";
                    while(gradeInput != "Q" && gradeBook.projectGradesVector.size() != gradeBook.maxSizeProject){
                        std::cin >> gradeInput;
                        int(gradeInput);
                        gradeBook.projectGradesVector.emplace_back(gradeInput);
                    }
                }
                else if (innerUserChoice == 4){
                    std::cout << "Please enter Exam grades: \n\n";
                    while(gradeInput != "Q" && gradeBook.examGradesVector.size() != gradeBook.maxSizeExam){
                        std::cin >> gradeInput;
                        int(gradeInput);
                        gradeBook.examGradesVector.emplace_back(gradeInput);
                    }
                }
                else if (innerUserChoice == 5){
                    // write gradebook object to input txt file
                    std::string fileName = "../input.txt";
                    outputFile.open(fileName);

                    //Write maze to file
                    if (outputFile.is_open()) {
                        outputFile << "Name " << gradeBook.getStudentName();
                        outputFile << std::endl;

                        for (int i = 0; i < gradeBook.labGradesVector.size(); i++){
                            outputFile << "Lab" << gradeBook.labGradesVector[i] << " ";
                        }
                        outputFile << std::endl;

                        for (int i = 0; i < gradeBook.assignmentGradesVector.size(); i++) {
                            outputFile << "Assignment" << gradeBook.assignmentGradesVector[i] << " ";
                        }
                        outputFile << std::endl;

                        for (int i = 0; i < gradeBook.projectGradesVector.size(); i++) {
                            outputFile << "Project" << gradeBook.projectGradesVector[i] << " ";
                        }
                        outputFile << std::endl;

                        for (int i = 0; i < gradeBook.examGradesVector.size(); i++) {
                            outputFile << "Exam" << gradeBook.examGradesVector[i] << " ";
                        }
                        outputFile << std::endl;

                        outputFile.close();
                    } else {
                        //Terminate program if unable to open file
                        std::cout << "Error opening file";
                        return 1;
                    }
                }
            }
        }
        else if (userChoice == 2) {
            while (innerUserChoice != 5) {}
            std::cout
                    << "[Option 1 Indicator]; Please look at the menu of choices and input the number correlated to your choice: \n\n";
        } else if (userChoice == 2) {
            while (innerUserChoice != 5) {
                std::cout
                        << "Select Specific Category; Please look at the menu of choices and input the number correlated to your choice: \n\n";


                std::cout << "1.) Report all Assignment Grades and Total \n";
                std::cout << "2.) Report all Lab Grades and Total \n";
                std::cout << "3.) Report all Exam Grades and Total \n";
                std::cout << "4.) Report all Project Grades and Total \n";
                std::cout << "5.) Return to Main Menu \n";

                std::cin >> innerUserChoice;

                if (innerUserChoice = 1) {
                    //// DoThing
                }
                if (innerUserChoice = 2) {
                    //// DoThing
                }
                if (innerUserChoice = 3) {
                    //// DoThing
                }
                if (innerUserChoice = 4) {
                    //// DoThing
                }
                if (innerUserChoice = 5) {
                    std::cout << "Returning you to the main menu... \n";
                }

            }
        } else if (userChoice == 5) {
            std::cout << "Exiting Gradebook Program... ";
        }
    }

//    int input;
//
//    std::cout << "Please enter 1 to input grades or 2 to generate reports";
//    std::cin >> input;
//    if (input == 1){
//        //check for student name, get name if null
//        std::cout << "Please select from the following options to enter grades:\n"
//                     "1. Labs\n2. Assignments\n3. Projects\n4. Exams\n5. Return to previous menu";
//        std::cin >> input;
//        if (input == 1){
//            std::cout << "Please enter grades for labs.";
//            //get lab grades
//        } else if (input == 2){
//            std::cout << "Please enter grades for assignments.";
//            //get assignment grades
//        }
//    } else{
//
//    }
//
//    std::cout << "Labs:\n";
//    for (int i = 0; i < gradeBook.labGradesVector.size(); i++){
//        std::cout << std::to_string(gradeBook.labGradesVector[i]);
//        std::cout << std::endl;
//    }
//    double labAverage = gradeBook.calculateSpecificAverage(gradeBook.labGradesVector, gradeBook.maxSizeLab);
//    std::cout << labAverage << "\n";
//    std::cout << "Assignments:\n";
//    for (int i = 0; i < gradeBook.assignmentGradesVector.size(); i++){
//        std::cout << std::to_string(gradeBook.assignmentGradesVector[i]);
//        std::cout << std::endl;
//    }
//    double assAverage = gradeBook.calculateSpecificAverage(gradeBook.assignmentGradesVector, gradeBook.maxSizeAss);
//    std::cout << assAverage << "\n";
//
//    // calculate coursegrade for student1's output
//    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.assignmentGradesVector,
//                                                       gradeBook.labGradesVector,
//                                                       gradeBook.examGradesVector,
//                                                       gradeBook.projectGradesVector);
//
//    // Output Values
//    std::cout << "Student Name: " << gradeBook.getStudentName() << "\n";
//    std::cout << "Overall Course Grade: " << courseGrade << "\n";
}


