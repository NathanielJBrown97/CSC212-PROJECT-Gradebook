#include "gradebook.h"
#include <string>
#include <vector>
//Parameterized constructor to create object with studentName set to string of parameter
GradeBook::GradeBook(std::string name) {
    this->studentName = name;
}

//// SETTERS
void GradeBook::SetStudentName(std::string name){
    this->studentName = name;
}

void GradeBook::SetProject1Grade(double grade){
    this->project1Grade = grade;
}
void GradeBook::SetProject2Grade(double grade) {
    this->project2Grade = grade;
}

/// GETTERS
std::string GradeBook::getStudentName() const {
    return this->studentName;
}

//// HELPERS
//void function taking reference of specific vector, and individual grade.
//adds grade into the specific vector -- this should be flexible and work for all grades
void GradeBook::addGradeToVector(std::vector<double> &SpecificGradeVector, double grade) {
    SpecificGradeVector.push_back(grade);
}

/// METHODS - Calculations
// double that takes in all grades vectors - calls helper calcAvg function to return averages
double GradeBook::calculateCourseGrade(const std::vector<double> &labGradesVector,
                            const std::vector<double> &assignmentGradesVector,
                            const std::vector<double> &projectGradesVector,
                            const std::vector<double> &examGradesVector
                            ){
    const int assignment_weight = 200;
    const int lab_weight = 200;
    const int exam_weight = 100;
    const int project_weight = 500;
    int totalPoints = 1000;
    double pointsEarned = 0;
    double average = 0;

    if (assignmentGradesVector.empty())
        totalPoints -= assignment_weight;
    else{
        for (double grade : this->assignmentGradesVector)
            pointsEarned += grade;
    }
    if (labGradesVector.empty())
        totalPoints -= lab_weight;
    else{
        for (double grade : this->labGradesVector)
            pointsEarned += grade;
    }
    if (examGradesVector.empty())
        totalPoints -= exam_weight;
    else{
        for (double grade : this->examGradesVector)
            pointsEarned += grade;
    }
    if (projectGradesVector.empty())
        totalPoints -= project_weight;
    else if (projectGradesVector.size() == 1){
        totalPoints -= this->maxScoreProject2;
        pointsEarned += this->project1Grade;
    }
    else{
        for (double grade : this->projectGradesVector)
            pointsEarned += grade;
    }

    if (totalPoints > 0){
        average = pointsEarned/totalPoints;
        average *= 100;
    }

    return average;
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
    average = ((sum / maxGrades) / maxScore) * 100;
    return average;
}
//Calculate project category average based on number of grades entered
double GradeBook::calculateProjectAverage() {
    double totalPointsEarned, average, totalPointsAvailable;

    if (this->projectGradesVector.size() == 2){
        totalPointsEarned = this->project1Grade + this->project2Grade;
        totalPointsAvailable = this->maxScoreProjectTotal;
    }
    else if (this->projectGradesVector.size() == 1){
        totalPointsEarned = this->project1Grade;
        totalPointsAvailable = this->maxScoreProject1;
    }

    average = (totalPointsEarned / totalPointsAvailable) * 100;
    return average;
}


