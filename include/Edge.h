#ifndef CGRAPH_EDGE_H
#define CGRAPH_EDGE_H


#include "Vertex.h"

namespace GraphLib {
    template <class T>
    class Vertex;


    template <class T, class L>
    class Edge {
    public:
        Edge(){}
        Edge(Vertex<T>* u, Vertex<T>* v);
        Edge(Vertex<T>* u, Vertex<T>* v, L label);
        bool operator<(const Edge<T,L>& edge);
        bool operator>(const Edge<T,L>& edge);
        Vertex<T>* u;
        Vertex<T>* v;
        L label;
    };

    template<class T, class L>
    Edge<T,L>::Edge(Vertex<T> *u, Vertex<T> *v, L label) : u(u), v(v), label(label){

    }

    template<class T, class L>
    bool Edge<T,L>::operator<(const Edge<T,L> &edge) {
        return this->label < edge.label;
    }

    template<class T, class L>
    bool Edge<T, L>::operator>(const Edge<T, L> &edge) {
        return this->label > edge.label;
    }

    template<class T, class L>
    Edge<T, L>::Edge(Vertex<T> *u, Vertex<T> *v) : u(u), v(v){

    }
}

#endif //CGRAPH_EDGE_H