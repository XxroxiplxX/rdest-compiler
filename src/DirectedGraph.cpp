#include "../include/DirectedGraph.h"
//#include "DirectedGraph.h"
void DirectedGraph::_asm_get(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("GET", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_halt() {
    _asm_instructions.push_back(AsmInstruction("HALT"));
}
void DirectedGraph::_asm_put(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("PUT", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_load(Value val, CodeBlock* codeblock) {
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("LOADI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("LOAD", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_store(Value val, CodeBlock* codeblock) {
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("STOREI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("STORE", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::translate_assign(Instruction ins, CodeBlock* codeblock) {
    translate_expression(ins.expr, codeblock);
    _asm_store(ins.left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->nbrs_ptrs[true], instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_expression(Expression expr, CodeBlock* codeblock) {
    _asm_load(expr.left, codeblock);
    switch(expr.type_of_operator) {
        case _ADD:
            //log.log("chce postawic add");
            _asm_add(expr.right, codeblock);
            break;
        case _SUB:
            _asm_sub(expr.right, codeblock);
            break;
    }
}
void DirectedGraph::_asm_add(Value val, CodeBlock* codeblock) {
    log.log("prosze o rejestr procedury: " + codeblock->proc_id + " dla zmiennej: " + val.load);
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("ADDI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("ADD", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("ADD", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_sub(Value val, CodeBlock* codeblock) {
    log.log("prosze o rejestr procedury: " + codeblock->proc_id + " dla zmiennej: " + val.load);
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("SUBI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("SUB", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("SUB", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_cmp_lower(Value left, Value right, CodeBlock* codeblock) {
    //load right sub left jpos true jump false
    _asm_load(right, codeblock);
    _asm_sub(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->nbrs_ptrs[true], instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->nbrs_ptrs[false], instruction_pointer));
    instruction_pointer++;

}
void DirectedGraph::_asm_cmp_eq(Value left, Value right, CodeBlock* codeblock) {
    //true jesli left - right = 0 i right i left = 0
    _asm_load(right, codeblock);
    _asm_sub(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->nbrs_ptrs[false], instruction_pointer));
    instruction_pointer++;
    _asm_load(left, codeblock);
    _asm_sub(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("JZERO", codeblock->nbrs_ptrs[true], instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->nbrs_ptrs[false], instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_cmp_leq(Value left, Value right, CodeBlock* codeblock) {
    //true jesli left <= right tzn left - right = 0
    _asm_load(left, codeblock);
    _asm_sub(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("JZERO", codeblock->nbrs_ptrs[true], instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->nbrs_ptrs[false], instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_condition(Instruction ins, CodeBlock* codeblock) {
    switch(ins.type_of_operator) {
        case _LLESS:
            _asm_cmp_lower(ins.left, ins.right, codeblock);
            break;
        case _LMORE:
            _asm_cmp_lower(ins.right, ins.left, codeblock);
            break;
        case _EQ:
            _asm_cmp_eq(ins.left, ins.right, codeblock);
            break;
        case _LLEQ:
            _asm_cmp_leq(ins.left, ins.right, codeblock);
            break;
        case _LHEQ:
            _asm_cmp_leq(ins.right, ins.left, codeblock);
            break;
    }
}
void DirectedGraph::translate_ins(Instruction ins, CodeBlock* codeblock) {
    switch (ins.type_of_instruction) {
        case _COND:
            translate_condition(ins, codeblock);
            break;
        case _READ:
            _asm_get(ins.right, codeblock);
            break;
        case _WRITE:
            _asm_put(ins.right, codeblock);
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
        get_vertexx(v_id)->neighbours[true] = u_id;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}
void DirectedGraph::add_edge(int v_id, int u_id, bool flag) {
    try {
        get_vertexx(v_id)->neighbours[flag] = u_id;
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
           log.log("linkuje vertex: ", nbr.second);
           auto tmp = get_vertexx(nbr.second);
           //tmp to sasiad, powinno byc tak ze kiedy sasiaf jest pusty to linkuje do sasiada sasiada
           /*if (tmp->meat.empty()) {
                //auto new_neig = get_vertexx(tmp->neighbours[true]);
                //codeblock->nbrs_ptrs[true] = get_vertexx(tmp->neighbours[true]);
                std::cout << "znalazlem pusty blok o id: " << tmp->id << std::endl;
                while (tmp->meat.empty()) {
                    tmp = get_vertexx(tmp->neighbours[true]);
                }
                codeblock->nbrs_ptrs[true] = tmp;
                std::cout << "linkuje " << codeblock->id << " z " << tmp->id << std::endl; 
                populate_neighbours(tmp, proc_id);
                
           } else {
                codeblock->nbrs_ptrs[nbr.first] = tmp;
                populate_neighbours(tmp, proc_id);
           }*/
            codeblock->nbrs_ptrs[nbr.first] = tmp;
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
    save_to_csv("/tmp/graphs");
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
            //for (int j = 0; j < vertices[i].neighbours.size(); j++) {
              //  outdata_e << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
                //std::cout << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
            //}
            for (auto node : vertices[i].nbrs_ptrs) {
                outdata_e << vertices[i].id << ";" << node.second->id << std::endl;
            }
        }
        outdata_e.close();
}
void DirectedGraph::translate_snippet(CodeBlock* codeblock) {
    if (codeblock->translated) {
        return;
    } else {
        codeblock->ip = instruction_pointer;    //stad bede wiedzial gdzie skakac
        for (auto instruction : codeblock->meat) {
            translate_ins(instruction, codeblock);
            log.log("tlumacze instrukcje w codeblocku: ", codeblock->id);
        }
        codeblock->translated = 1;
        for (auto nbr : codeblock->nbrs_ptrs) {
            translate_snippet(nbr.second);
        }
    }
}
void DirectedGraph::translate_main(int head_id) {
    auto head = get_vertexx(head_id);
    translate_snippet(head);
    resolve_jumps();
    for (auto asmins : _asm_instructions) {
        if (asmins.jump_address == -1) {
            log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins._register->id));
        } else {
            log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins.jump_address));
        }
    }

}
void DirectedGraph:: resolve_jumps() {
    for (int i = 0; i < _asm_instructions.size(); i++) {
        if (_asm_instructions[i].codeblock != nullptr) {
            //
            _asm_instructions[i].jump_address = _asm_instructions[i].codeblock->ip;
        }
    }
    
}