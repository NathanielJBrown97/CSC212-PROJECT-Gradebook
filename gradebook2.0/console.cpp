#include "gradebook.h"
#include <iostream>
#include <string>

int console(GradeBook gradebook){

        //// ADD ADDITIONAL OUTER LAYER TO DETERMINE UPDATE GRADES - OR REPORTS
        int report_update;
        std::string studentName;
        std::ofstream outputFile;

        while (gradebook.getStudentName() == ""){
            std::cout << "Please enter student name: \n";
            std::cin >> studentName;
            gradebook.SetStudentName(studentName);
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
                                 "1.) Assignments \n"
                                 "2.) Labs \n"
                                 "3.) Projects \n"
                                 "4.) Exam \n"
                                 "5.) Save Changes \n"
                                 "6.) Return to Main Menu \n";
                    std::cin >> innerUserChoice;

                    while (innerUserChoice != 6){
                        std::string gradeInput;
                        if (innerUserChoice == 1){
                            std::cout << "Please enter Lab grades: \n\n";
                            while(gradeInput != "Q" && gradebook.labGradesVector.size() != gradebook.maxSizeLab){
                                std::cin >> gradeInput;
                                int(gradeInput);
                                gradebook.labGradesVector.emplace_back(gradeInput);
                            }
                        }
                        else if (innerUserChoice == 2){
                            std::cout << "Please enter Assignment grades: \n\n";
                            while(gradeInput != "Q" && gradebook.assignmentGradesVector.size() != gradebook.maxSizeAss){
                                std::cin >> gradeInput;
                                int(gradeInput);
                                gradebook.assignmentGradesVector.emplace_back(gradeInput);
                            }
                        }
                        else if (innerUserChoice == 3){
                            std::cout << "Please enter Project grades: \n\n";
                            while(gradeInput != "Q" && gradebook.projectGradesVector.size() != gradebook.maxSizeProject){
                                std::cin >> gradeInput;
                                int(gradeInput);
                                gradebook.projectGradesVector.emplace_back(gradeInput);
                            }
                        }
                        else if (innerUserChoice == 4){
                            std::cout << "Please enter Exam grades: \n\n";
                            while(gradeInput != "Q" && gradebook.examGradesVector.size() != gradebook.maxSizeExam){
                                std::cin >> gradeInput;
                                int(gradeInput);
                                gradebook.examGradesVector.emplace_back(gradeInput);
                            }
                        }
                        else if (innerUserChoice == 5){
                            // write gradebook object to input txt file
                            std::string fileName = "../input.txt";
                            outputFile.open(fileName);

                            //Write maze to file
                            if (outputFile.is_open()) {
                                outputFile << "Name " << gradebook.getStudentName();
                                outputFile << std::endl;

                                for (int i = 0; i < gradebook.labGradesVector.size(); i++){
                                    outputFile << gradebook.labGradesVector[i] << " ";
                                }
                                outputFile << std::endl;

                                for (int i = 0; i < gradebook.assignmentGradesVector.size(); i++) {
                                    outputFile << gradebook.assignmentGradesVector[i] << " ";
                                }
                                outputFile << std::endl;

                                for (int i = 0; i < gradebook.projectGradesVector.size(); i++) {
                                    outputFile << gradebook.projectGradesVector[i] << " ";
                                }
                                outputFile << std::endl;

                                for (int i = 0; i < gradebook.examGradesVector.size(); i++) {
                                    outputFile << gradebook.examGradesVector[i] << " ";
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


        }
