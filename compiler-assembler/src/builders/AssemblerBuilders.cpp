

#include "AssemblerBuilders.h"
// #include "Assembler.h"
#include <memory>
namespace assembler::builders {
AsmInstructionBuilder &
assembler::builders::AsmInstructionBuilder::build_instruction_opcode(
    const char *_opcode) {
  asm_instruction_ptr->set_opcode(_opcode);
  return *this;
}

AsmInstructionBuilder &
AsmInstructionBuilder::build_instruction_comment(const char *_comment) {
  asm_instruction_ptr->set_comment(_comment);
  return *this;
}

AsmInstructionBuilder &AsmJumpInstructionBuilder::build_codeblock_to_jump(
    std::shared_ptr<Blocks::CodeBlock> &codeblock) {
  asm_instruction_ptr->set_codeblock_to_jump(codeblock);
  return *this;
}

void AsmJumpInstructionBuilder::reset() {
  asm_instruction_ptr =
      std::make_shared<AsmJumpInstruction>(AsmJumpInstruction());
}

std::shared_ptr<AsmInstruction> 
AsmJumpInstructionBuilder::return_built_instruction() {
  auto tmp = asm_instruction_ptr;
  reset();
  return tmp;
}

AsmJumpInstructionBuilder::AsmJumpInstructionBuilder() { reset(); }

void AsmBasicInstructionBuilder::reset() {
  asm_instruction_ptr =
      std::make_shared<AsmBasicInstruction>(AsmBasicInstruction());
}

std::shared_ptr<AsmInstruction> 
AsmBasicInstructionBuilder::return_built_instruction() {
  auto tmp = asm_instruction_ptr;
  reset();
  return tmp;
}

AsmInstructionBuilder &AsmBasicInstructionBuilder::build_instruction_address(
    std::shared_ptr<VirtualMachineModel::Register> &_address) {
  asm_instruction_ptr->set_address(_address);
  return *this;
}

AsmBasicInstructionBuilder::AsmBasicInstructionBuilder() { reset(); }

void AsmSingleInstructionBuilder::reset() {
  asm_instruction_ptr =
      std::make_shared<AsmSingleInstruction>(AsmSingleInstruction());
}

std::shared_ptr<AsmInstruction> 
AsmSingleInstructionBuilder::return_built_instruction() {
  auto tmp = asm_instruction_ptr;
  reset();
  return tmp;
}

AsmSingleInstructionBuilder::AsmSingleInstructionBuilder() { reset(); }

void AsmConstantInstructionBuilder::reset() {
  asm_instruction_ptr =
      std::make_shared<AsmConstantInstruction>(AsmConstantInstruction());
}

std::shared_ptr<AsmInstruction> 
AsmConstantInstructionBuilder::return_built_instruction() {
  auto tmp = asm_instruction_ptr;
  reset();
  return tmp;
}

AsmInstructionBuilder &
AsmConstantInstructionBuilder::build_instruction_constant(
    const char *_constant) {
  asm_instruction_ptr->set_constant(_constant);
  return *this;
}

AsmConstantInstructionBuilder::AsmConstantInstructionBuilder() { reset(); }
} // namespace assembler::builders