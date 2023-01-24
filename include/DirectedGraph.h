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
    bool holds_argument = 0;
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
    std::vector<std::string> arg_ids;
    Register* ret_reg = nullptr;
};
struct Architecture {
    Logging::Logger log = Logging::Logger("memory.log");
    int var_p = 1;
    //std::map<std::string, Register*> variables;
    std::map<std::string, Memory> procedures_memory;
    std::map<std::string, Register*> constants;
    Register* op_1;
    Register* op_2;
    Register* mul_trash;
    Register* mul_prod;
    void assert_ops() {
        op_1 = new Register(var_p);
        var_p++;
        op_2 = new Register(var_p);
        var_p++;
        mul_trash = new Register(var_p);
        var_p++;
        mul_prod = new Register(var_p);
        var_p++;
        log.log("do pamieci dodano rejestry operacji");
    }
    Register* get_mul_prod() {
        return mul_prod;
    }
    Register* get_mul_trash() {
        return mul_trash;
    }
    Register* get_op_1() {
        return op_1;
    }
    Register* get_op_2() {
        return op_2;
    }
    void assert_var(std::string id, std::string proc_id) {
        //variables.insert({id, Register(var_p)});
        procedures_memory[proc_id].variables[id] = new Register(var_p);
        log.log("do pamieci dodano rejestr: @" + std::to_string(var_p) + " dla procedury : @" + proc_id + " i zmiennej: @" + id);
        var_p++;
    }
    void assert_ret_reg(std::string proc_id) {
        log.log("do pamieci dodano rejestr powrotu dla procedury: " + proc_id);
        procedures_memory[proc_id].ret_reg = new Register(var_p);
    }
    Register* get_ret_reg(std::string proc_id) {
        return procedures_memory[proc_id].ret_reg;
    }
    void assert_const(std::string NUM) {
        constants[NUM] = new Register(var_p);
        
        log.log("do pamieci dodano stala: " + NUM + " na pozycji: " + std::to_string(var_p));
        var_p++;
    }
    void assert_arg(std::string id, std::string proc_id) {
        log.log("do pamieci dodano argument procedury: " + proc_id + " o sygnaturze: " + id);
        procedures_memory[proc_id].variables[id] = new Register(var_p, "arg");
        procedures_memory[proc_id].arg_ids.push_back(id);
        var_p++;
    }
    int get_register_val_id(std::string iden) {
       
        //if (variables[iden]->state == State::_UNLOCKED) {
           // return variables[iden]->id;
        //} else {
            return -1;
        //}
    }
    Register* get_constant(std::string NUM) {
        auto tmp_ptr = constants[NUM];
        log.log("pamiec przekazala rejestr: @" + std::to_string(tmp_ptr->id) + " dla stalej: @" + NUM);
        return tmp_ptr;
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
    std::string constant = "";
    int ip;
    int jump_address = -1;
    std::string label;
    CodeBlock* codeblock;
    AsmInstruction(std::string _code, CodeBlock* _to_jump, int _ip) : code(_code), _register(nullptr), ip(_ip), codeblock(_to_jump) {}

    AsmInstruction(std::string _code, int _ip) : code(_code), _register(nullptr), ip(_ip), codeblock(nullptr) {}

    AsmInstruction(std::string _code, Register* _r, int _ip) : code(_code), _register(_r), ip(_ip), codeblock(nullptr) {}

    AsmInstruction(std::string _code, Register* _r, int _ip, std::string _label) : code(_code), _register(_r), ip(_ip), label(_label), codeblock(nullptr) {}

    AsmInstruction(std::string _code, std::string _constant, int _ip) : code(_code), _register(nullptr), constant(_constant), ip(_ip), codeblock(nullptr) {}

    AsmInstruction(std::string _code, std::string _constant, int _ip, std::string _label) : code(_code), _register(nullptr), constant(_constant), ip(_ip), label(_label), codeblock(nullptr) {}
};
class DirectedGraph {
    public:
    Logging::Logger log = Logging::Logger("translation.log");
    Architecture architecture;

    int end_blocks = 1000;
    std::vector<CodeBlock> vertices;

    std::vector<int> head_ids;
    std::map<int, std::string> head_map;
    std::vector<AsmInstruction> _asm_instructions;
    int instruction_pointer = 0;
    void _asm_push_base(std::string signature, Register* address) {
        _asm_instructions.push_back(AsmInstruction(signature, address, instruction_pointer));
        instruction_pointer++;
    }
    void _asm_push_base(std::string signature, Register* address, std::string _label) {
        _asm_instructions.push_back(AsmInstruction(signature, address, instruction_pointer, _label + std::to_string(instruction_pointer) + "]"));
        instruction_pointer++;
    }
    void _asm_push_base(std::string signature, std::string var_name, std::string proc_id) {
        _asm_instructions.push_back(AsmInstruction(signature, architecture.get_register(var_name, proc_id), instruction_pointer));
        instruction_pointer++;
    }
    void add_vertexx(int v_id);
    void add_edge(int v_id, int u_id);
    void add_edge(int v_id, int u_id, bool flag);
    void transform();
    void resolve_jumps();
    void populate_neighbours(CodeBlock* codeblock, std::string proc_id);
    void translate_snippet(CodeBlock* codeblock);
    CodeBlock* get_vertexx(int v_id);
    void save_to_csv(std::string path);
    void translate_main();
    void resolve_consts();
    void _asm_set_constants();
    void translate_ins(Instruction ins, CodeBlock* codeblock);
    void translate_assign(Instruction ins, CodeBlock* codeblock);
    void translate_expression(Expression expr, CodeBlock* codeblock);
    void translate_condition(Instruction ins, CodeBlock* codeblock);
    void translate_call(Instruction ins, CodeBlock* codeblock);
    void _asm_cmp_lower(Value left, Value right, CodeBlock* codeblock);
    void _asm_cmp_eq(Value left, Value right, CodeBlock* codeblock);
    void _asm_cmp_leq(Value left, Value right, CodeBlock* codeblock);
    void _asm_load(Value val, CodeBlock* codeblock);
    void _asm_store(Value val, CodeBlock* codeblock);
    void _asm_get(Value val, CodeBlock* codeblock);
    void _asm_put(Value val, CodeBlock* codeblock);
    void _asm_add(Value val, CodeBlock* CodeBlock);
    void _asm_sub(Value val, CodeBlock* codeblock);
    void _asm_mul(Value left, Value right, CodeBlock* codeblock);
    void _asm_div(Value left, Value right);
    void _asm_mod(Value left, Value right);
    void _asm_halt(CodeBlock* codeblock);
    void _asm_jump_i(std::string proc_id);
    void _return();
};

#endif //COMPILER_DIRECTEDGRAPH_H