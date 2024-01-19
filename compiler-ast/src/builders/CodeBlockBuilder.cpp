

#include "CodeBlockBuilder.h"

namespace ast::blocks::builders {
CodeBlockBuilder::CodeBlockBuilder() { reset(); }
void CodeBlockBuilder::reset() {
  codeblock = std::shared_ptr<CodeBlock>(new CodeBlock());
}
CodeBlockBuilder &CodeBlockBuilder::build_codeblock_empty() {
  codeblock->set_codeblock_empty();
  return *this;
}
CodeBlockBuilder &CodeBlockBuilder::build_codeblock_last() {
  codeblock->set_codeblock_last();
  return *this;
}
CodeBlockBuilder &CodeBlockBuilder::build_codeblock_visited() {
  codeblock->set_codeblock_visited();
  return *this;
}
CodeBlockBuilder &CodeBlockBuilder::build_codeblock_translated() {
  codeblock->set_codeblock_translated();
  return *this;
}
CodeBlockBuilder &
CodeBlockBuilder::build_codeblock_instruction_pointer(int _ip) {
  codeblock->set_codeblock_instruction_pointer(_ip);
  return *this;
}
CodeBlockBuilder &CodeBlockBuilder::build_codeblock_id(int _id) {
  codeblock->set_codeblock_id(_id);
  return *this;
}
CodeBlockBuilder &
CodeBlockBuilder::build_next_true_codeblock(std::shared_ptr<CodeBlock> &nt) {
  codeblock->set_next_true_codeblock(nt);
  return *this;
}
CodeBlockBuilder &
CodeBlockBuilder::build_next_false_codeblock(std::shared_ptr<CodeBlock> &nf) {
  codeblock->set_next_false_codeblock(nf);
  return *this;
}
CodeBlockBuilder &CodeBlockBuilder::build_new_added_instruction(
    std::shared_ptr<Instruction> &instruction) {
  codeblock->push_new_instruction(instruction);
  return *this;
}
std::shared_ptr<CodeBlock> CodeBlockBuilder::return_built_obj() {
  auto tmp = codeblock;
  reset();
  return tmp;
}
} // namespace ast::blocks::builders
