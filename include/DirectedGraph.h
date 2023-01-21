#ifndef COMPILER_DIRECTEDGRAPH_H
#define COMPILER_DIRECTEDGRAPH_H


#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "CodeBlock.h"
#include "Logger.h"
struct Vertexx {
    int id;
    std::vector<int> neighbours;
    CodeBlock codeblock;
    Vertexx(int _id) :id(_id) {}
};
enum State {
    _LOCKED = 0,
    _UNLOCKED = 1
};
struct Register {
    int id;
    State state;
    std::string range;
    bool holds_argument = 0;;
    void lock() {
        state = _LOCKED;
    }
    void unlock() {
        state = _UNLOCKED;
    }
    Register(int _id) : id(_id), state(_UNLOCKED) {}
    Register(int _id, std::string arg) : id(_id), holds_argument(1), state(_UNLOCKED) {}
};
struct Memory {
    std::map<std::string, Register*> variables;
};
struct Architecture {
    Logging::Logger log = Logging::Logger("memory.log");
    int var_p = 1;
    //std::map<std::string, Register*> variables;
    std::map<std::string, Memory> procedures_memory;
    std::map<std::string, Register*> constants;
    void assert_var(std::string id, std::string proc_id) {
        //variables.insert({id, Register(var_p)});
        procedures_memory[proc_id].variables[id] = new Register(var_p);
        log.log("do pamieci dodano rejestr: @" + std::to_string(var_p) + " dla procedury : @" + proc_id + " i zmiennej: @" + id);
        var_p++;
    }
    void assert_arg(std::string id, std::string proc_id) {
        procedures_memory[proc_id].variables[id] = new Register(var_p, "arg");
        var_p++;
    }
    int get_register_val_id(std::string iden) {
       
        //if (variables[iden]->state == State::_UNLOCKED) {
           // return variables[iden]->id;
        //} else {
            return -1;
        //}
    }
    Register* get_register(std::string iden, std::string proc_id) {
       // if (variables[iden]->state == State::_UNLOCKED) {
          //  return variables[iden];
       // } else {
            //return nullptr;
       // }
        auto tmp_ptr = procedures_memory[proc_id].variables[iden];
        log.log("pamiec przekazala rejestr: @" + std::to_string(tmp_ptr->id) + " dla procedury : @" + proc_id + " i zmiennej: @" + iden);
        return tmp_ptr;
    }
};
struct AsmInstruction {
    std::string code;
    Register* _register;
    std::string constant;
    int ip;
    std::string label;
    std::string asm_to_string() {
        
    }
    AsmInstruction(std::string _code) : code(_code), _register(nullptr), ip(-1) {}
    AsmInstruction(std::string _code, Register* _r, int _ip) : code(_code), _register(_r), ip(_ip) {}
    AsmInstruction(std::string _code, Register* _r, int _ip, std::string _label) : code(_code), _register(_r), ip(_ip), label(_label) {}
    AsmInstruction(std::string _code, std::string _constant, int _ip) : code(_code), _register(nullptr), constant(_constant), ip(_ip) {}
    AsmInstruction(std::string _code, std::string _constant, int _ip, std::string _label) : code(_code), _register(nullptr), constant(_constant), ip(_ip), label(_label) {}
};
class DirectedGraph {
    public:
    Logging::Logger log = Logging::Logger("translation.log");
    Architecture architecture;


    std::vector<CodeBlock> vertices;

    std::vector<int> head_ids;
    std::map<int, std::string> head_map;
    std::vector<AsmInstruction> _asm_instructions;
    int instruction_pointer = 0;
    void add_vertexx(int v_id);
    void add_edge(int v_id, int u_id);
    void transform();
    void populate_neighbours(CodeBlock* codeblock, std::string proc_id);
    void translate_snippet(CodeBlock* codeblock);
    CodeBlock* get_vertexx(int v_id);
    void save_to_csv(std::string path);
    void translate_main(int head_id);
    void translate_ins(Instruction ins, CodeBlock* codeblock);
    void translate_assign(Instruction ins, CodeBlock* codeblock);
    void translate_expression(Expression expr, CodeBlock* codeblock);
    void _asm_get(Value val, CodeBlock* codeblock);
    void _asm_put(Value val, CodeBlock* codeblock);
    void _asm_add(Value val, CodeBlock* CodeBlock);
    void _asm_sub(Value val, CodeBlock* codeblock);
    void _asm_mul(Value left, Value right);
    void _asm_div(Value left, Value right);
    void _asm_mod(Value left, Value right);
    void _asm_halt();
};

#endif //COMPILER_DIRECTEDGRAPH_H