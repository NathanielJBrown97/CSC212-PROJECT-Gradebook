#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Read input file and extract student data and grade data
void IntakeDataFile(const std::string& fileName, GradeBook& gradeBook){
    std::ifstream inputFile;
    //Open file
    inputFile.open(fileName);
    if (inputFile.is_open()){
        std::string line;
        std::string category;
        std::string fname;
        std::string lname;
        double grade;

        while (inputFile){
            //Read line from file
            std::istringstream extractValue(line);
            //Get line header
            extractValue >> category;
            //Evaluate data based on line headers, saving data to gradebook object
            if (category == "Name"){
                extractValue >> fname >> lname;
                gradeBook.SetStudentName(fname + " " + lname);
            } else if (category == "Labs"){
                while(extractValue >> grade)
                    gradeBook.labGradesVector.emplace_back(grade);
            } else if (category == "Assignments"){
                while(extractValue >> grade)
                    gradeBook.assignmentGradesVector.emplace_back(grade);
            } else if (category == "Projects"){
                while(extractValue >> grade)
                    gradeBook.projectGradesVector.emplace_back(grade);
            } else if (category == "Exams"){
                while(extractValue >> grade)
                    gradeBook.examGradesVector.emplace_back(grade);
            }
            getline(inputFile, line);
        }
        //Close file
        inputFile.close();
    }else
        //Output error message if unable to open file
        std::cout << "Error opening file.\n";
}

//Save user input to output file
bool SaveChanges(std::string filename, GradeBook gradeBook) {
    std::ofstream outputFile;
    bool saved = false;

    //Open output file
    outputFile.open(filename);

    if (outputFile.is_open()) {
        //Write content to output file
        outputFile << "Name " << gradeBook.getStudentName() << std::endl;

        outputFile << "Labs ";
        for (int i = 0; i < gradeBook.labGradesVector.size(); i++)
            outputFile << gradeBook.labGradesVector[i] << " ";
        outputFile << std::endl;

        outputFile << "Assignments ";
        for (int i = 0; i < gradeBook.assignmentGradesVector.size(); i++)
            outputFile << gradeBook.assignmentGradesVector[i] << " ";
        outputFile << std::endl;

        outputFile << "Projects ";
        for (int i = 0; i < gradeBook.projectGradesVector.size(); i++) {
            outputFile << gradeBook.projectGradesVector[i] << " ";
        }
        outputFile << std::endl;

        outputFile << "Exams ";
        for (int i = 0; i < gradeBook.examGradesVector.size(); i++)
            outputFile << gradeBook.examGradesVector[i] << " ";
        outputFile << std::endl;

        outputFile.close();
        saved = true;
    } else {
        saved = false;
    }
    return saved;
}

//Display submenu based on input given from main menu returning user choice
int DisplayInnerMenu(int menuChoice){
    int input;
    if (menuChoice == 1)
        std::cout << "\nManual Intake; Please input the number correlated with the category you would like to update: \n"
                 "1.) Labs \n"
                 "2.) Assignments \n"
                 "3.) Projects \n"
                 "4.) Exam \n"
                 "5.) Save Changes \n"
                 "6.) Return to Main Menu \n";
    else if (menuChoice == 3)
        std::cout << "Select Specific Category; Please look at the menu of choices and input the number correlated to your choice: \n\n"
                     "1.) Report all Lab Grades and Total \n"
                     "2.) Report all Assignment Grades and Total \n"
                     "3.) Report all Project Grades and Total \n"
                     "4.) Report all Exam Grades and Total \n"
                     "5.) Return to Main Menu \n";
    else if (menuChoice == 4)
        std::cout << "Course; Please look at the menu and input the number for which full report you would like. \n\n"
                     "1.) Full Report Card and Course Grade (Outputs Every Grade) \n"
                     "2.) Report Card: Averages of All Categories and Course Grade\n"
                     "3.) Course Average Only \n"
                     "4.) Return to the Main Menu \n";

    std::cout << ">>";
    std::cin >> input;
    return input;
}

//Displays main menu
void DisplayMainMenu(){
    std::cout << "Please look at the menu of choices and input the number correlated to your choice: \n\n"
                 "1.) Manual Intake \n"
                 "2.) Individual: Report Student's Name and Overall Course Grade \n"
                 "3.) Category: Report Specific Category Grades \n"
                 "4.) Course: Full Course Report \n"
                 "5.) End Program \n";
    std::cout << ">>";
}

