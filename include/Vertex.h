#ifndef CGRAPH_VERTEX_H
#define CGRAPH_VERTEX_H

#include "vector"

#include "map"
#include "algorithm"
#include "CodeBlock.h"
namespace GraphLib {

    template <class T>
    class Vertex {

    public:
        std::vector<Vertex<T>*> neighbours;
        Vertex(){}
        Vertex(T l);
        //CodeBlock codeblock;
        T label;
        std::vector<Vertex<T>*>* get_neighbours();
        bool operator<(const Vertex<T>& vertex);
        bool operator>(const Vertex<T>& vertex);
        int eccentricity();
        bool isIncidental(Vertex<T>* v);
        int dist(Vertex<T> v, int acc);
        int degree();
};

    template<class T>
    bool Vertex<T>::isIncidental(Vertex<T>* v) {
        if (std::find(neighbours.begin(), &neighbours.end(), v)) {
            return true;
        }
        return false;
    }

    template<class T>
    int Vertex<T>::degree() {
        return neighbours.size();
    }

    template<class T>
    Vertex<T>::Vertex(T l) : label(l) {

    }

    template<class T>
    std::vector<Vertex<T> *>* Vertex<T>::get_neighbours() {
        return &neighbours;
    }

    template<class T>
    int Vertex<T>::eccentricity() {
        return 0;
    }

    template<class T>
    int Vertex<T>::dist(Vertex<T>v, int acc) {
        for (auto neighbour : neighbours) {
            if (v.isIncidental(*neighbour)) {
                return 1;
            } else {
                return dist(neighbour, acc+1);
            }
        }
    }

    template<class T>
    bool Vertex<T>::operator<(const Vertex<T> &vertex) {
        return this->label < vertex.label;
    }

    template<class T>
    bool Vertex<T>::operator>(const Vertex<T> &vertex) {
        return this->label < vertex.label;
    }


}

#endif //CGRAPH_VERTEX_H
