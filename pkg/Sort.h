#ifndef SORTER_H
#define SORTER_H

#include "Course.h"
#include <vector>

// Define Sort Class (Using HeapSort Algorithm)
class Sort 
{
    public:
        static void heapSortByCode(std::vector<Course>& courses, bool ascending = true);
        static void introSortByCode(std::vector<Course> &courses, bool ascending = true);
        static void introSortByName(std::vector<Course> &courses, bool ascending = true);

    private:
        static void heapify(std::vector<Course>& courses, int n, int i, bool ascending);
};

#endif
