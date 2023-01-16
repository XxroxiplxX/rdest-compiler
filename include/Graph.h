//
// Created by piotrkali on 11/26/22.
//
#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

#include "set"
#include "iostream"
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "fstream"

namespace GraphLib {
    /*
     * ******************************************
     * *       Vertices labels are unique       *
     * *   all labels have overloaded order     *
     * *             operators                  *
     * *                                        *
     * ******************************************
     */

    template <class T, class L>
    class Graph {


    public:
        std::vector<Vertex<T>> vertices;
        std::vector<Edge<T,L>> edges;
        Vertex<T>* get_vertex(T label);
        Edge<T,L>* get_edge(T u_label, T v_label);
        Graph() {}
        Graph(const Graph<T,L>& graph);
        Graph(const std::vector<Vertex<T>> vertices);
        ~Graph(){};
        int distance(Vertex<T> u, Vertex<T> v);
        void add_vertex(Vertex<T> v);
        void add_vertex(T t);
        void add_edge(Vertex<T>* u, Vertex<T>* v, L label);
        void add_edge(Vertex<T>* u, Vertex<T>* v);
        void add_edge(T ut, T vt, L label);
        std::vector<Vertex<T>*>* get_neighbours(Vertex<T> u);
        int min_degree();
        int max_degree();
        std::vector<Vertex<T>>get_vertices();
        std::vector<Edge<T,L>>get_edges();
        int eccentricity(Vertex<T>* u);
        int diameter();
        int radius();
        void save_to_csv(std::string path);
        void print_e() {
            for (auto it : edges) {
                std::cout << it.u->label << " -> " << it.v->label << "    ";
            }
            std::cout << std::endl;
        }
    };

    template<class T, class L>
    int Graph<T,L>::min_degree() {
        int min = vertices[0].degree();
        for (auto it : vertices) {
            if (it.degree() < min) {
                min = it.degree();
            }
        }
        return min;
    }

    template<class T, class L>
    std::vector<Vertex<T>> Graph<T,L>::get_vertices() {
        return vertices;
    }

    template<class T, class L>
    void Graph<T,L>::add_vertex(Vertex<T> v) {
        vertices.push_back(v);
    }

    template<class T, class L>
    void Graph<T,L>::add_edge(Vertex<T>* u, Vertex<T>* v, L label) {
        edges.push_back(Edge<T,L>(u,v,label));
        u->get_neighbours()->push_back(v);
        v->get_neighbours()->push_back(u);
    }

    template<class T, class L>
    std::vector<Edge<T,L>> Graph<T,L>::get_edges() {
        return edges;
    }

    template<class T, class L>
    void Graph<T,L>::add_vertex(T t) {
        vertices.push_back(Vertex<T>(t));
    }

    template<class T, class L>
    std::vector<Vertex<T> *>* Graph<T,L>::get_neighbours(Vertex<T> u) {
        return u.get_neighbours();
    }

    template<class T, class L>
    int Graph<T,L>::max_degree() {
        int max = vertices[0].degree();
        for (auto it : vertices) {
            if (it.degree() > max) {
                max = it.degree();
            }
        }
        return max;
    }

    template<class T, class L>int Graph<T,L>::distance(Vertex<T> u, Vertex<T> v) {
        return u.dist(v, 0);
    }

    template<class T, class L>
    int Graph<T,L>::eccentricity(Vertex<T> *u) {
        int max_dist = 0;
        int tmp;
        for (auto v : vertices) {
            tmp = u->dist(v, 0);
            if (tmp > max_dist) {
                max_dist = tmp;
            }
        }
        return max_dist;
    }

    template<class T, class L>
    int Graph<T,L>::diameter() {
        int max = 0;
        int tmp;
        for (auto vertex : vertices) {
            tmp = eccentricity(vertex);
            if (tmp > max) {
                max = tmp;
            }
        }
        return max;
    }

    template<class T, class L>
    int Graph<T,L>::radius() {
        int min = vertices[0];
        int tmp;
        for (auto vertex : vertices) {
            tmp = eccentricity(vertex);
            if (tmp < min) {
                min = tmp;
            }
        }
        return min;
    }

    template<class T, class L>
    void Graph<T,L>::add_edge(T ut, T vt, L label) {
        auto u = get_vertex(ut);
        auto v = get_vertex(vt);
        if (!(u and v)) {
            std::cout << "problem" << std::endl;
            return;
        }
        edges.push_back(Edge<T,L>(u,v, label));
        u->get_neighbours()->push_back(v);
        v->get_neighbours()->push_back(u);
    }

    template<class T, class L>
    void Graph<T,L>::save_to_csv(std::string path) {
        std::ofstream outdata_v;
        std::ofstream outdata_e;
        outdata_v.open(path + "/graph_v.csv");
        outdata_e.open(path + "/graph_e.csv");
        outdata_v << "v" << ";" << std::endl;
        outdata_e << "e1" << ";" << "e2" << std::endl;
        for (auto vertex : vertices) {
            outdata_v << vertex.label << ";" << std::endl;
            std::cout << vertex.label << ";" << std::endl;
        }
        outdata_v.close();
        /*for (auto edge : edges) {
            outdata_e << edge.u->label << ";" << edge.v->label << std::endl;
            
        }*/
        for (int i = 0; i < edges.size(); i++) {
            outdata_e << edges[i].u->label << ";" << edges[i].v->label << std::endl;
        }
        outdata_e.close();
    }

    template<class T, class L>
    Vertex<T>* Graph<T,L>::get_vertex(T l) {
        Vertex<T>* ptr = nullptr;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].label == l) {
                ptr = &vertices[i];
                return ptr;
            }
        }
        return nullptr;
    }

    template<class T, class L>
    Graph<T,L>::Graph(const Graph<T,L>& graph) {
        for (auto it : graph.vertices) {
            vertices.push_back(it);
        }
        for (auto it : graph.edges) {
            edges.push_back(it);
        }
    }

/*
 * **************************************************
 * *                w : E -> N                      *
 * *                x : V -> N                      *
 * **************************************************
 */
    

    template<class T, class L>
    Graph<T,L>::Graph(const std::vector<Vertex<T>> vertices) {
        for (auto vert : vertices) {
            this->vertices.push_back(vert);
        }
    }

    template<class T, class L>
    Edge<T,L> *Graph<T,L>::get_edge(T u_label, T v_label) {
        for (int i = 0; i < edges.size(); i++) {
            if ((edges[i].v->label == v_label and edges[i].u->label == u_label) or (edges[i].v->label == u_label and edges[i].u->label == v_label)) {
                return &edges[i];
            }
        }
        return nullptr;
    }

    template<class T, class L>
    void Graph<T, L>::add_edge(Vertex<T> *u, Vertex<T> *v) {
        edges.push_back(Edge<T,L>(u,v));
        u->get_neighbours()->push_back(v);
        v->get_neighbours()->push_back(u);
        //std::cout << "[]added edge between " << v->label << " and " << u->label << std::endl;
    }

}



#endif //CGRAPH_GRAPH_H
