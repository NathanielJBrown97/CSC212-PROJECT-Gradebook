#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Gradebook class used to contain records associated with a specific student. Private members of student name.
// Public members containing vectors (holding students grades), as well as maxSizes and scores in relation to specific categories.
// ProjectGrade double variables to properly handle appropriate weighting.
// Constructors, Setters, Getters, Helpers, and Methods.
class GradeBook{
private:
    // variable for student name
    std::string studentName;
public:
    // series of vectors to contain the category grades
    /// ass
    std::vector<double> assignmentGradesVector;
    const int maxSizeAss = 4;
    const int maxScoreAss = 50;
    /// lab
    std::vector<double> labGradesVector;
    const int maxSizeLab = 8;
    const int maxScoreLab = 25;
    /// exa
    std::vector<double> examGradesVector;
    const int maxSizeExam = 1;
    const int maxScoreExam = 100;
    /// pro
    std::vector<double> projectGradesVector;
    const int maxSizeProject = 2;
    const int maxScoreProjectTotal = 500;
    const int maxScoreProject1 = 150;
    const int maxScoreProject2 = 350;
    double project1Grade = 0;
    double project2Grade = 0;

    /// Constructor (param - type string) Sets name.
    GradeBook(std::string name);
    /// Setters.
    void SetStudentName(std::string name);
    void SetProject1Grade(double grade); // setter for project 1
    void SetProject2Grade(double grade); // setter for project 2
    /// Getter
    std::string getStudentName() const;

    /// Helpers.
    //helper that will take a passed vector and a grade; and then add the grade into the vector
    void addGradeToVector(std::vector<double> &SpecificGradeVector, double grade);
    /// Methods - Calculations.
    // takes the grade vectors of all categories and outputs overall average.
    double calculateCourseGrade(
                                const std::vector<double> &labGradesVector,
                                const std::vector<double> &assignmentGradesVector,
                                const std::vector<double> &projectGradesVector,
                                const std::vector<double> &examGradesVector);

    //calculate course grade; passed specific vector, returns specific average
    double calculateSpecificAverage(std::vector<double> &SpecificGradeVector, int maxGrades, double maxScore);

    // calculates the project average specifically.
    double calculateProjectAverage();


};