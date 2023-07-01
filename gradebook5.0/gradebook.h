#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Student Class used to hold vectors containing category grades (i.e. hw, ass, exam, lab, ect)
class GradeBook{
private:
    // variable for student name
    std::string studentName;
public:
    // series of vectors to contain the category grades
    std::vector<double> assignmentGradesVector;
    const int maxSizeAss = 4;
    const int maxScoreAss = 50;
    std::vector<double> labGradesVector;
    const int maxSizeLab = 8;
    const int maxScoreLab = 25;
    std::vector<double> examGradesVector;
    const int maxSizeExam = 1;
    const int maxScoreExam = 100;
    std::vector<double> projectGradesVector;
    const int maxSizeProject = 2;
    const int maxScoreProjectTotal = 500;
    const int maxScoreProject1 = 150;
    const int maxScoreProject2 = 350;

    //Parameterized constructor of Student object
    GradeBook(std::string name);
    //METHODS


    //Method that will calculate weighted course grade -- will use calcAvg helper -- passed all gradesVectors.
    double calculateCourseGrade(
                                const std::vector<double> &labGradesVector,
                                const std::vector<double> &assignmentGradesVector,
                                const std::vector<double> &projectGradesVector,
                                const std::vector<double> &examGradesVector);
//HELPERS
    //helper to calculate course grade; passed specific vector, returns specific average
    double calculateSpecificAverage(std::vector<double> &SpecificGradeVector, int maxGrades, double maxScore);

    //helper that will take a passed vector and a grade; and then add the grade into the vector
    void addGradeToVector(std::vector<double> &SpecificGradeVector, double grade);
    void SetStudentName(std::string name);
//GETTERS
    std::string getStudentName() const;




};