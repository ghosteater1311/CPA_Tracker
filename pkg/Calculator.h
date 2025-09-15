#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include "Course.h"

// Define Calculator Class
class Calculator 
{
    private:
        // Attributes
        std::vector<Course> courses;

    public:
        // Methods
        void addCourse(const Course& course);
        void clearCourses();
        double calculateCPA() const;
        const std::vector<Course>& getCourses() const;
};

#endif