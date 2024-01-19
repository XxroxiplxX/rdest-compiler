#include "Block.h"
#include <memory>

namespace ast::blocks::fields {
// Block
void Block::set_left(Value *val) { left = std::shared_ptr<Value>(val); }
void Block::set_right(Value *val) { right = std::shared_ptr<Value>(val); }
std::shared_ptr<Value> Block::get_left() { return left; }
std::shared_ptr<Value> Block::get_right() { return right; }
void Block::set_operator(_type_of_operator type) { type_of_operator = type; }
_type_of_operator Block::get_operator() const { return type_of_operator; }

} // namespace ast::blocks::fields