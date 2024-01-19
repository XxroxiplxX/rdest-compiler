#ifndef COMPILER_BLOCKS_BLOCK
#define COMPILER_BLOCKS_BLOCK
#include "Value.h"
#include <memory>
#include <vector>
namespace ast::blocks::fields {
enum _type_of_meat {
  _COND = 1,
  _READ = 2,
  _WRITE = 3,
  _ASS = 4,
  _CALL = 16,
  _ENDWHILE = 17

};

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
};

class Block {
protected:
  std::shared_ptr<Value> left;
  std::shared_ptr<Value> right;
  _type_of_operator type_of_operator;

public:
  virtual ~Block() {}
  void set_left(Value *val);
  void set_right(Value *val);
  std::shared_ptr<Value> get_left();
  std::shared_ptr<Value> get_right();
  void set_operator(_type_of_operator type);
  _type_of_operator get_operator() const;
};

} // namespace ast::blocks::fields

#endif