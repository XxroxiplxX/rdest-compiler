#ifndef COMPILER_BLOCKS_CODEBLOCK
#define COMPILER_BLOCKS_CODEBLOCK

#include "Block.h"
#include "Instruction.h"
#include <memory>
#include <vector>
namespace ast::blocks::fields {
class CodeBlock {
  bool is_empty;
  bool is_last;
  int ip;
  int id;
  bool is_visited;
  bool is_translated;
  std::shared_ptr<CodeBlock> next_true;
  std::shared_ptr<CodeBlock> next_false;
  std::vector<std::shared_ptr<Instruction>> meat;

public:
  CodeBlock();
  bool is_codeblock_empty() const;
  bool is_codeblock_last() const;
  bool is_codeblock_visited() const;
  bool is_codeblock_translated() const;
  int get_codeblock_instruction_pointer() const;
  int get_codeblock_id() const;
  std::shared_ptr<CodeBlock> get_next_true_codeblock() const;
  std::shared_ptr<CodeBlock> get_next_false_codeblock() const;
  std::vector<std::shared_ptr<Instruction>> &get_all_instructions();

  void set_codeblock_empty();
  void set_codeblock_last();
  void set_codeblock_visited();
  void set_codeblock_translated();
  void set_codeblock_instruction_pointer(int _ip);
  void set_codeblock_id(int _id);
  void set_next_true_codeblock(std::shared_ptr<CodeBlock> &);
  void set_next_false_codeblock(std::shared_ptr<CodeBlock> &);
  void push_new_instruction(std::shared_ptr<Instruction> &instruction);
};

} // namespace ast::blocks::fields

#endif // COMPILER_BLOCKS_CODEBLOCK