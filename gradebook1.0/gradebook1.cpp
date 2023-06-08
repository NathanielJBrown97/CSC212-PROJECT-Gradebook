#include "OGgradebook.h"
#include <string>        // for std::string
#include <fstream>       // for std::ifstream
#include <sstream>       // for std::istringstream
#include <vector>        // for std::vector

Student::Student(const std::string &name) : studentName(name) {
}

// METHODS

// void method that is passed a filename and a student object to fill - utilizes helper function to add grades to vectors.
void Student::intakeDataFile(const std::string& fileName, Student& student){
    //open file passed to intake - call it file
    std::ifstream file(fileName);
    // string to store each line of hte txt
    std::string currentLine;
    //while there are lines to get - i.e. read each line
    while (std::getline(file, currentLine)){
        //create istringstream variable 'extractVal' to get values from each lnie
        std::istringstream extractValue(currentLine);
        //string to store category name (i.e. hw, assignment, lab, ect)
        std::string categoryName;
        //int for each grade
        int grade;

        // extract categoryName from the istream variable
        extractValue >> categoryName;

        // loop through grades of above category extracting them
        while (extractValue >> grade){
            // if category is homework...
            if (categoryName == "Homework"){
                //call helper function to add this grade to hw vector for our student.
                student.addGradeToVector(student.homeworkGradesVector, grade);
            }
                // if category is assignment...
            else if (categoryName == "Assignment"){
                //call helper function to add this grade to the assignment vector
                student.addGradeToVector(student.assignmentGradesVector, grade);
            }
                // if category is lab...
            else if (categoryName == "Lab"){
                // call helper function to add this grade to the lab vector
                student.addGradeToVector(student.labGradesVector, grade);
            }
                // if category is exam
            else if (categoryName == "Exam"){
                // call helper function to add this grade to the grade vector.
                student.addGradeToVector(student.examGradesVector, grade);
            }
                // if category is project
            else if (categoryName == "Project"){
                // clal helper function to add this grade to the project vector
                student.addGradeToVector(student.projectGradesVector, grade);
            }
        }
    }
    // close the file - because reasons.
    file.close();
}

// double that takes in all grades vectors - calls helper calcAvg function to return averages
double Student::calculateCourseGrade(const std::vector<int> &homeworkGradesVector ,
                            const std::vector<int> &assignmentGradesVector ,
                            const std::vector<int> &labGradesVector ,
                            const std::vector<int> &examGradesVector ,
                            const std::vector<int> &projectGradesVector){
    return (calculateSpecificAverage(homeworkGradesVector) * 0.10)
         + (calculateSpecificAverage(assignmentGradesVector) * 0.20)
         + (calculateSpecificAverage(labGradesVector) * 0.20)
         + (calculateSpecificAverage(examGradesVector) * 0.10)
         + (calculateSpecificAverage(projectGradesVector) * 0.40);
}

// HELPERS

//void function taking reference of specific vector, and individual grade.
//adds grade into the specific vector -- this should be flexible and work for all grades
void Student::addGradeToVector(std::vector<int> &SpecificGradeVector, int grade) {
    SpecificGradeVector.push_back(grade);
}

//double (for precision) helper function, takes specific vector, returns average
double Student::calculateSpecificAverage(const std::vector<int> &SpecificGradeVector){
    double sum = 0;
    // for each grade in specific vector
    for(int eachGrade : SpecificGradeVector){
        //add to sum
        sum += eachGrade;
    }
    // return the average (sum / size of vector)
    return sum / SpecificGradeVector.size();
}

std::string Student::getStudentName() const {
    return studentName;
}
