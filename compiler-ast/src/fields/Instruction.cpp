

#include "Instruction.h"

namespace ast::blocks::fields {
// Instruction
Instruction::Instruction() : _while_cond(false) {}
bool Instruction::is_while_cond() const { return _while_cond; }
void Instruction::enable_while_cond() { _while_cond = true; }
Expression &Instruction::get_expression() { return expr; }
void Instruction::set_expression(Expression &expression) { expr = expression; }
std::vector<std::shared_ptr<Value>> Instruction::get_args_vector() const {
  return args;
}
void Instruction::push_arg(std::shared_ptr<Value> &val) { args.push_back(val); }
void Instruction::set_proc_id(std::string id) { proc_id = id; }
std::string Instruction::get_proc_id() const { return proc_id; }
} // namespace ast::blocks::fields
