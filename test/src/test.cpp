#include "test.h"

#include "algorithm.hpp"

using namespace io2357911;

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

#define test_matrix_sorted_find(matrix, values, result) \
for (size_t row = 0; row < values.rows(); row++) { \
    for (size_t col = 0; col < values.columns(); col++) { \
        CPPUNIT_ASSERT_EQUAL(sorted_find(matrix, values[row][col]), result); \
    } \
}

void Test::find() {
    ::matrix<int> matrix;
    ::matrix<int> values;
    bool result;

    matrix = {
        {15,20,40,85},
        {20,35,80,95},
        {30,55,95,105},
        {40,80,100,120},
    };
    values = matrix;
    result = true;
    test_matrix_sorted_find(matrix, values, result);

    matrix = {
        {15,20,40,85},
        {20,35,80,95},
        {30,55,95,105},
        {40,80,100,120},
    };
    values = {
        {1,2,3,4,82,83,121,200},
    };
    result = false;
    test_matrix_sorted_find(matrix, values, result);
}
