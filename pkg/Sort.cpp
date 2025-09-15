#include "Sort.h"
#include <algorithm>

void Sort::heapify(std::vector<Course>& courses, int n, int i, bool ascending) 
{
    int extreme = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    auto compare = [&](const Course& a, const Course& b) 
    {
        return ascending ? (a.getCode() > b.getCode()) : (a.getCode() < b.getCode());
    };

    if(left < n && compare(courses[left], courses[extreme]))
        extreme = left;

    if(right < n && compare(courses[right], courses[extreme]))
        extreme = right;

    if(extreme != i) 
    {
        std::swap(courses[i], courses[extreme]);
        heapify(courses, n, extreme, ascending);
    }
}

void Sort::heapSortByCode(std::vector<Course>& courses, bool ascending) 
{
    int n = courses.size();

    for(int i = n / 2 - 1; i >= 0; i--) heapify(courses, n, i, ascending);

    for(int i = n - 1; i > 0; i--) 
    {
        std::swap(courses[0], courses[i]);
        heapify(courses, i, 0, ascending);
    }
}

// IntroSort (std::sort) by Code
void Sort::introSortByCode(std::vector<Course> &courses, bool ascending) {
    if (ascending) {
        std::sort(courses.begin(), courses.end(),
                  [](const Course &a, const Course &b) {
                      return a.getCode() < b.getCode();
                  });
    } else {
        std::sort(courses.begin(), courses.end(),
                  [](const Course &a, const Course &b) {
                      return a.getCode() > b.getCode();
                  });
    }
}

// IntroSort (std::sort) by Name
void Sort::introSortByName(std::vector<Course> &courses, bool ascending) {
    if (ascending) {
        std::sort(courses.begin(), courses.end(),
                  [](const Course &a, const Course &b) {
                      return a.getName() < b.getName();
                  });
    } else {
        std::sort(courses.begin(), courses.end(),
                  [](const Course &a, const Course &b) {
                      return a.getName() > b.getName();
                  });
    }
}