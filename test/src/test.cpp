#include "test.h"

#include "algorithms.hpp"

using namespace io2357911::algorithms;

void Test::sort() {
    array<array<int>> arrays = {
        {},
        {0},
        {9,1},
        {7,2,3,2,9},
        {1,2,3,2,9,55,16,0,2,-25},
    };

    for (auto array : arrays) {
        bubble_sort(array);
        CPPUNIT_ASSERT(std::is_sorted(array.begin(), array.end()));
    }

    for (auto array : arrays) {
        count_sort(array);
        CPPUNIT_ASSERT(std::is_sorted(array.begin(), array.end()));
    }

    for (auto array : arrays) {
        insert_sort(array);
        CPPUNIT_ASSERT(std::is_sorted(array.begin(), array.end()));
    }

    for (auto array : arrays) {
        merge_sort(array);
        CPPUNIT_ASSERT(std::is_sorted(array.begin(), array.end()));
    }

}
