#ifndef SEARCHER_H
#define SEARCHER_H

#include "Course.h"
#include <vector>
#include <string>

// Define Search Class (Using BinarySearch Algorithm)
class Search
{
    public:
        static int binarySearchByCode(const std::vector<Course>& courses, const std::string& code);
        static int binarySearchByName(const std::vector<Course>& courses, const std::string& name);
};

#endif
