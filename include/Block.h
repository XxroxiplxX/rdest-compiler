#ifndef COMPILER_BLOCKS_BLOCK
#define COMPILER_BLOCKS_BLOCK

#include "ValueFactory.h"
#include <memory>
#include <vector>
namespace Blocks {
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
using namespace ValueTypes;
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

class Expression : public Block {

  

public:
  
  // std::string exp_to_string() {
  //     return "%%%exp---->" + left.val_to_string() + "____" +
  //     std::to_string(type_of_operator) + "____" + right.val_to_string();
  // }
};
class Instruction : public Block {
  bool _while_cond;
  _type_of_meat type_of_instruction;
  Expression expr;
  std::vector<std::shared_ptr<Value>> args;
  std::string proc_id;

public:
  Instruction();
  bool is_while_cond() const;
  void enable_while_cond();
  Expression &get_expression();
  void set_expression(Expression &expression);
  std::vector<std::shared_ptr<Value>> get_args_vector() const;
  void push_arg(std::shared_ptr<Value> val);
  void set_proc_id(std::string id);
  std::string get_proc_id() const;
};
template <class Construction> class Builder {
public:
  virtual ~Builder() {}
  virtual Builder &build_left_value(Value* val) = 0;
  virtual Builder &build_right_value(Value* val) = 0;
  virtual Builder &build_operator(_type_of_operator _operator) = 0;
  virtual void reset() = 0;
  virtual std::shared_ptr<Construction> return_builded_obj() const = 0;
};

class InstructionBuilder : public Builder<Instruction> {

  std::shared_ptr<Instruction> instruction;
  

public:
  void reset() override;
  InstructionBuilder();
  InstructionBuilder &build_left_value(Value* val) override;
  InstructionBuilder &build_right_value(Value* val) override;
  InstructionBuilder &build_operator(_type_of_operator _operator) override;
  InstructionBuilder &build_enable_while_cond();
  InstructionBuilder &build_expression(Expression& e);
  InstructionBuilder &build_args_vector(std::shared_ptr<Value> arg);
  InstructionBuilder &build_proc_id(std::string id);
  std::shared_ptr<Instruction> return_builded_obj() const override;
};

class ExpressionBuilder : public Builder<Expression> {
  std::shared_ptr<Expression> expression;
  

public:
  void reset() override;
  ExpressionBuilder();
  ExpressionBuilder &build_left_value(Value* val) override;
  ExpressionBuilder &build_right_value(Value* val) override;
  ExpressionBuilder &build_operator(_type_of_operator _operator) override;
  std::shared_ptr<Expression> return_builded_obj() const override;

};
} // namespace Blocks

#endif