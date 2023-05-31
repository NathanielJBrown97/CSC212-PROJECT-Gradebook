#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Student Class used to hold vectors containing category grades (i.e. hw, ass, exam, lab, ect)
class Student{
public:
    // variable for student name
    std::string studentName;
    // series of vectors to contain the category grades
    std::vector<int> homeworkGradesVector; // delete later

    std::vector<int> assignmentGradesVector;
    const int maxSizeAss = 4;
    std::vector<int> labGradesVector;
    const int maxSizeLab = 8;
    std::vector<int> examGradesVector;
    const int maxSizeExam = 1;
    std::vector<int> projectGradesVector;
    const int maxSizeProject = 2;

    //Parameterized constructor of Student object
    Student(const std::string &name);
//METHODS
    //Method that will read the txt file and sort the information into related vector; using addGrade helper function
    void intakeDataFile(const std::string& fileName, Student& student);

    //Method that will calculate weighted course grade -- will use calcAvg helper -- passed all gradesVectors.
    double calculateCourseGrade(const std::vector<int> &homeworkGradesVector ,
                                const std::vector<int> &assignmentGradesVector ,
                                const std::vector<int> &labGradesVector ,
                                const std::vector<int> &examGradesVector ,
                                const std::vector<int> &projectGradesVector);
//HELPERS
    //helper to calculate course grade; passed specific vector, returns specific average
    double calculateSpecificAverage(const std::vector<int> &SpecificGradeVector);

    //helper that will take a passed vector and a grade; and then add the grade into the vector
    void addGradeToVector(std::vector<int> &SpecificGradeVector, int grade);

//GETTERS
    std::string getStudentName() const;




};