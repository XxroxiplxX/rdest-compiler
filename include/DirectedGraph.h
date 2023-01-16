#ifndef COMPILER_DIRECTEDGRAPH_H
#define COMPILER_DIRECTEDGRAPH_H


#include <vector>
#include <iostream>
#include <fstream>
#include "CodeBlock.h"
struct Vertexx {
    int id;
    std::vector<int> neighbours;
    CodeBlock codeblock;
    Vertexx(int _id) :id(_id) {}
};

class DirectedGraph {
    public:
    
    std::vector<CodeBlock> vertices;
    void add_vertexx(int v_id);
    void add_edge(int v_id, int u_id);
    CodeBlock* get_vertexx(int v_id);
    void save_to_csv(std::string path);
};

#endif //COMPILER_DIRECTEDGRAPH_H