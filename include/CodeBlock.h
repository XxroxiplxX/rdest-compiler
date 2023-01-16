#ifndef COMPILER_CODDEBLOCK_H
#define COMPILER_CODDEBLOCK_H


#include <vector>
#include<string>
enum type_of_value {
    _NUM = 1,
    _ID = 2
};
struct Value {
    int type;
    std::string load;
    Value() {
        type = 0;
    }
    Value(std::string _load) {
        if (_load[0] == 'I') {
            type = type_of_value::_ID;
            for (int i = 3; i < _load.length(); i++) {
                load += _load[i];
            }
        } else {
            type = type_of_value::_NUM;
            for (int i = 4; i < _load.length(); i++) {
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
    int type_of_operator;
    Value left;
    Value right;
};
struct Instruction {
    int type_of_instruction;
    int type_of_operator;
    Value left;
    Value right;
    Expression expr;
    std::vector<Value> args;
};

class CodeBlock {
    public:
        std::vector<Instruction> meat;
        
        CodeBlock(){}
        int id;
        std::vector<int> neighbours;
        
        CodeBlock(int _id) :id(_id) {}
        

};

#endif //COMPILER_CODDEBLOCK_H