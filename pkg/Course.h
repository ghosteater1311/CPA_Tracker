#ifndef COURSE_H
#define COURSE_H

#include <string>

// Define Course Class
class Course 
{
    private:
        // Attributes
        std::string code;
        std::string name;
        int credits;
        double gradePoint;
        std::string gradeAlphabet;

    public:
        // Constructor
        Course(std::string code, std::string name, int credits, double gradePoint, std::string gradeAlphabet);
        Course(std::string code, std::string name, int credits);

        // Getter & Setter
        std::string getCode() const;
        std::string getName() const;
        int getCredits() const;
        double getGradePoint() const;
        std::string getGradeAlphabet() const;
};

#endif
