//
// Created by korycki on 1/19/2024.
//

#ifndef RDEST_COMPILER_INSTRUCTION_H
#define RDEST_COMPILER_INSTRUCTION_H

#include "Block.h"
#include "Expression.h"
namespace ast::blocks::fields {
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
  void push_arg(std::shared_ptr<Value> &val);
  void set_proc_id(std::string id);
  std::string get_proc_id() const;
};
} // namespace ast::blocks::fields

#endif // RDEST_COMPILER_INSTRUCTION_H
