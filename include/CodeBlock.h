#include <vector>
#include<string>

enum _type_of_meat {
    _COND = 1,
    _READ = 2,
    _WRITE = 3,
    _ASS = 4,
} _type_of_meat;

enum _operators {
    _MUL = 5,
    _DIV = 6,
    _SUB = 7,
    _ADD = 8,
    _MOD = 9,
    _NONE = 0
} _operators;

struct Instruction {
    int type_of_instruction;
    int type_of_operator;
    std::string left;
    std::string mid;
    std::string right;
};

class CodeBlock {
    public:
        std::vector<std::string> meat;
        int id;
        CodeBlock(std:: string one, std::string two) {
            meat.push_back(one);
            meat.push_back(two);
        }

};