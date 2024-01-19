

#ifndef RDEST_COMPILER_CODEBLOCKBUILDER_H
#define RDEST_COMPILER_CODEBLOCKBUILDER_H

#include "CodeBlock.h"
#include "Instruction.h"
namespace ast::blocks::builders {
using namespace fields;
class CodeBlockBuilder {
  std::shared_ptr<CodeBlock> codeblock;

public:
  CodeBlockBuilder();
  void reset();
  CodeBlockBuilder &build_codeblock_empty();
  CodeBlockBuilder &build_codeblock_last();
  CodeBlockBuilder &build_codeblock_visited();
  CodeBlockBuilder &build_codeblock_translated();
  CodeBlockBuilder &build_codeblock_instruction_pointer(int _ip);
  CodeBlockBuilder &build_codeblock_id(int _id);
  CodeBlockBuilder &build_next_true_codeblock(std::shared_ptr<CodeBlock> &);
  CodeBlockBuilder &build_next_false_codeblock(std::shared_ptr<CodeBlock> &);
  CodeBlockBuilder &
  build_new_added_instruction(std::shared_ptr<Instruction> &instruction);
  std::shared_ptr<CodeBlock> return_built_obj();
};
} // namespace ast::blocks::builders

#endif // RDEST_COMPILER_CODEBLOCKBUILDER_H
