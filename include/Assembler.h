#ifndef COMPILER_ASSEMBLER
#define COMPILER_ASSEMBLER
#include "Architecture.h"
#include "CodeBlock.h"
#include <memory>
namespace Assembler {

class AsmInstruction {
  std::string opcode;

public:
  virtual void resolve_jump() = 0;
  virtual void print(std::ostream &os) const = 0;
};

class AsmJumpInstruction : public AsmInstruction {
  std::shared_ptr<Blocks::CodeBlock> codeblock_to_jump;

public:
  void print(std::ostream &os) const override;
  void resolve_jump() override;
};

class AsmNotJumpInstruction : public AsmInstruction {
public:
  virtual void resolve_jump() override;
};
class AsmBasicInstruction : public AsmNotJumpInstruction {
  std::shared_ptr<VirtualMachineModel::Register> adress;

public:
  void print(std::ostream &os) const override;
};

class AsmSingleInstruction : public AsmNotJumpInstruction {
public:
  void print(std::ostream &os) const override;
};
class AsmConstantInstruction : public AsmNotJumpInstruction {
  std::string constant;

public:
  void print(std::ostream &os) const override;
};




/*
class AssemblerFactory {
public:
  virtual ~AssemblerFactory();
  virtual std::unique_ptr<AsmInstruction> &create_asm_instruction() const;
};
class AsmBasicInstructionFactory : public AssemblerFactory {
public:
  std::unique_ptr<AsmInstruction> &create_asm_instruction() const override;
};
class AsmJumpFactory : public AssemblerFactory {
public:
  std::unique_ptr<AsmInstruction> &create_asm_instruction() const override;
};
class AsmSingleInstructionFactory : public AssemblerFactory {
public:
  std::unique_ptr<AsmInstruction> &create_asm_instruction() const override;
};*/

} // namespace Assembler

#endif // COMPILER_ASSEMBLER