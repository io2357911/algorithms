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

    /*
     * 1-2-3  7
     * | | |  |
     * 4-5-6  8
     */

    using graph_t = graph<int, int, list_adjacency>;
    //using graph_t = graph<int, int, matrix_adjacency>;

    graph_t g;
    vertex v1 = g.add_vertex(1);
    vertex v2 = g.add_vertex(2);
    vertex v3 = g.add_vertex(3);
    vertex v4 = g.add_vertex(4);
    vertex v5 = g.add_vertex(5);
    vertex v6 = g.add_vertex(6);
    vertex v7 = g.add_vertex(7);
    vertex v8 = g.add_vertex(8);
    g.add_edge(v1, v2, 12);
    g.add_edge(v1, v4, 14);
    g.add_edge(v2, v3, 23);
    g.add_edge(v2, v5, 25);
    g.add_edge(v3, v6, 36);
    g.add_edge(v4, v5, 45);
    g.add_edge(v5, v6, 56);
    g.add_edge(v7, v8, 78);
    
    if (1) {
        std::cout << "vertex iterator:" << std::endl;

        auto vi = g.vertex_iterator();
        while (vi.next()) {
            std::cout << 
                "vid:" << (*vi).id << "," << 
                "v:" << g(*vi) << std::endl; 
        }
        std::cout << std::endl;
    }
    
    if (1) {
        std::cout << "vertex edge iterator:" << std::endl;

        auto ei = g.edge_iterator(v1);
        while (ei.next()) {
            std::cout << 
                "eid:" << (*ei).id << ", " 
                "v1:" << (*ei).src.id << ", " 
                "v2:" << (*ei).dest.id << ", "  
                "e:" << g(*ei) << std::endl; 
        }
        std::cout << std::endl;
    }

    if (1) {
        std::cout << "edge iterator:" << std::endl;

        auto ei = g.edge_iterator();
        while (ei.next()) {
            std::cout << 
                "eid:" << (*ei).id << ", " 
                "v1:" << (*ei).src.id << ", " 
                "v2:" << (*ei).dest.id << ", "  
                "e:" << g(*ei) << std::endl; 
        }
        std::cout << std::endl;
    }

    if (1) {
        auto visitor = [] (graph_t &graph, const vertex &v) -> bool {
            std::cout << 
                "vid:" << v.id << "," << 
                "v:" << graph(v) << std::endl; 
            //return graph(v) == 3; 
            return false;
        };

        std::cout << "dfs (recursive):" << std::endl;
        dfs<graph_t>(g, visitor, true);

        std::cout << "dfs:" << std::endl;
        dfs<graph_t>(g, visitor, false);

        std::cout << "bfs:" << std::endl;
        bfs<graph_t>(g, visitor);

        std::cout << std::endl;
    }
}

void Test::binary_search() {
    array<array<int>> arrays = {
        {0},
        {1,9},
        {1,1,3,6,20},
        {-15,0,3,155},
    };

    for (auto array : arrays) {
        for (auto value : array) {
            CPPUNIT_ASSERT_EQUAL(true, ::binary_search(array, value));
        }
    }

    array<int> array = {4, 8, 15, 18, 23, 42};
    for (auto value : array) {
        CPPUNIT_ASSERT_EQUAL(false, ::binary_search(array, value - 1));
        CPPUNIT_ASSERT_EQUAL(false, ::binary_search(array, value + 1));
    }
}

void Test::bigint() {
    for (int value = 0; value < 512; value++) {
        BigInt bi = value;
        CPPUNIT_ASSERT(bi == value);
    }

    for (int first = 0; first < 16; first++) {
        for (int second = 0; second < 16; second++) {
            int sum = first + second;
            BigInt bsum = BigInt(first) + BigInt(second);
            CPPUNIT_ASSERT(bsum == sum);

            int prod = first * second;
            BigInt bprod = BigInt(first) * BigInt(second);
            CPPUNIT_ASSERT(bprod == prod);
        }
    }
}
