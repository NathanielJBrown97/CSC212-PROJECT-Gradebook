#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// void method that is passed a filename and a student object to fill - utilizes helper function to add grades to vectors.
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
        std::cout << "Error opening file.\n";
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
    std::cout << "\nManual Intake; Please input the number correlated with the category you would like to update: \n"
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
    double average = 0.0;
    if (!gradesVec.empty()){
        average = gradeBook.calculateSpecificAverage(gradesVec, numGrades, maxScore);
    }
    std::cout << "\n" << type <<  " Average: " << average << "\n\n";
}

bool ValidateGrade(double grade, double maxGrade){
    bool valid = false;
    if (grade <= maxGrade){
        valid = true;
    }
    return valid;
}

int InsertNewGrade(std::string category, std::vector<double> &gradesVec, int maxSize, double maxScore, int menuChoice) {
    int newMenuChoice = menuChoice;
    std::string gradeInput;
    if (gradesVec.size() == maxSize) {
        std::cout << "Max number of " << category << " grades have been entered.\n";
    } else {
        std::cout << "Please enter " << category << " grade: ";
        std::cin >> gradeInput;
        std::string save;
        while (gradesVec.size() != maxSize && newMenuChoice == menuChoice) {
            double grade = std::stod(gradeInput);
            if (ValidateGrade(grade, maxScore)) {
                //if (category == "Project"){
                //do stuff
                //check vector for existing grades
                //check value
                //
                //}
                gradesVec.emplace_back(grade);
                std::cout << "Enter Y if you have another grade to enter or N to return to menu\n";
                std::cout << ">>";
                std::cin >> save;
                if (save == "N") {
                    newMenuChoice = 0;
                } else {
                    std::cout << "Please enter " << category << " grade: ";
                    std::cin >> gradeInput;
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
    //create object of the student class
    GradeBook gradeBook("");

    //extract filename from CLA
//    std::string fileName = argv[1];
//    std::string fileName = "../test.txt";
//    std::string fileName = "../test_empty.txt";
//    std::string fileName = "../test_varying_grades.txt";
    std::string fileName = "../input.txt";
    // initiate intake of student1 txt file; to fill student obj's vectors
    int report_update;
    std::string studentName;
    int userChoice = 0;
    int innerUserChoice = 0;


    //Process input file
    IntakeDataFile(fileName, gradeBook);

    //Prompt user to enter student name if not read from txt file
    while (gradeBook.getStudentName() == ""){
        std::cout << "Please enter student name: ";
        std::getline(std::cin,studentName);
        gradeBook.SetStudentName(studentName);
    }

    //Display menus allowing user to enter grade info for a student
    //or generate reports
    while (userChoice != 5) {
        DisplayMainMenu();
        std::cin >> userChoice;
        std::cout << "\n";
        std::cout << "------------------------------\n";
        if (userChoice == 1){
            while (innerUserChoice != 6){
                innerUserChoice = DisplayGradeInputMenu();
                if (innerUserChoice == 1)
                    innerUserChoice = InsertNewGrade("Lab", gradeBook.labGradesVector,
                                                     gradeBook.maxSizeLab, gradeBook.maxScoreLab, innerUserChoice);
                else if (innerUserChoice == 2)
                    innerUserChoice = InsertNewGrade("Assignment", gradeBook.assignmentGradesVector,
                                                     gradeBook.maxSizeAss, gradeBook.maxScoreAss, innerUserChoice);
                else if (innerUserChoice == 3)
                    innerUserChoice = InsertNewGrade("Project", gradeBook.projectGradesVector,
                                                     gradeBook.maxSizeProject, gradeBook.maxScoreProjectTotal, innerUserChoice);
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
        else if (userChoice == 2) {
            // calculate coursegrade for student1's output
            double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                gradeBook.assignmentGradesVector,
                                                                gradeBook.projectGradesVector,
                                                                gradeBook.examGradesVector);
            std::cout<< "Individual Output: \n\n"
                        "Student's Name: " << gradeBook.getStudentName() <<
                        "\nStudent's Course Grade: " << courseGrade << "\n\n";
            std::cout << "Returning to Main Menu \n";
        } else if (userChoice == 3) {
            while (innerUserChoice != 5) {
                std::cout << "------------------------------\n";
                std::cout << "Select Specific Category; Please look at the menu of choices and input the number correlated to your choice: \n\n"
                             "1.) Report all Lab Grades and Total \n"
                             "2.) Report all Assignment Grades and Total \n"
                             "3.) Report all Project Grades and Total \n"
                             "4.) Report all Exam Grades and Total \n"
                             "5.) Return to Main Menu \n";
                std::cout << ">>";
                std::cin >> innerUserChoice;
                std::cout << "------------------------------\n";

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
        }else if (userChoice == 4){
            while(innerUserChoice != 4){
                std::cout << "Course; Please look at the menu and input the number for which full report you would like. \n\n"
                             "1.) Full Report Card and Course Grade (Outputs Every Grade) \n"
                             "2.) Report Card: Averages of All Categories and Course Grade\n"
                             "3.) Course Average Only \n"
                             "4.) Return to the Main Menu \n";
                std::cout << ">>";
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
                                    gradeBook.projectGradesVector.size(), gradeBook.maxScoreProjectTotal);
                    //EXAM OUT
                    OutputGradeList(gradeBook, "Exam", gradeBook.examGradesVector,
                                    gradeBook.examGradesVector.size(), gradeBook.maxScoreExam);
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 2){
                    std::cout << "------------------------------\n";
                    std::cout << "Report on Student: Averages for Each Category and Overall: \n\n";
                    //AVG LAB OUT
                    double labAverage = gradeBook.calculateSpecificAverage(gradeBook.labGradesVector,
                                                                           gradeBook.maxSizeLab,
                                                                           gradeBook.maxScoreLab);
                    std::cout << "Lab Average: "<< labAverage << "\n";
                    //AVG ASS OUT
                    double assAverage = gradeBook.calculateSpecificAverage(gradeBook.assignmentGradesVector,
                                                                           gradeBook.maxSizeAss,
                                                                           gradeBook.maxScoreAss);
                    std::cout << "Assignment Average: "<< assAverage << "\n";
                    //AVG PROJ OUT
                    double ProjectAverage = gradeBook.calculateSpecificAverage(gradeBook.projectGradesVector,
                                                                               gradeBook.maxSizeProject,
                                                                               gradeBook.maxScoreProjectTotal);
                    std::cout << "Project Average: "<< ProjectAverage << "\n";
                    //AVG EXAM OUT
                    double examAverage = gradeBook.calculateSpecificAverage(gradeBook.examGradesVector,
                                                                            gradeBook.maxSizeExam,
                                                                            gradeBook.maxScoreExam);
                    std::cout << "Exam Average: "<< examAverage << "\n";
                    std::cout << "------------------------------\n";
                    std::cout << "------------------------------\n";
                    //AVG COURSE
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 3){
                    std::cout << "------------------------------\n";
                    std::cout << "Class Average Only \n\n";
                    //AVG COURSE
                    double courseGrade = gradeBook.calculateCourseGrade(gradeBook.labGradesVector,
                                                                        gradeBook.assignmentGradesVector,
                                                                        gradeBook.projectGradesVector,
                                                                        gradeBook.examGradesVector);
                    std::cout << "Class Average: " << courseGrade << "\n";
                    std::cout << "------------------------------\n";
                }
                else if (innerUserChoice == 4)
                    std::cout << "Returning to Main Menu... \n";
            }
        }
        else if (userChoice == 5) {
            std::cout << "Exiting Gradebook Program... ";
        }
    }
}