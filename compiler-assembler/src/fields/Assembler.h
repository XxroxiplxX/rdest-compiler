#ifndef COMPILER_ASSEMBLER
#define COMPILER_ASSEMBLER
//#include <compiler-ast/src/Block.h>
#include "compiler-memory/src/Register.h"
#include <compiler-ast/src/fields/CodeBlock.h>
#include <memory>
#include <string>

namespace assembler::fields {
#define DEFAULT_ASSEMBLER_ARG_BEGIN 10
#define DEFAULT_ASSEMBLER_ARG_SPACING 12
using ast::blocks::fields::CodeBlock;
class AsmInstruction {
protected:
  std::string opcode;
  std::string comment;

public:
  virtual void resolve_jump() = 0;
  virtual void print(std::ostream &os) = 0;
  void set_opcode(const char*_opcode);
  void set_comment(const char*_comment);
  virtual void
  set_codeblock_to_jump(std::shared_ptr<CodeBlock> &codeblock) {}
  virtual void
  set_address(std::shared_ptr<memory::Register>& _register) {}
  virtual void set_constant(const char*_constant) {}
};

class AsmJumpInstruction : public AsmInstruction {
  std::shared_ptr<CodeBlock> codeblock_to_jump;
  std::string jump_address;
public:
  void
  set_codeblock_to_jump(std::shared_ptr<CodeBlock> &codeblock) override;
  void print(std::ostream &os) override;
  void resolve_jump() override;
};

class AsmNotJumpInstruction : public AsmInstruction {
public:
  void resolve_jump() override {}
  void print(std::ostream &os) override;
};
class AsmBasicInstruction : public AsmNotJumpInstruction {
  std::shared_ptr<memory::Register> address;

public:
void print(std::ostream &os) override;
  void
  set_address(std::shared_ptr<memory::Register>& _register) override;
};

class AsmSingleInstruction : public AsmNotJumpInstruction {
public:
};
class AsmConstantInstruction : public AsmNotJumpInstruction {
  std::string constant;

public:
void print(std::ostream &os) override;
  void set_constant(const char*_constant) override;
};

} // namespace assembler::fields

#endif // COMPILER_ASSEMBLER