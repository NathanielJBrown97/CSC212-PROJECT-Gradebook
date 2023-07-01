#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void IntakeDataFile(const std::string& fileName, GradeBook& gradeBook){
    std::ifstream inputFile;
    inputFile.open(fileName);
    if (inputFile.is_open()){
        std::string line;
        std::string category;
        std::string fname;
        std::string lname;
        double grade;

        while (inputFile){
            std::istringstream extractValue(line);

            extractValue >> category;
            if (category == "Name"){
                extractValue >> fname >> lname;
                gradeBook.SetStudentName(fname + " " + lname);
            } else if (category == "Labs"){
                while(extractValue >> grade){
                    gradeBook.labGradesVector.emplace_back(grade);
                }
            } else if (category == "Assignments"){
                while(extractValue >> grade){
                    gradeBook.assignmentGradesVector.emplace_back(grade);
                }
            } else if (category == "Projects"){
                while(extractValue >> grade){
                    gradeBook.projectGradesVector.emplace_back(grade);
                }
            } else if (category == "Exams"){
                while(extractValue >> grade){
                    gradeBook.examGradesVector.emplace_back(grade);
                }
            }
            getline(inputFile, line);
        }
        inputFile.close();

    }else{
        std::cout << "Error opening file.";
//        return 1;
    }
}

bool SaveChanges(std::string filename, GradeBook gradeBook) {
    std::ofstream outputFile;
    bool saved = false;

    outputFile.open(filename);

    if (outputFile.is_open()) {
        outputFile << "Name " << gradeBook.getStudentName();
        outputFile << std::endl;

        outputFile << "Labs ";
        for (int i = 0; i < gradeBook.labGradesVector.size(); i++) {
            outputFile << gradeBook.labGradesVector[i] << " ";
        }
        outputFile << std::endl;
        outputFile << "Assignments ";
        for (int i = 0; i < gradeBook.assignmentGradesVector.size(); i++) {
            outputFile << gradeBook.assignmentGradesVector[i] << " ";
        }
        outputFile << std::endl;

        outputFile << "Projects ";
        for (int i = 0; i < gradeBook.projectGradesVector.size(); i++) {
            outputFile << gradeBook.projectGradesVector[i] << " ";
        }
        outputFile << std::endl;
        outputFile << "Exams ";
        for (int i = 0; i < gradeBook.examGradesVector.size(); i++) {
            outputFile << gradeBook.examGradesVector[i] << " ";
        }
        outputFile << std::endl;

        outputFile.close();
        saved = true;
    } else {
        saved = false;
    }
    return saved;
}

int DisplayGradeInputMenu(){
    int input;
    std::cout << "Manual Intake; Please input the number correlated with the category you would like to update: \n"
                 "1.) Labs \n"
                 "2.) Assignments \n"
                 "3.) Projects \n"
                 "4.) Exam \n"
                 "5.) Save Changes \n"
                 "6.) Return to Main Menu \n";
    std::cout << ">>";
    std::cin >> input;
    return input;
}
void DisplayMainMenu(){
    std::cout << "Please look at the menu of choices and input the number correlated to your choice: \n\n"
                 "1.) Manual Intake \n"
                 "2.) Individual: Report Student's Name and Overall Course Grade \n"
                 "3.) Category: Report Specific Category Grades \n"
                 "4.) Course: Full Course Report \n"
                 "5.) End Program \n";
    std::cout << ">>";
}

//Dispalys list of grades for each category
void OutputGradeList(GradeBook gradeBook, std::string type, std::vector<double> gradesVec, int numGrades, double maxScore){
    std::cout << "------------------------------\n";
//    std::cout << "Outputting all " << type << " Grades and Total: \n\n";
    std::cout << type << " Grade List: ";
    for (int currentLab = 0; currentLab < numGrades; currentLab++){
        std::cout << gradesVec[currentLab] << " ";
    }
    double average = gradeBook.calculateSpecificAverage(gradesVec, numGrades, maxScore);
    std::cout << "\n" << type <<  "Average: " << average << "\n\n";
}

bool ValidateGrade(double grade, double maxGrade){
    bool valid = false;
    if (grade <= maxGrade){
        valid = true;
    }
    return valid;
}


