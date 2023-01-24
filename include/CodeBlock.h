#ifndef COMPILER_CODDEBLOCK_H
#define COMPILER_CODDEBLOCK_H


#include <vector>
#include<string>
#include <map>
enum type_of_value {
    _NUM = 1,
    _ID = 2
};
struct Value {
    type_of_value type;
    std::string load="";
    bool is_arg = 0;
    Value() {
        type = type_of_value::_ID;
    }
    std::string val_to_string() {
        return "%val% = %type:" + std::to_string(type) + "%load:" + load;
    }
    Value(std::string _load) {
        if (_load[0] == 'I') {
            type = type_of_value::_ID;
            for (int i = 3; i < _load.length(); i++) {
                load += _load[i];
            }
        } else if (_load[0] == 'N') {
            type = type_of_value::_NUM;
            for (int i = 4; i < _load.length(); i++) {
                load += _load[i];
            }
        } else {
            type = type_of_value::_ID;
            for (int i = 3; i < _load.length(); i++) {
                load += _load[i];
            }
        }
    }
};
enum _type_of_meat {
    _COND = 1,
    _READ = 2,
    _WRITE = 3,
    _ASS = 4,
    _CALL = 16,
    _EMPTY = 0
} ;

enum _type_of_operator {
    _MUL = 5,
    _DIV = 6,
    _SUB = 7,
    _ADD = 8,
    _MOD = 9,
    _EQ = 10,
    _NEQ = 11,
    _LLEQ = 12,
    _LHEQ = 13,
    _LLESS = 14,
    _LMORE = 15,
    _NONE = 0
} ;
struct Expression {
    _type_of_operator type_of_operator;
    Value left;
    Value right;
    std::string exp_to_string() {
        return "%%%exp---->" + left.val_to_string() + "____" + std::to_string(type_of_operator) + "____" + right.val_to_string();
    }
};
struct Instruction {
    _type_of_meat type_of_instruction;
    int type_of_operator;
    Value left;
    Value right;
    Expression expr;
    std::vector<Value> args;
    std::string proc_id;
    std::string to_asm() {
        //switch (type_of_instruction) {
          //  case _type_of_meat::_ASS:
                //aaaa
            return "";
        //}
    }
};

class CodeBlock {
    public:
        std::vector<Instruction> meat;
        
        //std::vector<CodeBlock*> nbrs_ptrs;
        //std::map<bool, CodeBlock*> nbrs_ptrs;
        CodeBlock* next_true; //= nullptr;
        CodeBlock* next_false; //= nullptr;
        CodeBlock(){
            //next_false = nullptr;
            //next_true = nullptr;
            //next_false_id = -1;
            //next_true_id = -1;
        }
        bool empty = 0;
        bool last = 0;
        int ip;
        int id;
        bool visited = false;
        bool translated = false;
        int next_true_id; // = -1;
        int next_false_id; // = -1;
        //std::vector<int> neighbours;
        //std::map<bool, int> neighbours;
        std::string proc_id;
        CodeBlock(int _id) :id(_id) {
            next_true= nullptr;
            next_false= nullptr;
            next_true_id = -1;
            next_false_id = -1;
        }
        

};

#endif //COMPILER_CODDEBLOCK_H