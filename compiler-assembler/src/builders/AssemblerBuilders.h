#ifndef ASSEMBLER_BUILDER
#define ASSEMBLER_BUILDER

#include "Assembler.h"

namespace assembler::builders {
using namespace fields;
using ast::blocks::fields::CodeBlock;
class AsmInstructionBuilder {
protected:
  std::shared_ptr<AsmInstruction> asm_instruction_ptr;

public:
  virtual void reset() = 0;
  virtual ~AsmInstructionBuilder() = default;
  virtual std::shared_ptr<AsmInstruction> return_built_instruction() = 0;
  AsmInstructionBuilder &build_instruction_opcode(const char*_opcode);
  AsmInstructionBuilder &build_instruction_comment(const char*_comment);
};
class AsmJumpInstructionBuilder : public AsmInstructionBuilder {
public:
  AsmJumpInstructionBuilder();
  AsmInstructionBuilder &
  build_codeblock_to_jump(std::shared_ptr<CodeBlock> &codeblock);
  void reset() override;
  std::shared_ptr<AsmInstruction> return_built_instruction() override;
};
class AsmBasicInstructionBuilder : public AsmInstructionBuilder {
public:
  AsmBasicInstructionBuilder();
  void reset() override;
  std::shared_ptr<AsmInstruction> return_built_instruction() override;
  AsmInstructionBuilder &build_instruction_address(
      std::shared_ptr<memory::Register> &_address);
};
class AsmSingleInstructionBuilder : public AsmInstructionBuilder {
public:
  AsmSingleInstructionBuilder();
  void reset() override;
  std::shared_ptr<AsmInstruction> return_built_instruction() override;
};
class AsmConstantInstructionBuilder : public AsmInstructionBuilder {
public:
  AsmConstantInstructionBuilder();
  void reset() override;
  std::shared_ptr<AsmInstruction> return_built_instruction() override;
  AsmInstructionBuilder &
  build_instruction_constant(const char*_constant);
};
} // namespace assembler::builders

#endif