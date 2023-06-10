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

// double that takes in all grades vectors - calls helper calcAvg function to return averages
double GradeBook::calculateCourseGrade(const std::vector<double> &assignmentGradesVector ,
                            const std::vector<double> &labGradesVector ,
                            const std::vector<double> &examGradesVector ,
                            const std::vector<double> &projectGradesVector){
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
void GradeBook::addGradeToVector(std::vector<double> &SpecificGradeVector, double grade) {
    SpecificGradeVector.push_back(grade);
}

//double (for precision) helper function, takes specific vector, returns average
double GradeBook::calculateSpecificAverage(std::vector<double> &SpecificGradeVector, int maxGrades, double maxScore){
    double sum = 0;
    double average = 0;

    // for each grade in specific vector
    for(int eachGrade : SpecificGradeVector){
        //add to sum
        sum += eachGrade;
    }
    // return the average (sum / size of vector)
//    return sum / SpecificGradeVector.size();
    average = ((sum / maxGrades) / maxScore) * 100;
    return average;
}

std::string GradeBook::getStudentName() const {
    return this->studentName;
}
