#include "../include/DirectedGraph.h"
void DirectedGraph::_asm_read(Value val) {
    _asm_instructions.push_back(AsmInstruction("READ", architecture.get_register(val.load), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_write(Value val) {
    _asm_instructions.push_back(AsmInstruction("WRITE", architecture.get_register(val.load), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_assign(Instruction ins) {
    translate_expression(ins.expr);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register(ins.left.load), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_expression(Expression expr) {
    _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_register(expr.left.load), instruction_pointer));
    instruction_pointer++;
    switch(expr.type_of_operator) {
        case _ADD:
            _asm_add(expr.left, expr.right);
            break;
    }
}
void DirectedGraph::_asm_add(Value left, Value right) {
    _asm_instructions.push_back(AsmInstruction("ADD", architecture.get_register(right.load), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_ins(Instruction ins) {
    switch (ins.type_of_instruction) {
        case _COND:
            break;
        case _READ:
            _asm_read(ins.right);
            break;
        case _WRITE:
            _asm_write(ins.right);
            break;
        case _ASS:
            translate_assign(ins);
            break;
        case _CALL:
            break;
        case _EMPTY:
            break;
    }
    //translacja ID := ID + ID;
    architecture.assert_var("a");
    architecture.assert_var("b");
    architecture.assert_var("c");
    log.log("utoworzono rejestry zmiennych a b c");
    //_asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_register("b")));
    //_asm_instructions.push_back(AsmInstruction("ADD", architecture.get_register("c")));
    //_asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register("a")));
}

void DirectedGraph::add_vertexx(int v_id) {
    vertices.push_back(CodeBlock(v_id));
}

CodeBlock* DirectedGraph::get_vertexx(int v_id) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].id == v_id) {
            return &vertices[i];
        }
    }
    throw "no bitches :((";
}

void DirectedGraph::add_edge(int v_id, int u_id) {
    try {
        get_vertexx(v_id)->neighbours.push_back(u_id);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}
void DirectedGraph::populate_neighbours(CodeBlock* codeblock) {
   
        for (auto nbr : codeblock->neighbours) {
            auto tmp = get_vertexx(nbr);
            codeblock->nbrs_ptrs.push_back(tmp);
            populate_neighbours(tmp);
        
    }
}
void DirectedGraph::transform() {
    CodeBlock* tmp;
    for (auto head : head_ids) {
        tmp = get_vertexx(head);
        std::cout << "glowa         " << head << std::endl;
        populate_neighbours(tmp);
    }
}

void DirectedGraph::save_to_csv(std::string path) {
        std::ofstream outdata_v;
        std::ofstream outdata_e;
        outdata_v.open(path + "/graph_v.csv");
        outdata_e.open(path + "/graph_e.csv");
        outdata_v << "v" << ";" << std::endl;
        outdata_e << "e1" << ";" << "e2" << std::endl;
        for (auto vertex : vertices) {
            outdata_v << vertex.id << ";" << std::endl;
        }
        outdata_v.close();
        /*for (auto edge : edges) {
            outdata_e << edge.u->label << ";" << edge.v->label << std::endl;
            
        }*/
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices[i].nbrs_ptrs.size(); j++) {
                outdata_e << vertices[i].id << ";" << vertices[i].nbrs_ptrs[j]->id << std::endl;
                //std::cout << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
            }
            
        }
        outdata_e.close();
    }