#include "Calculator.h"

// Add course
void Calculator::addCourse(const Course& course) 
{ 
    courses.push_back(course); 
}

// Remove course
void Calculator::clearCourses() 
{ 
    courses.clear(); 
}

// Calculator CPA
double Calculator::calculateCPA() const 
{
    double totalPoints = 0;
    int totalCredits = 0;
    for(const auto& course : courses) 
    {
        if(course.getGradePoint() != 0)
        {
            totalPoints += course.getCredits() * course.getGradePoint();
            totalCredits += course.getCredits();
        }
    }
    return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

// Getter courses
const std::vector<Course>& Calculator::getCourses() const 
{
    return courses;
}
