
#include "InstructionBuilder.h"

namespace ast::blocks::builders {
// InstructionBuilder
void InstructionBuilder::reset() {
  instruction = std::make_shared<Instruction>(Instruction());
}
InstructionBuilder::InstructionBuilder() { reset(); }
InstructionBuilder &InstructionBuilder::build_left_value(Value *val) {
  instruction->set_left(val);
  return *this;
}
InstructionBuilder &InstructionBuilder::build_right_value(Value *val) {
  instruction->set_right(val);
  return *this;
}
InstructionBuilder &
InstructionBuilder::build_operator(_type_of_operator _operator) {
  instruction->set_operator(_operator);
  return *this;
}
InstructionBuilder &InstructionBuilder::build_enable_while_cond() {
  instruction->enable_while_cond();
  return *this;
}
InstructionBuilder &InstructionBuilder::build_expression(Expression &e) {
  instruction->set_expression(e);
  return *this;
}
InstructionBuilder &
InstructionBuilder::build_args_vector(std::shared_ptr<Value> &arg) {
  instruction->push_arg(arg);
  return *this;
}
InstructionBuilder &InstructionBuilder::build_proc_id(std::string id) {
  instruction->set_proc_id(id);
  return *this;
}
std::shared_ptr<Instruction> &InstructionBuilder::return_built_obj() {
  return instruction;
}
} // namespace ast::blocks::builders
