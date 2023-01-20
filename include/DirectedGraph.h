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
    void lock() {
        state = _LOCKED;
    }
    void unlock() {
        state = _UNLOCKED;
    }
    Register(int _id) : id(_id), state(_UNLOCKED) {}
};
struct Architecture {
    
    int var_p = 1;
    std::map<std::string, Register*> variables;
    std::map<std::string, Register*> constants;
    void assert_var(std::string id) {
        //variables.insert({id, Register(var_p)});
        variables[id] = new Register(var_p);
        var_p++;
    }
    int get_register_val_id(std::string iden) {
       
        if (variables[iden]->state == State::_UNLOCKED) {
            return variables[iden]->id;
        } else {
            return -1;
        }
    }
    Register* get_register(std::string iden) {
        if (variables[iden]->state == State::_UNLOCKED) {
            return variables[iden];
        } else {
            return nullptr;
        }
    }
};
struct AsmInstruction {
    std::string code;
    Register* _register;
    int constant;
    int ip;
    std::string label;
    AsmInstruction(std::string _code, Register* _r, int _ip) : code(_code), _register(_r), ip(_ip) {}
    AsmInstruction(std::string _code, Register* _r, int _ip, std::string _label) : code(_code), _register(_r), ip(_ip), label(_label) {}
    AsmInstruction(std::string _code, int _constant, int _ip) : code(_code), constant(_constant), ip(_ip) {}
    AsmInstruction(std::string _code, int _constant, int _ip, std::string _label) : code(_code), constant(_constant), ip(_ip), label(_label) {}
};
class DirectedGraph {
    public:
    Logging::Logger log = Logging::Logger("translation.log");
    Architecture architecture;


    std::vector<CodeBlock> vertices;

    std::vector<int> head_ids;

    std::vector<AsmInstruction> _asm_instructions;
    int instruction_pointer = 0;
    void add_vertexx(int v_id);
    void add_edge(int v_id, int u_id);
    void transform();
    void populate_neighbours(CodeBlock* codeblock);
    CodeBlock* get_vertexx(int v_id);
    void save_to_csv(std::string path);
    void translate_ins(Instruction ins);
    void translate_assign(Instruction ins);
    void translate_expression(Expression expr);
    void _asm_read(Value val);
    void _asm_write(Value val);
    void _asm_add(Value left, Value right);
};

#endif //COMPILER_DIRECTEDGRAPH_H