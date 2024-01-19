

#ifndef RDEST_COMPILER_INSTRUCTIONBUILDER_H
#define RDEST_COMPILER_INSTRUCTIONBUILDER_H

#include "BlockBuilder.h"
#include "Instruction.h"
namespace ast::blocks::builders {

class InstructionBuilder : public BlockBuilder<Instruction> {

  std::shared_ptr<Instruction> instruction;

public:
  void reset() override;
  InstructionBuilder();
  InstructionBuilder &build_left_value(Value *val) override;
  InstructionBuilder &build_right_value(Value *val) override;
  InstructionBuilder &build_operator(_type_of_operator _operator) override;
  InstructionBuilder &build_enable_while_cond();
  InstructionBuilder &build_expression(Expression &e);
  InstructionBuilder &build_args_vector(std::shared_ptr<Value> &arg);
  InstructionBuilder &build_proc_id(std::string id);
  std::shared_ptr<Instruction> &return_built_obj() override;
};
} // namespace ast::blocks::builders

#endif // RDEST_COMPILER_INSTRUCTIONBUILDER_H
