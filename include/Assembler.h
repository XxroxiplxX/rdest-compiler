#ifndef COMPILER_ASSEMBLER
#define COMPILER_ASSEMBLER
#include "Architecture.h"
#include "CodeBlock.h"
#include <memory>
namespace Assembler {
#define DEFAULT_ASSEMBLER_ARG_BEGIN 10
#define DEFAULT_ASSEMBLER_ARG_SPACING 12
class AsmInstruction {
  protected:

  std::string opcode;
  std::string comment;

public:
  
  virtual void resolve_jump() = 0;
  virtual void print(std::ostream &os) const = 0;
  void set_opcode(std::string &_opcode);
  void set_comment(std::string& _comment);
  virtual void
  set_codeblock_to_jump(std::shared_ptr<Blocks::CodeBlock> &codeblock){}
  virtual void
  set_adress(std::shared_ptr<VirtualMachineModel::Register> _register){}
  virtual void set_constant(std::string& _constant) {}
};

class AsmJumpInstruction : public AsmInstruction {
  std::shared_ptr<Blocks::CodeBlock> codeblock_to_jump;

public:
  void
  set_codeblock_to_jump(std::shared_ptr<Blocks::CodeBlock> &codeblock) override;
  void print(std::ostream &os) const override;
  void resolve_jump() override;
};

class AsmNotJumpInstruction : public AsmInstruction {
public:
  virtual void resolve_jump() override {}
};
class AsmBasicInstruction : public AsmNotJumpInstruction {
  std::shared_ptr<VirtualMachineModel::Register> adress;

public:
  void
  set_adress(std::shared_ptr<VirtualMachineModel::Register> _register) override;
  void print(std::ostream &os) const override;
};

class AsmSingleInstruction : public AsmNotJumpInstruction {
public:
  void print(std::ostream &os) const override;
};
class AsmConstantInstruction : public AsmNotJumpInstruction {
  std::string constant;

public:
  void set_constant(std::string& _constant) override;
  void print(std::ostream &os) const override;
};

class AsmInstructionBuilder {
protected:
  std::unique_ptr<AsmInstruction> asm_instruction_ptr;

public:
  virtual void reset() = 0;
  virtual ~AsmInstructionBuilder() {}
  virtual std::unique_ptr<AsmInstruction> &return_built_instruction() = 0;
  AsmInstructionBuilder &build_instruction_opcode(std::string &_opcode);
  AsmInstructionBuilder &build_instruction_comment(std::string &_comment);
};
class AsmJumpInstructionBuilder : public AsmInstructionBuilder {
public:
  AsmInstructionBuilder &
  build_codeblock_to_jump(std::shared_ptr<Blocks::CodeBlock> &codeblock);
  void reset() override;
  std::unique_ptr<AsmInstruction> &return_built_instruction() override;
};
class AsmBasicInstructionBuilder : public AsmInstructionBuilder {
public:
  void reset() override;
  std::unique_ptr<AsmInstruction> &return_built_instruction() override;
  AsmBasicInstructionBuilder &build_instruction_address(
      std::shared_ptr<VirtualMachineModel::Register> &_address);
};
class AsmSingleInstructionBuilder : public AsmInstructionBuilder {
public:
  void reset() override;
  std::unique_ptr<AsmInstruction> &return_built_instruction() override;
};
class AsmConstantInstructionBuilder : public AsmInstructionBuilder {
public:
  void reset() override;
  std::unique_ptr<AsmInstruction> &return_built_instruction() override;
  AsmConstantInstructionBuilder &
  build_instruction_constant(const std::string &_constant);
};


} // namespace Assembler

#endif // COMPILER_ASSEMBLER