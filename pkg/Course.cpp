#include "Course.h"

// Constructor
Course::Course(std::string code, std::string name, int credits, double gradePoint, std::string gradeAlphabet)
    : code(code), name(name), credits(credits), gradePoint(gradePoint), gradeAlphabet(gradeAlphabet) {}
        
Course::Course(std::string code, std::string name, int credits)
    : code(code), name(name), credits(credits) {}

// Getter and Setter
std::string Course::getCode() const { return code; }
std::string Course::getName() const { return name; }
int Course::getCredits() const { return credits; }
double Course::getGradePoint() const { return gradePoint; }
std::string Course::getGradeAlphabet() const { return gradeAlphabet; }