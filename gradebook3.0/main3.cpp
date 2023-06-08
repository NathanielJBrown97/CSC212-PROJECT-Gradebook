#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    //create object of the student class
    GradeBook obj("");
    std::string file_name = std::string(argv[1]);
    obj.intakeDataFile(file_name, obj);

    // Run Console for UI after creation of Object.
    int userChoice = 0;
    while (userChoice != 5) {
        std::cout << "------------------------------\n";
        std::cout << "Please look at the menu of choices and input the number correlated to your choice: \n\n"
                     "1.) Manual Intake \n"
                     "2.) Individual: Report Student's Name and Overall Course Grade \n"
                     "3.) Category: Report Specific Category Grades \n"
                     "4.) Course: Full Course Report \n"

                     "5.) End Program \n";

        std::cin >> userChoice;
        std::cout << "\n";
        std::cout << "------------------------------\n";
        int innerUserChoice = 0;
        if (userChoice == 1){
            while (innerUserChoice != 6){
                std::cout << "Manual Intake; Please input the number correlated with the category you would like to update: \n\n"
                             "1.) Assignments \n"
                             "2.) Labs \n"
                             "3.) Projects \n"
                             "4.) Exam \n"
                             "5.) Save Changes \n"
                             "6.) Return to Main Menu \n";
                std::cin >> innerUserChoice;


                if (innerUserChoice == 1){
                    std::cout << "temp \n";
                }
                else if (innerUserChoice == 2){
                    std::cout << "temp \n";
                }
                else if (innerUserChoice == 3){
                    std::cout << "temp \n";
                }
                else if (innerUserChoice == 4){
                    std::cout << "temp \n";
                }
                else if (innerUserChoice == 5){
                    std::cout << "temp \n";
                }
                else if (innerUserChoice == 6){
                    std::cout << "temp \n";
                }
            }
        }
        else if (userChoice == 2) {
            // calculate coursegrade for student1's output
            double courseGrade = obj.calculateCourseGrade(obj.assignmentGradesVector,
                                                          obj.labGradesVector,
                                                          obj.examGradesVector,
                                                          obj.projectGradesVector);
            std::cout<< "Individual Output: \n\n"

                        "Student's Name: " << obj.getStudentName() <<
                        "\nStudent's Course Grade: " << courseGrade << "\n\n";

            std::cout << "Returning to Main Menu \n";
        }

        else if (userChoice == 3) {
            while (innerUserChoice != 5) {
                std::cout << "------------------------------\n";
                std::cout << "Select Specific Category; Please look at the menu of choices and input the number correlated to your choice: \n\n"
                             "1.) Report all Assignment Grades and Total \n"
                             "2.) Report all Lab Grades and Total \n"
                             "3.) Report all Exam Grades and Total \n"
                             "4.) Report all Project Grades and Total \n"
                             "5.) Return to Main Menu \n";

                std::cin >> innerUserChoice;
                std::cout << "------------------------------\n";

                if (innerUserChoice == 1) {
                    std::cout << "------------------------------\n";
                    std::cout << "Outputting all Assignment Grades and Total: \n\n";

                    std::cout << "Assignment Grade List: \n";
                    for (int currentAss = 0; currentAss < obj.assignmentGradesVector.size(); currentAss++){
                        std::cout << std::to_string(obj.assignmentGradesVector[currentAss]) << "\n";
                    }
                    double assAverage = obj.calculateSpecificAverage(obj.assignmentGradesVector, obj.maxSizeAss);
                    std::cout << "Assignment Average: "<< assAverage << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 2) {
                    std::cout << "------------------------------\n";
                    std::cout << "Outputting all Lab Grades and Total: \n\n";

                    std::cout << "Lab Grade List: \n";
                    for (int currentLab = 0; currentLab < obj.labGradesVector.size(); currentLab++){
                        std::cout << std::to_string(obj.labGradesVector[currentLab]) << "\n";
                    }
                    double labAverage = obj.calculateSpecificAverage(obj.labGradesVector, obj.maxSizeLab);
                    std::cout << "Lab Average: "<< labAverage << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 3) {
                    std::cout << "------------------------------\n";
                    std::cout << "Outputting all Exam Grades and Total: \n\n";

                    std::cout << "Exam Grade List: \n";
                    for (int currentExam = 0; currentExam < obj.examGradesVector.size(); currentExam++){
                        std::cout << std::to_string(obj.examGradesVector[currentExam]) << "\n";
                    }
                    double examAverage = obj.calculateSpecificAverage(obj.examGradesVector, obj.maxSizeExam);
                    std::cout << "Exam Average: "<< examAverage << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 4) {
                    std::cout << "------------------------------\n";
                    std::cout << "Outputting all Project Grades and Total: \n\n";

                    std::cout << "Project Grade List: \n";
                    for (int currentProject = 0; currentProject < obj.projectGradesVector.size(); currentProject++){
                        std::cout << std::to_string(obj.projectGradesVector[currentProject]) << "\n";
                    }
                    double ProjectAverage = obj.calculateSpecificAverage(obj.projectGradesVector, obj.maxSizeProject);
                    std::cout << "Project Average: "<< ProjectAverage << "\n";
                    std::cout << "------------------------------\n";

                }
                else if (innerUserChoice == 5) {

                    std::cout << "Returning you to the main menu... \n";
                }

            }
        }
        else if (userChoice == 4){
            while(innerUserChoice != 4){
                std::cout << "Course; Please look at the menu and input the number for which full report you would like. \n\n"
                             "1.) Full Report Card and Course Grade (Outputs Every Grade) \n"
                             "2.) Report Card: Averages of All Categories and Course Grade\n"
                             "3.) Course Average Only \n"
                             "4.) Return to the Main Menu \n";
                std::cin >> innerUserChoice;

                if (innerUserChoice == 1){
                    std::cout << "Full Course Report Card: (Every Grade, Category Averages, and Course Average) \n\n";
                    //ASS OUT
                    std::cout << "Assignment Grade List: \n";
                    for (int currentAss = 0; currentAss < obj.assignmentGradesVector.size(); currentAss++){
                        std::cout << std::to_string(obj.assignmentGradesVector[currentAss]) << " ";
                    }
                    double assAverage = obj.calculateSpecificAverage(obj.assignmentGradesVector, obj.maxSizeAss);
                    std::cout << "\nAssignment Average: "<< assAverage << "\n\n";
                    //LAB OUT
                    std::cout << "Lab Grade List: \n";
                    for (int currentLab = 0; currentLab < obj.labGradesVector.size(); currentLab++){
                        std::cout << std::to_string(obj.labGradesVector[currentLab]) << " ";
                    }
                    double labAverage = obj.calculateSpecificAverage(obj.labGradesVector, obj.maxSizeLab);
                    std::cout << "\nLab Average: "<< labAverage << "\n\n";
                    //EXAM OUT
                    std::cout << "Exam Grade List: \n";
                    for (int currentExam = 0; currentExam < obj.examGradesVector.size(); currentExam++){
                        std::cout << std::to_string(obj.examGradesVector[currentExam]) << " ";
                    }
                    double examAverage = obj.calculateSpecificAverage(obj.examGradesVector, obj.maxSizeExam);
                    std::cout << "Exam Average: "<< examAverage << "\n\n";
                    //PROJ OUT
                    std::cout << "\nProject Grade List: \n";
                    for (int currentProject = 0; currentProject < obj.projectGradesVector.size(); currentProject++){
                        std::cout << std::to_string(obj.projectGradesVector[currentProject]) << " ";
                    }
                    double ProjectAverage = obj.calculateSpecificAverage(obj.projectGradesVector, obj.maxSizeProject);
                    std::cout << "\nProject Average: "<< ProjectAverage << "\n\n";

                }
                else if (innerUserChoice == 2){
                    std::cout << "------------------------------\n";
                    std::cout << "Report on Student: Averages for Each Category and Overall: \n\n";
                    //AVG ASS OUT
                    double assAverage = obj.calculateSpecificAverage(obj.assignmentGradesVector, obj.maxSizeAss);
                    std::cout << "Assignment Average: "<< assAverage << "\n";
                    //AVG LAB OUT
                    double labAverage = obj.calculateSpecificAverage(obj.labGradesVector, obj.maxSizeLab);
                    std::cout << "Lab Average: "<< labAverage << "\n";
                    //AVG EXAM OUT
                    double examAverage = obj.calculateSpecificAverage(obj.examGradesVector, obj.maxSizeExam);
                    std::cout << "Exam Average: "<< examAverage << "\n";
                    //AVG PROJ OUT
                    double ProjectAverage = obj.calculateSpecificAverage(obj.projectGradesVector, obj.maxSizeProject);
                    std::cout << "Project Average: "<< ProjectAverage << "\n";
                    std::cout << "------------------------------\n";
                    std::cout << "------------------------------\n";
                    //AVG COURSE
                    double courseGrade = obj.calculateCourseGrade(obj.assignmentGradesVector,
                                                                  obj.labGradesVector,
                                                                  obj.examGradesVector,
                                                                  obj.projectGradesVector);
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 3){
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average Only \n\n";
                    //AVG COURSE
                    double courseGrade = obj.calculateCourseGrade(obj.assignmentGradesVector,
                                                                  obj.labGradesVector,
                                                                  obj.examGradesVector,
                                                                  obj.projectGradesVector);
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 4) {
                    std::cout << "Returning to Main Menu... \n";
                }
            }
        }
        else if (userChoice == 5) {
            std::cout << "Exiting Gradebook Program... ";
        }
    }





}

