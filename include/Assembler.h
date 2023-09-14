#ifndef COMPILER_ASSEMBLER
#define COMPILER_ASSEMBLER
#include "Architecture.h"
#include "CodeBlock.h"
#include <memory>
namespace Assembler {

class AsmInstruction {
  std::string opcode;
  int instruction_pointer;

public:
  virtual ~AsmInstruction();
  virtual void resolve_jump() = 0;
  virtual void print(std::ostream &os) const = 0;
};
class AsmBasicInstruction : public AsmInstruction {
  std::shared_ptr<VirtualMachineModel::Register> adress;

public:
  void print(std::ostream &os) const override;
  void resolve_jump() override;
};
class AsmJump : public AsmInstruction {
  std::shared_ptr<Blocks::CodeBlock> codeblock_to_jump;

public:
  void print(std::ostream &os) const override;
  void resolve_jump() override;
};
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

} // namespace Assembler

#endif // COMPILER_ASSEMBLER