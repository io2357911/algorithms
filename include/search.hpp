#ifndef SEARCH_H
#define SEARCH_H

#include <map>
#include <queue>
#include <stack>
#include "graph.hpp"

namespace io2357911 {

using visit_map = std::map<vertex, bool>;

/**
 * @brief dfs deep first graph search
 * @param graph to search in
 * @param visitor is a function to call on visited vertex (return true to stop search)
 * @return true - if visitor returned true
 */
template <class G, class V>
bool dfs(G &graph, V visitor, bool recursive = false) {

    // mark all vertices as not visited

    visit_map visited;
    auto vi = graph.vertex_iterator();
    while (vi.next()) {
        visited[*vi] = false;
    }
    
    // search across all vertices if graph is not coupled

    vi = graph.vertex_iterator();
    while (vi.next()) {
        if (recursive) {
            if (dfs(graph, visitor, *vi, visited)) {
                return true;
            } 
        } else {
            if (dfs_not_recursive(graph, visitor, *vi, visited)) {
                return true;
            } 
        }
    }
    return false;
}

template <class G, class V>
bool dfs(G &graph, V visitor, const vertex &v, visit_map &visited) {
    if (!visited[v]) {

        // visit vertex

        visited[v] = true;
        if (visitor(graph, v)) {
            return true;
        }

        // continue with neighbours

        auto ei = graph.edge_iterator(v);
        while (ei.next()) {
            if (dfs(graph, visitor, (*ei).dest, visited)) {
                return true;
            } 
        }
    }
    return false;
}

template <class G, class V>
bool dfs_not_recursive(G &graph, V visitor, const vertex &v, visit_map &visited) {
    if (visited[v]) return false;

    std::stack<typename G::vertex_edge_iterator_t> stack;

    auto visit = [&] (const vertex& v) -> bool {
        visited[v] = true;
        stack.push(graph.edge_iterator(v));
        return visitor(graph, v);
    };
    
    if (visit(v)) return true;

    while (stack.size()) {

        // find first not visited neighbour

        auto &ei = stack.top();
        while (ei.next() && visited[(*ei).dest]) {}

        if (ei) {
            // going deeper
            if (visit((*ei).dest)) return true;
        
        } else {
            // return back
            stack.pop();
        }
    }
    return false;
}
/**
 * @brief bfs breadth first graph search
 * @param graph to search in
 * @param visitor is a function to call on visited vertex (return true to stop search)
 * @return true - if visitor returned true
 */
template <class G, class V>
bool bfs(G &graph, V visitor) {

    // mark all vertices as not visited

    visit_map visited;
    auto vi = graph.vertex_iterator();
    while (vi.next()) {
        visited[*vi] = false;
    }
    
    // search across all vertices if graph is not coupled

    vi = graph.vertex_iterator();
    while (vi.next()) {
       if (bfs(graph, visitor, *vi, visited)) {
           return true;
       } 
    }
    return false;
}

template <class G, class V>
bool bfs(G &graph, V visitor, const vertex &v, visit_map &visited) {

    // push vertex to queue

    std::queue<vertex> vertices;
    vertices.push(v); 

    while (vertices.size()) {
        auto v = vertices.front();
        vertices.pop();
        if (visited[v]) continue;

        // visit vertex

        visited[v] = true;
        if (visitor(graph, v)) {
            return true;
        }

        // push neighbours to queue

        auto ei = graph.edge_iterator(v);
        while (ei.next()) {
            vertices.push((*ei).dest);
        }
    }
    return false;
}    

/**
 * @brief binary_search searches value in sorted array
 * @param array to search in
 * @param value to search
 * @return true - if array contains value, else - otherwise
 */
template <typename T>
bool binary_search(const array<T> &array, const T &value) {
    size_t l = 0;
    size_t h = array.size();

    while (h - l > 0) {
        size_t m = (h + l) / 2;

        if (value == array[m]) {
            return true;

        } else if (value > array[m]) {
            l = m + 1;
        
        } else {
            h = m;
        }
    }
    return false;
}

} // namespace io2357911

#endif // SEARCH_H
