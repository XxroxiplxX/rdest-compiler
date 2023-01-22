#include "../include/DirectedGraph.h"
//#include "DirectedGraph.h"
void DirectedGraph::_asm_get(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("GET", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_halt(CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("HALT", instruction_pointer));
    instruction_pointer++;
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
void DirectedGraph::_asm_jump_i(std::string proc_id) {
    _asm_instructions.push_back(AsmInstruction("JUMPI", architecture.get_ret_reg(proc_id), instruction_pointer));
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
void DirectedGraph::translate_call(Instruction ins, CodeBlock* codeblock) {
    std::string proc_to_jump = ins.proc_id;
    log.log("wewnatrz procedury: " + codeblock->proc_id + " tlumacze calla do procedury: " + proc_to_jump);
    for (int i = 0; i < ins.args.size(); i++) {
        _asm_load(ins.args[i], codeblock);
        std::string id_want_to_store = architecture.procedures_memory[proc_to_jump].arg_ids[i];
        _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register(id_want_to_store, proc_to_jump), instruction_pointer));
        instruction_pointer++;
        log.log("zapakowalem argument: " + id_want_to_store);
    }
    _asm_instructions.push_back(AsmInstruction("SET", std::to_string(instruction_pointer + 2), instruction_pointer)); //lokalizacja powrotu
    log.log("ustawilem adres powrotu na: ", instruction_pointer + 2);
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_ret_reg(proc_to_jump), instruction_pointer));
    instruction_pointer++;
    
    int id_of_proc_head;
    for (auto proc_head : head_map) {
        if (proc_head.second == proc_to_jump) {
            id_of_proc_head = proc_head.first;
        }
    }
    log.log("skacze do procedury, ktorej glowa ma numer: ", id_of_proc_head);
    _asm_instructions.push_back(AsmInstruction("JUMP", get_vertexx(id_of_proc_head), instruction_pointer));
}
void DirectedGraph::translate_ins(Instruction ins, CodeBlock* codeblock) {
    log.log("tlumacze instrukcje w procedurze: " + codeblock->proc_id);
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
            translate_call(ins, codeblock);
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
    std::cout << "skonczylem transformacje\n";
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
    log.log("trans");
    if (codeblock->translated) {
        return;
    } else {
        //std::cout <<"adres"<< codeblock << std::endl;;
        codeblock->ip = instruction_pointer;    //stad bede wiedzial gdzie skakac
        for (auto instruction : codeblock->meat) {
            translate_ins(instruction, codeblock);
            log.log("tlumacze instrukcje w codeblocku: ", codeblock->id);
        }
        codeblock->translated = 1;
        log.log("before if");
        log.log("size ", codeblock->nbrs_ptrs.size());
        if (codeblock->nbrs_ptrs.size() == 0) {
            log.log("trafilem na koniec");
            if (codeblock->proc_id == "main") {
                _asm_halt(codeblock);
            } else {
                _asm_jump_i(codeblock->proc_id);
            }
            
        }
        log.log("after if");

        

        for (auto nbr : codeblock->nbrs_ptrs) {
            log.log("in loop");
            log.log("moi sasiedzi to: " , nbr.first);
            log.log(*codeblock);
            
            std::cout << nbr.second << std::endl;
            log.log("@@@@@@2");
            log.log(*nbr.second);
            translate_snippet(nbr.second);
            //log.log("wyjebalem sie");
        }
    }
}
void DirectedGraph::translate_main() {
    for (auto it : head_ids) {
        auto head = get_vertexx(it);
        log.log("tlumacze head z id: ", it);
        translate_snippet(head);
    }
    log.log("------teraz skoski-------");
    resolve_jumps();/*
    for (auto asmins : _asm_instructions) {
        if (asmins.jump_address == -1) {
            if (asmins._register != nullptr) {
                log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins._register->id));
            } else {
                log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " );
            }
        } else {
            log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins.jump_address));
        }
    }*/

}
void DirectedGraph:: resolve_jumps() {
    for (int i = 0; i < _asm_instructions.size(); i++) {
        if (_asm_instructions[i].codeblock != nullptr) {
            //
            _asm_instructions[i].jump_address = _asm_instructions[i].codeblock->ip;
        }
    }
    
}