//Displays list of grades and average for each category
//Passed our GradeBook Object, string indicating category, a vector of the grades, int representing a number of grades, and a double of the max score for this category
void OutputGradeList(GradeBook gradeBook, std::string type, std::vector<double> gradesVec, int numGrades, double maxScore){
    double average = 0.0;

    //Output list of grades for each category
    std::cout << "------------------------------\n";
    std::cout << type << " Grade List: ";
    for (int grade = 0; grade < numGrades; grade++){
        std::cout << gradesVec[grade] << " ";
    }
    //Perform average calculation for each category
    if (!gradesVec.empty()){
        if (type != "Project")
            average = gradeBook.calculateSpecificAverage(gradesVec, numGrades, maxScore);
        else
            average = gradeBook.calculateProjectAverage();
    }
    //Display average for each category
    std::cout << "\n" << type <<  " Average: " << round(average) << "%" << "\n\n";
}

//Validate grade input based on maximum score possible
bool ValidateGrade(double grade, double maxGrade){
    bool valid = false;
    if (grade <= maxGrade && grade >= 0)
        valid = true;

    return valid;
}

//Save grade to gradebook
//Passed string for category indication, vector containing grades, an int for the maximum entries for this category, double for the maximum score, and the int representing the menu choice.
int InsertNewGrade(std::string category, std::vector<double> &gradesVec, int maxSize, double maxScore, int menuChoice) {
    int newMenuChoice = menuChoice;
    std::string gradeInput;

    //Check that maximum number of grades has not been entered for category
    if (gradesVec.size() == maxSize)
        std::cout << "Max number of " << category << " grades have been entered.\n";
    else {
        //Prompt user to enter grade
        std::cout << "Please enter " << category << " grade: ";
        std::cin >> gradeInput;
        std::string save;

        //Allow user to enter multiple grades per category
        while (gradesVec.size() != maxSize && newMenuChoice == menuChoice) {
            double grade = std::stod(gradeInput);

            //Check if valid grade entered
            if (ValidateGrade(grade, maxScore)) {
                gradesVec.emplace_back(grade);
                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                std::cout << ">>";
                std::cin >> save;
                if (save == "N") {
                    newMenuChoice = 0;
                } else {
                    if (gradesVec.size() == maxSize)
                        std::cout << "Max number of " << category << " grades have been entered.\n";
                    else{
                        std::cout << "Please enter " << category << " grade: ";
                        std::cin >> gradeInput;
                    }
                }
            } else {
                std::cout << "Invalid grade entered. Max grade allowed is: " << maxScore << "\n";
                std::cout << "Please enter " << category << " grade: ";
                std::cin >> gradeInput;
            }
        }
    }
    return newMenuChoice;
}

