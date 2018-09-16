#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <exception>
#include "matrix.hpp"

#define NULL_ID -1
#define isInRange(value, array) (value > -1 && value < (int)array.size())

namespace io2357911 {


class invalid_vertex_exception : public std::exception {};
class invalid_edge_exception : public std::exception {};

using vertex_id = int;

struct vertex {
    vertex_id id = NULL_ID; 
};

using edge_id = int;

struct edge {
    edge_id id = NULL_ID;
    vertex src;
    vertex dest;
};


using matrix_adjacency = matrix<edge_id>;


struct edge_node {
    edge_id eid;
    vertex_id vid;
};
using edge_list = std::list<edge_node>;
using list_adjacency = std::map<vertex_id, edge_list>;


template <class V, class E, class A>
class base_graph {
public:
    vertex add_vertex(const V &vert) {
        _vertices.push_back(vert);

        vertex v;
        v.id = _vertices.size() - 1;
        return v;
    }

    edge add_edge(vertex v1, vertex v2, const E& ed) {
        _edges.push_back(ed);

        edge e;
        e.id = _edges.size() - 1;
        e.src = v1;
        e.dest = v2;
        return e;
    }

    V& operator()(const vertex &vertex) {
        if (!isInRange(vertex.id, _vertices)) { 
            throw invalid_vertex_exception();
        }
        return _vertices[vertex.id];
    }

    E& operator()(const edge &edge) {
        if (!isInRange(edge.id, _edges)) {
            throw invalid_edge_exception();
        }
        return _edges[edge.id];
    }

protected:
    std::vector<V> _vertices;
    std::vector<E> _edges;
    A _adjacency;
};

template <class V, class E, class A>
class graph : public base_graph<V, E, A> {
};

template <class V, class E>
class graph<V, E, list_adjacency> : public base_graph<V, E, list_adjacency> {
public: 
    using list_graph = graph<V, E, list_adjacency>; 

    edge add_edge(vertex first, vertex second, const E &ed) {
        edge e = base_graph<V,E,list_adjacency>::add_edge(first, second, ed); 

        edge_node en;
        en.eid = e.id;
        en.vid = e.dest.id;
        this->_adjacency[e.src.id].push_back(en); 

        return e;
    }
    
    class vertex_iterator_t {
    public:
       vertex_iterator_t(const list_graph &graph) :
           _graph(graph)
       {} 

       bool next() {
           _vid++; 
           return isInRange(_vid, _graph._vertices);
       }
       
       vertex operator*(){
           vertex v;
           v.id = _vid;
           return v;
       }

    private:
       const list_graph &_graph; 
       vertex_id _vid = NULL_ID;
    };
    friend class vertex_iterator_t;

    vertex_iterator_t vertex_iterator() const {
        vertex_iterator_t it(*this);
        return it;
    }
};


template <class V, class E>
class graph<V, E, matrix_adjacency> : public base_graph<V, E, matrix_adjacency> {
public: 
    //edge add_edge(vertex first, vertex second, const E &e) {
        //std::cout << "matrix add edge" << std::endl;
        //return edge();
    //}
};

//template <class id>
//void add_edge(Graph g, edge e);
//vertex nextVertex(Graph g); 
//edge next_edge(Graph g); 
//vertex nextVertex(Graph g, vertex v); 
//
//class Graph::EdgeIterator;
//class Edge::EdgeIterator;
//class Graph::VertexIterator;

} // namespace io2357911

#endif // GRAPH_H
