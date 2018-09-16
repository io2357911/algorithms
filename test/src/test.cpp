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

    graph<int, int, list_adjacency> g;
    v1 = g.add_vertex(1);
    v2 = g.add_vertex(2);
    e12 = g.add_edge(v1, v2, 42);
    e12 = g.add_edge(v1, v2, 43);
    g.add_edge(v2, v1, 1);
    g.add_edge(v2, v1, 2);
    g.add_edge(v2, v1, 3);

    std::cout << 
        "v1:" << g(v1) << ", " 
        "v2:" << g(v2) << ", " 
        "e12:" << g(e12) << std::endl;
    std::cout << std::endl;
    
    {
        auto vi = g.vertex_iterator();
        while (vi.next()) {
            std::cout << 
                "vid:" << (*vi).id << "," << 
                "v:" << g(*vi) << std::endl; 
        }
        std::cout << std::endl;
    }
    
    if (1) {
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

    {
        using graph_t = graph<int, int, list_adjacency>;

        struct visitor_t {
            bool is_visited(graph_t *graph, const vertex &vert) {
                return false;
            }
            void set_visited(graph_t *graph, const vertex &vert, bool visited) {
                (*graph)(vert) = visited;
            }
            bool match(graph_t *graph, const vertex &vert, const int &value) {
                return false;
            }
        } visitor;

        bool found = bfs_search<graph_t, visitor_t, int>(&g, visitor, 5);
        std::cout << "found:" << found << std::endl;
        std::cout << std::endl;

        using bfs_iterator_t = bfs_iterator<graph_t, visitor_t>;

        bfs_iterator_t vi(&g, visitor);
        while (vi.next()) {
            std::cout << 
                "vid:" << (*vi).id << "," << 
                "v:" << g(*vi) << std::endl; 
        }
        std::cout << std::endl;
    }
    //class mybfs : public bfs_iterator<>

    //graph<int, int, matrix_adjacency> mg;
    //v1 = mg.add_vertex(1);
    //v2 = mg.add_vertex(2);
    //mg.add_edge(v1, v2, 42);
}
