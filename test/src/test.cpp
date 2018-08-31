#include "test.h"

#include "algorithms.hpp"

using namespace io2357911::algorithms;

#define test_sort(sort, arrays) \
for (auto array : arrays) { \
    sort(array); \
    CPPUNIT_ASSERT(std::is_sorted(array.begin(), array.end())); \
}

void Test::sort() {
    array<array<int>> arrays = {
        {},
        {0},
        {9,1},
        {7,2,3,2,9},
        {1,2,3,2,9,55,16,0,2,-25},
    };

    test_sort(bubble_sort, arrays);
    test_sort(count_sort, arrays);
    test_sort(insert_sort, arrays);
    test_sort(merge_sort, arrays);
    test_sort(quick_sort, arrays);
    test_sort(heap_sort, arrays);
}
