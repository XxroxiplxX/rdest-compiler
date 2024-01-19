#include "Assembler.h"
#include <compiler-ast/src/fields/CodeBlock.h>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <iostream>
namespace assembler::fields {
using std::to_string;

void AsmInstruction::set_opcode(const char *_opcode) { opcode = _opcode; }

void AsmInstruction::set_comment(const char *_comment) { comment = _comment; }

void AsmJumpInstruction::set_codeblock_to_jump(
    std::shared_ptr<CodeBlock> &codeblock) {
  codeblock_to_jump = codeblock;
}

void AsmJumpInstruction::print(std::ostream &os) {
  resolve_jump();
  if (comment != "") {
    comment = "[" + comment + "]";
  }
  os << std::left << std::setw(10) << opcode << std::setw(10) << jump_address
     << comment << std::endl;
}

void AsmJumpInstruction::resolve_jump() {
  if (!codeblock_to_jump)
    throw std::runtime_error("codeblock_to_jump unset");
  auto ip = codeblock_to_jump->get_codeblock_instruction_pointer();
  if (ip == -1)
    throw std::runtime_error("instruction pointer for untranslated codeblock");
  jump_address =
      to_string(codeblock_to_jump->get_codeblock_instruction_pointer());
}

void AsmNotJumpInstruction::print(std::ostream &os) {}

void AsmBasicInstruction::print(std::ostream &os) {
  if (comment != "") {
    comment = "[" + comment + "]";
  }
  os << std::left << std::setw(10) << opcode << std::setw(10)
     << address->get_id_as_string() << comment << std::endl;
}

void AsmBasicInstruction::set_address(
    std::shared_ptr<memory::Register> &_register) {
  address = _register;
}

void AsmConstantInstruction::print(std::ostream &os) {
  if (comment != "") {
    comment = "[" + comment + "]";
  }
  os << std::left << std::setw(10) << opcode << std::setw(10)
     << constant << comment << std::endl;
}

void AsmConstantInstruction::set_constant(const char *_constant) {
  AsmInstruction::set_constant(_constant);
}
} // namespace assembler::fields