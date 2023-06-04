#include "gradebook.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

GradeBook::GradeBook(const std::string &name) {
}

// METHODS
void GradeBook::SetStudentName(std::string name){
    this->studentName = name;
}
// void method that is passed a filename and a student object to fill - utilizes helper function to add grades to vectors.
void GradeBook::intakeDataFile(const std::string& fileName, GradeBook& gradeBook){
    std::ifstream inputFile;
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
//        return 1;
    }
}

// double that takes in all grades vectors - calls helper calcAvg function to return averages
double GradeBook::calculateCourseGrade(const std::vector<int> &assignmentGradesVector ,
                            const std::vector<int> &labGradesVector ,
                            const std::vector<int> &examGradesVector ,
                            const std::vector<int> &projectGradesVector){
    int totalPoints = 1000;
    double pointsEarned = 0;
    double average = 0;

    if (assignmentGradesVector.empty())
        totalPoints -= 200;
    else{
        for (double grade : this->assignmentGradesVector){
            pointsEarned += grade;
        }
    }
    if (labGradesVector.empty())
        totalPoints -= 200;
    else{
        for (double grade : this->labGradesVector){
            pointsEarned += grade;
        }
    }
    if (examGradesVector.empty())
        totalPoints -= 100;
    else{
        for (double grade : this->examGradesVector){
            pointsEarned += grade;
        }
    }
    if (projectGradesVector.empty())
        totalPoints -= 500;
    else{
        for (double grade : this->projectGradesVector){
            pointsEarned += grade;
        }
    }


    if (totalPoints > 0){
        average = pointsEarned/totalPoints;
        average *= 100;
    }

    return average;
}

// HELPERS

//void function taking reference of specific vector, and individual grade.
//adds grade into the specific vector -- this should be flexible and work for all grades
void GradeBook::addGradeToVector(std::vector<int> &SpecificGradeVector, int grade) {
    SpecificGradeVector.push_back(grade);
}

//double (for precision) helper function, takes specific vector, returns average
double GradeBook::calculateSpecificAverage(const std::vector<int> &SpecificGradeVector, int maxGrades){
    double sum = 0;
    // for each grade in specific vector
    for(int eachGrade : SpecificGradeVector){
        //add to sum
        sum += eachGrade;
    }
    // return the average (sum / size of vector)
//    return sum / SpecificGradeVector.size();
return sum / maxGrades;
}

std::string GradeBook::getStudentName() const {
    return this->studentName;
}