int main(int argc, char* argv[]){
    //create object of the student class
    GradeBook gradeBook("");

    //extract filename from CLA
    std::string fileName = argv[1];

    IntakeDataFile(fileName, gradeBook);


    int report_update;
    std::string studentName;

    while (gradeBook.getStudentName() == ""){
        std::cout << "Please enter student name: ";
        std::getline(std::cin,studentName);
        gradeBook.SetStudentName(studentName);
    }

    int userChoice = 0;
    while (userChoice != 5) {
        DisplayMainMenu();
        std::cin >> userChoice;
        std::cout << "\n";
        std::cout << "------------------------------\n";
        int innerUserChoice = 0;
        if (userChoice == 1){
            while (innerUserChoice != 6){
                innerUserChoice = DisplayGradeInputMenu();
                std::string gradeInput;
                if (innerUserChoice == 1){
                    if (gradeBook.labGradesVector.size() == gradeBook.maxSizeLab){
                        std::cout << "Max number of lab grades have been entered.\n";
                        innerUserChoice = DisplayGradeInputMenu();
                    }else{
                        std::cout << "Please enter Lab grade: ";
                        std::cin >> gradeInput;
                        std::string save;
                        while(gradeBook.labGradesVector.size() != gradeBook.maxSizeLab && innerUserChoice == 1){
                            double grade = std::stod(gradeInput);
                            if (ValidateGrade(grade, gradeBook.maxScoreLab)){
                                gradeBook.labGradesVector.emplace_back(grade);
                                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                                std::cout << ">>";
                                std::cin >> save;
                                if (save == "N"){
                                    innerUserChoice = 0;
                                } else{
                                    std::cout << "Please enter Lab grade: ";
                                    std::cin >> gradeInput;
                                }
                            } else {
                                std::cout << "Invalid grade entered. Max grade allowed is: " << gradeBook.maxScoreLab << "\n";
                                std::cout << "Please enter Lab grade: ";
                                std::cin >> gradeInput;
                            }
                        }
                    }
                }
                else if (innerUserChoice == 2){
                    if (gradeBook.assignmentGradesVector.size() == gradeBook.maxSizeAss){
                        std::cout << "Max number of assignment grades have been entered.\n";
                        innerUserChoice = DisplayGradeInputMenu();
                    }else {
                        std::cout << "Please enter Assignment grade: ";
                        std::cin >> gradeInput;
                        std::string save;
                        while(gradeBook.assignmentGradesVector.size() != gradeBook.maxSizeAss && innerUserChoice == 2){
                            double grade = std::stod(gradeInput);
                            if (ValidateGrade(grade, gradeBook.maxScoreAss)){
                                gradeBook.assignmentGradesVector.emplace_back(grade);
                                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                                std::cout << ">>";
                                std::cin >> save;
                                if (save == "N"){
                                    innerUserChoice = 0;
                                } else{
                                    std::cout << "Please enter Assignment grade: ";
                                    std::cin >> gradeInput;
                                }
                            } else{
                                std::cout << "Invalid grade entered. Max grade allowed is: " << gradeBook.maxScoreAss << "\n";
                                std::cout << "Please enter Assignment grade: ";
                                std::cin >> gradeInput;
                            }
                        }
                    }
                }
                else if (innerUserChoice == 3){
                    if (gradeBook.projectGradesVector.size() == gradeBook.maxSizeProject){
                        std::cout << "Max number of project grades have been entered.\n";
                        innerUserChoice = DisplayGradeInputMenu();
                    } else{
                        std::cout << "Please enter Project grades: ";
                        std::cin >> gradeInput;
                        std::string save;
                        while(gradeBook.projectGradesVector.size() != gradeBook.maxSizeProject && innerUserChoice == 3){
                            double grade = std::stod(gradeInput);
                            if (ValidateGrade(grade, gradeBook.maxScoreProject)){
                                gradeBook.projectGradesVector.emplace_back(grade);
                                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                                std::cout << ">>";
                                std::cin >> save;
                                if (save == "N"){
                                    innerUserChoice = 0;
                                } else{
                                    std::cout << "Please enter Project grade: ";
                                    std::cin >> gradeInput;
                                }
                            } else{
                                std::cout << "Invalid grade entered. Max grade allowed is: " << gradeBook.maxScoreProject << "\n";
                                std::cout << "Please enter Project grade: ";
                                std::cin >> gradeInput;
                            }
                        }
                    }
                }
                else if (innerUserChoice == 4){
                    if (gradeBook.examGradesVector.size() == gradeBook.maxSizeExam){
                        std::cout << "Max number of exam grades have been entered.\n";
                        innerUserChoice = DisplayGradeInputMenu();
                    } else{
                        std::cout << "Please enter Exam grades: ";
                        std::cin >> gradeInput;
                        std::string save;
                        while(gradeBook.examGradesVector.size() != gradeBook.maxSizeExam && innerUserChoice == 4){
                            double grade = std::stod(gradeInput);
                            if (ValidateGrade(grade, gradeBook.maxScoreExam)){
                                gradeBook.examGradesVector.emplace_back(grade);
                                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                                std::cout << ">>";
                                std::cin >> save;
                                if (save == "N"){
                                    innerUserChoice = 0;
                                } else{
                                    std::cout << "Please enter Exam grade: ";
                                    std::cin >> gradeInput;
                                }
                            } else{
                                std::cout << "Invalid grade entered. Max grade allowed is: " << gradeBook.maxScoreExam << "\n";
                                std::cout << "Please enter Exam grade: ";
                                std::cin >> gradeInput;
                            }
                        }
                    }
                }
                else if (innerUserChoice == 5){
                    // Save changes to output file
                    bool fileSaved = false;
                    fileSaved = SaveChanges(fileName, gradeBook);
                    if (fileSaved){
                        std::cout << "------------------------------\n";
                        std::cout << "Data saved to file\n";
                        std::cout << "------------------------------\n";
                    } else {
                        //Terminate program if unable to open file
                        std::cout << "------------------------------\n";
                        std::cout << "Error saving to file";
                        std::cout << "------------------------------\n";
                    }
                }
            }
        }
        else if (userChoice == 2) {
            /*while (innerUserChoice != 5) {}
            std::cout
                    << "[Option 1 Indicator]; Please look at the menu of choices and input the number correlated to your choice: \n\n";*/
            // calculate coursegrade for student1's output
            double courseGrade = gradeBook.calculateCourseGrade(gradeBook.assignmentGradesVector,
                                                          gradeBook.labGradesVector,
                                                          gradeBook.examGradesVector,
                                                          gradeBook.projectGradesVector);
            std::cout<< "Individual Output: \n\n"

                        "Student's Name: " << gradeBook.getStudentName() <<
                     "\nStudent's Course Grade: " << courseGrade << "\n\n";

            std::cout << "Returning to Main Menu \n";
        } else if (userChoice == 3) {
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
                    OutputGradeList(gradeBook, "Assignment", gradeBook.assignmentGradesVector,
                                    gradeBook.assignmentGradesVector.size(), gradeBook.maxScoreAss);
                }
                else if (innerUserChoice == 2) {
                    OutputGradeList(gradeBook, "Lab", gradeBook.labGradesVector,
                                    gradeBook.labGradesVector.size(), gradeBook.maxScoreLab);
                }
                else if (innerUserChoice == 3) {
                    OutputGradeList(gradeBook, "Exam", gradeBook.examGradesVector,
                                    gradeBook.examGradesVector.size(), gradeBook.maxScoreExam);
                }
                else if (innerUserChoice == 4) {
                    OutputGradeList(gradeBook, "Project", gradeBook.projectGradesVector,
                                    gradeBook.projectGradesVector.size(), gradeBook.maxScoreProject);
                }
                else if (innerUserChoice == 5) {
                    std::cout << "Returning you to the main menu... \n";
                }
            }
        }else if (userChoice == 4){
            while(innerUserChoice != 4){
                std::cout << "Course; Please look at the menu and input the number for which full report you would like. \n\n"
                             "1.) Full Report Card and Course Grade (Outputs Every Grade) \n"
                             "2.) Report Card: Averages of All Categories and Course Grade\n"
                             "3.) Course Average Only \n"
                             "4.) Return to the Main Menu \n";
                std::cin >> innerUserChoice;

                if (innerUserChoice == 1){
                    std::cout << "Full Course Report Card: (Every Grade, Category Averages, and Course Average) \n\n";
                    //LAB OUT
                    OutputGradeList(gradeBook, "Lab", gradeBook.labGradesVector,
                                    gradeBook.labGradesVector.size(), gradeBook.maxScoreLab);
                    //ASS OUT
                    OutputGradeList(gradeBook, "Assignment", gradeBook.assignmentGradesVector,
                                    gradeBook.assignmentGradesVector.size(), gradeBook.maxScoreAss);
                    //PROJ OUT
                    OutputGradeList(gradeBook, "Project", gradeBook.projectGradesVector,
                                    gradeBook.projectGradesVector.size(), gradeBook.maxScoreProject);
                    //EXAM OUT
                    OutputGradeList(gradeBook, "Exam", gradeBook.examGradesVector,
                                    gradeBook.examGradesVector.size(), gradeBook.maxScoreExam);
                }
                else if (innerUserChoice == 2){
                    std::cout << "------------------------------\n";
                    std::cout << "Report on Student: Averages for Each Category and Overall: \n\n";
                    //AVG ASS OUT
                    double assAverage = gradeBook.calculateSpecificAverage(gradeBook.assignmentGradesVector, gradeBook.maxSizeAss, gradeBook.maxScoreAss);
                    std::cout << "Assignment Average: "<< assAverage << "\n";
                    //AVG LAB OUT
                    double labAverage = gradeBook.calculateSpecificAverage(gradeBook.labGradesVector, gradeBook.maxSizeLab, gradeBook.maxScoreLab);
                    std::cout << "Lab Average: "<< labAverage << "\n";
                    //AVG EXAM OUT
                    double examAverage = gradeBook.calculateSpecificAverage(gradeBook.examGradesVector, gradeBook.maxSizeExam, gradeBook.maxScoreExam);
                    std::cout << "Exam Average: "<< examAverage << "\n";
                    //AVG PROJ OUT
                    double ProjectAverage = gradeBook.calculateSpecificAverage(gradeBook.projectGradesVector, gradeBook.maxSizeProject, gradeBook.maxScoreProject);
                    std::cout << "Project Average: "<< ProjectAverage << "\n";
                    std::cout << "------------------------------\n";
                    std::cout << "------------------------------\n";
                    //AVG COURSE
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.assignmentGradesVector,
                                                                  gradeBook.labGradesVector,
                                                                  gradeBook.examGradesVector,
                                                                  gradeBook.projectGradesVector);
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 3){
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average Only \n\n";
                    //AVG COURSE
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.assignmentGradesVector,
                                                                  gradeBook.labGradesVector,
                                                                  gradeBook.examGradesVector,
                                                                  gradeBook.projectGradesVector);
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