int main(int argc, char* argv[]){
    //Extract filename from CLA
    std::string fileName = argv[1];
    //Initialize gradebook
    GradeBook gradeBook("");

    std::string studentName;
    int userChoice = 0;
    int enterProjectGrade = 0;

    //Process input file
    IntakeDataFile(fileName, gradeBook);

    //Prompt user to enter student name if not read from txt file
    while (gradeBook.getStudentName() == ""){
        std::cout << "Please enter student name: ";
        std::getline(std::cin,studentName);
        gradeBook.SetStudentName(studentName);
    }

    //Check if input file contained project grades and assign to project grade variables
    if (gradeBook.projectGradesVector.size() == 2){
        gradeBook.project1Grade = gradeBook.projectGradesVector[0];
        gradeBook.project2Grade = gradeBook.projectGradesVector[1];
    }
    else if (gradeBook.projectGradesVector.size() == 1)
        gradeBook.project1Grade = gradeBook.projectGradesVector[0];

    //Display menus allowing user to enter grade info for a student or generate reports
    while (userChoice != 5) {
        int innerUserChoice = 0;

        DisplayMainMenu();
        std::cin >> userChoice;
        std::cout << "\n";
        std::cout << "------------------------------\n";


        /// MANUAL INTAKE
        if (userChoice == 1){
            while (innerUserChoice != 6){
                //Display submenu to enter grades for each category
                innerUserChoice = DisplayInnerMenu(1);
                if (innerUserChoice == 1)
                    innerUserChoice = InsertNewGrade("Lab", gradeBook.labGradesVector,
                                                     gradeBook.maxSizeLab, gradeBook.maxScoreLab, innerUserChoice);
                else if (innerUserChoice == 2)
                    innerUserChoice = InsertNewGrade("Assignment", gradeBook.assignmentGradesVector,
                                                     gradeBook.maxSizeAss, gradeBook.maxScoreAss, innerUserChoice);
                else if (innerUserChoice == 3) {
                    while (enterProjectGrade != 3) {
                        std::cout << "\n------------------------------\n";
                        std::cout << "Which Project Grade Would You Like To Add? \n"
                                     "NOTE: you must ensure you are modifying the correct Project values listed below to maintain accuracy of report. Failure to do so is your own doing. \nOnly update 1 Project1 grade and 1 Project2 grade\n"
                                     "1.) Project 1: (Maximum Points 150) \n"
                                     "2.) Project 2: (Maximum Points 350) \n"
                                     "3.) Return to Previous Menu \n>>";
                        std::cin >> enterProjectGrade;
                        if (enterProjectGrade == 1) {
                            double grade;
                            if (gradeBook.project1Grade > 0){
                                std::cout << "This gradebook already contains a grade for project 1. \n";
                            }else{
                                std::cout << "You have selected Project 1. Enter a grade between 0 and 150: ";
                                std::cin >> grade;
                                while (!ValidateGrade(grade, gradeBook.maxScoreProject1)){
                                    std::cout << "This is not a valid input... input a grade between 0 and 150: ";
                                    std::cin >> grade;
                                }
                                // conditional to ensure only modify vector/grade values if size < 2
                                if (gradeBook.projectGradesVector.size() < 2) {
                                    // set project member to grade value -- for calc
                                    gradeBook.SetProject1Grade(grade);
                                    //add grade to vector
                                    gradeBook.addGradeToVector(gradeBook.projectGradesVector, grade);
                                } else {
                                    std::cout << "There are already two grades in Projects... you cannot add more. \n";
                                    std::cout << "------------------------------\n";
                                }
                            }
                        } else if (enterProjectGrade == 2) {
                            double grade;
                            if (gradeBook.project2Grade > 0){
                                std::cout << "This gradebook already contains a grade for Project 2. \n";
                            }else{
                                std::cout << "You have selected Project 2. Enter a grade between 0 and 350: \n";
                                std::cin >> grade;
                                while (!ValidateGrade(grade, gradeBook.maxScoreProject2)){
                                    std::cout << "This is not a valid input... input a grade between 0 and 350: \n";
                                    std::cin >> grade;
                                }
                                // set project member to grade value -- for calc
                                if (gradeBook.projectGradesVector.size() < 2) {
                                    gradeBook.SetProject2Grade(grade);
                                    //add grade to vector
                                    gradeBook.addGradeToVector(gradeBook.projectGradesVector, grade);
                                } else {
                                    std::cout << "There are already two grades in Projects... you cannot add more. \n";
                                    std::cout << "------------------------------\n";
                                }
                            }
                        } else if (enterProjectGrade == 3) {
                            // display message and while loop will terminate
                            std::cout << "Returning to previous menu...\n";
                        } else {
                            std::cout << "Invalid choice! Select a number from 1-3. \n";
                        }
                    }
                    enterProjectGrade = 0;
                }
                else if (innerUserChoice == 4)
                    innerUserChoice = InsertNewGrade("Exam", gradeBook.examGradesVector,
                                                     gradeBook.maxSizeExam, gradeBook.maxScoreExam, innerUserChoice);
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
        //// INDIVIDUAL OUTPUT
        else if (userChoice == 2) {
            // Calculate coursegrade for student and display report
            double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                gradeBook.assignmentGradesVector,
                                                                gradeBook.projectGradesVector,
                                                                gradeBook.examGradesVector);
            std::cout<< "Individual Output: \n\n"
                        "Student's Name: " << gradeBook.getStudentName() <<
                        "\nStudent's Course Grade: " << round(courseGrade) << "%" << "\n\n";
            std::cout << "Returning to Main Menu \n";
        }
        //// CATEGORY OUTPUT
        else if (userChoice == 3) {
            while (innerUserChoice != 5) {
                std::cout << "------------------------------\n";
                innerUserChoice = DisplayInnerMenu(3);
                std::cout << "------------------------------\n";

                //Display grade list and average for selected category
                if (innerUserChoice == 1)
                    OutputGradeList(gradeBook, "Lab", gradeBook.labGradesVector,
                                    gradeBook.labGradesVector.size(), gradeBook.maxScoreLab);
                else if (innerUserChoice == 2)
                    OutputGradeList(gradeBook, "Assignment", gradeBook.assignmentGradesVector,
                                    gradeBook.assignmentGradesVector.size(), gradeBook.maxScoreAss);
                else if (innerUserChoice == 3)
                    OutputGradeList(gradeBook, "Project", gradeBook.projectGradesVector,
                                    gradeBook.projectGradesVector.size(), gradeBook.maxScoreProjectTotal);
                else if (innerUserChoice == 4)
                    OutputGradeList(gradeBook, "Exam", gradeBook.examGradesVector,
                                    gradeBook.examGradesVector.size(), gradeBook.maxScoreExam);
                else if (innerUserChoice == 5)
                    std::cout << "Returning you to the main menu... \n";
            }
        }
        //// COURSE OUTPUT
        else if (userChoice == 4){
            while(innerUserChoice != 4){
                innerUserChoice = DisplayInnerMenu(4);

                //Display all grades for every category and all averages including course average
                /// COURSE -  FULL REPORT
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
                                    gradeBook.projectGradesVector.size(), gradeBook.maxScoreProjectTotal);
                    //EXAM OUT
                    OutputGradeList(gradeBook, "Exam", gradeBook.examGradesVector,
                                    gradeBook.examGradesVector.size(), gradeBook.maxScoreExam);
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average: " << round(courseGrade) << "%" << "\n";
                    std::cout << "------------------------------\n";
                }
                /// COURSE - AVERAGES ONLY & COURSE OVERALL
                else if (innerUserChoice == 2){
                    double labAverage, assAverage, projectAverage, examAverage, courseGrade = 0;

                    //Display all averages including course average
                    std::cout << "------------------------------\n";
                    std::cout << "Report on Student: Averages for Each Category and Overall: \n\n";
                    //AVG LAB OUT
                    if (!gradeBook.labGradesVector.empty())
                        labAverage = gradeBook.calculateSpecificAverage(gradeBook.labGradesVector,
                                                                           gradeBook.labGradesVector.size(),
                                                                           gradeBook.maxScoreLab);
                    std::cout << "Lab Average: "<< round(labAverage) << "%" << "\n";
                    //AVG ASS OUT
                    if (!gradeBook.assignmentGradesVector.empty())
                        assAverage = gradeBook.calculateSpecificAverage(gradeBook.assignmentGradesVector,
                                                                           gradeBook.assignmentGradesVector.size(),
                                                                           gradeBook.maxScoreAss);
                    std::cout << "Assignment Average: "<< round(assAverage) << "%" << "\n";
                    if (!gradeBook.projectGradesVector.empty())
                        projectAverage = gradeBook.calculateProjectAverage();
                    std::cout << "Project Average: "<< round(projectAverage) << "%" << "\n";
                    //AVG EXAM OUT
                    if (!gradeBook.examGradesVector.empty())
                        examAverage = gradeBook.calculateSpecificAverage(gradeBook.examGradesVector,
                                                                            gradeBook.examGradesVector.size(),
                                                                            gradeBook.maxScoreExam);
                    std::cout << "Exam Average: "<< round(examAverage) << "%" << "\n";
                    std::cout << "------------------------------\n";
                    std::cout << "------------------------------\n";
                    //AVG COURSE
                    courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "Class Average: " << round(courseGrade) << "%" << "\n";
                    std::cout << "------------------------------\n";
                }
                /// COURSE - CLASS AVERAGE ONLY
                else if (innerUserChoice == 3){
                    //Display course average only
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average Only \n\n";
                    //AVG COURSE
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "Class Average: " << round(courseGrade) << "%" << "\n";
                    std::cout << "------------------------------\n";
                }
                /// COURSE - RETURN
                else if (innerUserChoice == 4)
                    std::cout << "Returning to Main Menu... \n";
            }
        }
        /// EXIT PROGRAM CONDITIONAL
        else if (userChoice == 5) {
            std::cout << "Exiting Gradebook Program... ";
        }
    }
}