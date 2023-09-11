#include "CodeBlock.h"

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

void CodeBlock::set_codeblock_empty() { is_empty = true; }
void CodeBlock::set_codeblock_last() { is_last = true; }
void CodeBlock::set_codeblock_visited() { is_visited = true; }
void CodeBlock::set_codeblock_translated() { is_translated = true; }
void CodeBlock::set_codeblock_instruction_pointer(int _ip) { ip = _ip; }
void CodeBlock::set_codeblock_id(int _id) { id = _id; }
void CodeBlock::set_next_true_codeblock(std::shared_ptr<CodeBlock> nt) {
  next_true = nt;
}
void CodeBlock::set_next_false_codeblock(std::shared_ptr<CodeBlock> nf) {
  next_false = nf;
}
} // namespace Blocks