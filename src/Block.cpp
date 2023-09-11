#include "../include/Block.h"
#include <memory>

namespace Blocks {
// Block
void Block::set_left(Value *val) {
  left = std::shared_ptr<Value>(val);
}
void Block::set_right(Value *val) {
  right = std::shared_ptr<Value>(val);
}
std::shared_ptr<Value> Block::get_left() {
  return left;
}
std::shared_ptr<Value> Block::get_right() {
  return right;
}
void Block::set_operator(_type_of_operator type) {
  type_of_operator = type;
}
_type_of_operator Block::get_operator() const {
  return type_of_operator;
}

// Instruction
Instruction::Instruction() : _while_cond(false) {}
bool Instruction::is_while_cond() const {
  return _while_cond;
}
void Instruction::enable_while_cond() {
  _while_cond = true;
}
Expression &Instruction::get_expression()  {
  return expr;
}
void Instruction::set_expression(Expression &expression) {
  expr = expression;
}
std::vector<std::shared_ptr<Value>> Instruction::get_args_vector() const {
  return args;
}
void Instruction::push_arg(std::shared_ptr<Value> val) {
  args.push_back(val);
}
void Instruction::set_proc_id(std::string id) {
  proc_id = id;
}
std::string Instruction::get_proc_id() const {
  return proc_id;
}

// ExpressionBuilder
void ExpressionBuilder::reset() {
  expression = std::make_shared<Expression>(Expression());
}
ExpressionBuilder::ExpressionBuilder() {
  reset();
}
ExpressionBuilder &ExpressionBuilder::build_left_value(Value *val) {
  expression->set_left(val);
  return *this;
}
ExpressionBuilder &ExpressionBuilder::build_right_value(Value *val) {
  expression->set_right(val);
    return *this;
}
ExpressionBuilder &ExpressionBuilder::build_operator(_type_of_operator _operator) {
  expression->set_operator(_operator);
    return *this;
}
std::shared_ptr<Expression> ExpressionBuilder::return_builded_obj() const {
  return expression;
}

// InstructionBuilder
void InstructionBuilder::reset() {
  instruction = std::make_shared<Instruction>(Instruction());
}
InstructionBuilder::InstructionBuilder() {
  reset();
}
InstructionBuilder &InstructionBuilder::build_left_value(Value *val) {
  instruction->set_left(val);
    return *this;
}
InstructionBuilder &InstructionBuilder::build_right_value(Value *val) {
  instruction->set_right(val);
    return *this;
}
InstructionBuilder &InstructionBuilder::build_operator(_type_of_operator _operator) {
  instruction->set_operator(_operator);
  return *this;
}
InstructionBuilder &InstructionBuilder::build_enable_while_cond() {
  instruction->enable_while_cond();
  return *this;
}
InstructionBuilder &InstructionBuilder::build_expression(Expression& e) {
  instruction->set_expression(e);
    return *this;
}
InstructionBuilder &InstructionBuilder::build_args_vector(std::shared_ptr<Value> arg) {
  instruction->push_arg(arg);
    return *this;
}
InstructionBuilder &InstructionBuilder::build_proc_id(std::string id) {
  instruction->set_proc_id(id);
    return *this;
}
std::shared_ptr<Instruction> InstructionBuilder::return_builded_obj() const {
  return instruction;
}

} // namespace Blocks