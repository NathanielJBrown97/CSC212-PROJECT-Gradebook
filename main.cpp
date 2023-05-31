#include "gradebook.h"
#include <iostream>
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
    Student student1("Nathaniel Brown");

    //extract filename from CLA
    std::string fileName = argv[1];

    // initiate intake of student1 txt file; to fill student obj's vectors
    student1.intakeDataFile(fileName, student1);

    // calculate coursegrade for student1's output
    double courseGrade = student1.calculateCourseGrade(student1.homeworkGradesVector,
                                                       student1.assignmentGradesVector,
                                                       student1.labGradesVector,
                                                       student1.examGradesVector,
                                                       student1.projectGradesVector);

    // Output Values
    std::cout << "Student Name: " << student1.getStudentName() << "\n";
    std::cout << "Overall Course Grade: " << courseGrade << "\n";
}


