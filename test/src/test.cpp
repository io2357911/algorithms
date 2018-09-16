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

void Test::polynomial_deriative() {
    struct test {
        std::string polynomial; 
        std::string derivative; 
    };

    std::vector<test> tests = {
        {"x^2+x", "2*x+1"},
        {"2*x^100+100*x^2", "200*x^99+200*x"},
        {"x^10000+x+1", "10000*x^9999+1"},
        {"-x^2-x^3", "-3*x^2-2*x"},
        {"x+x+x+x+x+x+x+x+x+x", "10"},
    };

    for (auto test : tests) {
        CPPUNIT_ASSERT_EQUAL(test.derivative, derivative(test.polynomial));
    }
}

void Test::graph_search() {
    vertex v1, v2;
    edge e12;

    graph<int, int, list_adjacency> lg;
    v1 = lg.add_vertex(1);
    v2 = lg.add_vertex(2);
    e12 = lg.add_edge(v1, v2, 42);

    std::cout << "v1:" << lg(v1) << ", v2:" << lg(v2) << ", e12:" << lg(e12) << std::endl;

    auto vi = lg.vertex_iterator();
    while (vi.next()) {
        std::cout << "vid:" << (*vi).id << ", v:" << lg(*vi) << std::endl; 
    }


    graph<int, int, matrix_adjacency> mg;
    v1 = mg.add_vertex(1);
    v2 = mg.add_vertex(2);
    mg.add_edge(v1, v2, 42);
}
