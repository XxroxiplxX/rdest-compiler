#include "CodeBlock.h"
#include <memory>

namespace Blocks {
bool CodeBlock::is_codeblock_empty() const { return is_empty; }
bool CodeBlock::is_codeblock_last() const { return is_last; }
bool CodeBlock::is_codeblock_visited() const { return is_visited; }
bool CodeBlock::is_codeblock_translated() const { return is_translated; }
int CodeBlock::get_codeblock_instruction_pointer() const { return ip; }
int CodeBlock::get_codeblock_id() const { return id; }
std::shared_ptr<CodeBlock> CodeBlock::get_next_true_codeblock() const {
  return next_true;
}
std::shared_ptr<CodeBlock> CodeBlock::get_next_false_codeblock() const {
  return next_false;
}
std::vector<std::shared_ptr<Instruction>> &CodeBlock::get_all_instructions() {
  return meat;
}

void CodeBlock::set_codeblock_empty() { is_empty = true; }
void CodeBlock::set_codeblock_last() { is_last = true; }
void CodeBlock::set_codeblock_visited() { is_visited = true; }
void CodeBlock::set_codeblock_translated() { is_translated = true; }
void CodeBlock::set_codeblock_instruction_pointer(int _ip) { ip = _ip; }
void CodeBlock::set_codeblock_id(int _id) { id = _id; }
void CodeBlock::set_next_true_codeblock(std::shared_ptr<CodeBlock> &nt) {
  next_true = nt;
}
void CodeBlock::set_next_false_codeblock(std::shared_ptr<CodeBlock> &nf) {
  next_false = nf;
}
void CodeBlock::push_new_instruction(
    std::shared_ptr<Instruction> &instruction) {
  meat.push_back(instruction);
}

void CodeBlockBuilder::reset() {
  codeblock = std::shared_ptr<CodeBlock>(new CodeBlock);
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
} // namespace Blocks