#include "../include/DirectedGraph.h"
void DirectedGraph::_asm_read(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("GET", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_halt() {
    _asm_instructions.push_back(AsmInstruction("HALT"));
}
void DirectedGraph::_asm_write(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("PUT", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_assign(Instruction ins, CodeBlock* codeblock) {
    translate_expression(ins.expr, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register(ins.left.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_expression(Expression expr, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_register(expr.left.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
    switch(expr.type_of_operator) {
        case _ADD:
            //log.log("chce postawic add");
            _asm_add(expr.left, expr.right, codeblock);
            break;
    }
}
void DirectedGraph::_asm_add(Value left, Value right, CodeBlock* codeblock) {
    log.log("prosze o rejestr procedury: " + codeblock->proc_id + " dla zmiennej: " + right.load);
    _asm_instructions.push_back(AsmInstruction("ADD", architecture.get_register(right.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_ins(Instruction ins, CodeBlock* codeblock) {
    switch (ins.type_of_instruction) {
        case _COND:
            break;
        case _READ:
            _asm_read(ins.right, codeblock);
            break;
        case _WRITE:
            _asm_write(ins.right, codeblock);
            break;
        case _ASS:
            translate_assign(ins, codeblock);
            break;
        case _CALL:
            break;
        case _EMPTY:
            break;
    }
    //translacja ID := ID + ID;
    //architecture.assert_var("a");
    //architecture.assert_var("b");
    //architecture.assert_var("c");
    //log.log("utoworzono rejestry zmiennych a b c");
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
void DirectedGraph::populate_neighbours(CodeBlock* codeblock, std::string proc_id) {
   if (codeblock->visited) {
       return;
   } else {
       codeblock->visited = 1;
       codeblock->proc_id = proc_id;
       for (auto nbr: codeblock->neighbours) {
           log.log("linkuje vertex: ", nbr);
           auto tmp = get_vertexx(nbr);
           codeblock->nbrs_ptrs.push_back(tmp);
           populate_neighbours(tmp, proc_id);

       }
   }
}
void DirectedGraph::transform() {
    CodeBlock* tmp;
    for (auto head : head_map) {
        tmp = get_vertexx(head.first);
        std::cout << "glowa no        " << head.first << "id: " << head.second << std::endl;
        populate_neighbours(tmp, head.second);
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
            for (int j = 0; j < vertices[i].neighbours.size(); j++) {
                outdata_e << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
                //std::cout << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
            }
            
        }
        outdata_e.close();
}
void DirectedGraph::translate_snippet(CodeBlock* codeblock) {
    if (codeblock->translated) {
        return;
    } else {
        codeblock->ip = instruction_pointer + 1;    //stad bede wiedzial gdzie skakac
        for (auto instruction : codeblock->meat) {
            translate_ins(instruction, codeblock);
        }
        codeblock->translated = 1;
        for (auto nbr : codeblock->nbrs_ptrs) {
            translate_snippet(nbr);
        }
    }
}
void DirectedGraph::translate_main(int head_id) {
    auto head = get_vertexx(head_id);
    translate_snippet(head);
    for (auto asmins : _asm_instructions) {
        log.log(asmins.code + "        " + std::to_string(asmins._register->id));
    }

}