#include "Search.h"

int Search::binarySearchByCode(const std::vector<Course>& courses, const std::string& code) 
{
    int low = 0, high = courses.size() - 1;

    while(low <= high) 
    {
        int mid = low + (high - low) / 2;

        if(courses[mid].getCode() == code)
            return mid;
        else if(courses[mid].getCode() < code)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int Search::binarySearchByName(const std::vector<Course>& courses, const std::string& name) 
{
    int low = 0, high = courses.size() - 1;

    while(low <= high) 
    {
        int mid = low + (high - low) / 2;

        if(courses[mid].getName() == name)
            return mid;
        else if(courses[mid].getName() < name)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
