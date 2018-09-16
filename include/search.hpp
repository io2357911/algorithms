#ifndef SEARCH_H
#define SEARCH_H

#include <functional>
#include "graph.hpp"

namespace io2357911 {

template <class G, class V, class T>
bool bfs_search(G *graph, V &visitor, const T &value) {
    auto vi = graph->vertex_iterator();
    while (vi.next()) {
        visitor.set_visited(graph, *vi, false);
    }

    vi = graph->vertex_iterator();
    while (vi.next()) {
        if (!visitor.is_visited(graph, *vi)) {
            visitor.set_visited(graph, *vi, true);
        }

        if (visitor.match(graph, *vi, value)) {
            return true;
        }
    }

    return false;
}

template <class G, class V>
class bfs_iterator {
public:
    bfs_iterator(G *graph, V visitor) :
        _graph(graph), _vi(graph->vertex_iterator())
    {} 

    bool next() {
        return _vi.next(); 
    }

    vertex operator*(){
        if (!_visitor.is_visited(_graph, *_vi)) {
            _visitor.set_visited(_graph, *_vi, true);
        }
        return *_vi;
    }

protected:
    G *_graph;
    typename G::vertex_iterator_t _vi;
    V _visitor;
};

} // namespace io2357911

#endif // SEARCH_H

