
#include "ExpressionBuilder.h"
namespace ast::blocks::builders {
// ExpressionBuilder
void ExpressionBuilder::reset() {
  expression = std::make_shared<Expression>(Expression());
}
ExpressionBuilder::ExpressionBuilder() { reset(); }
ExpressionBuilder &ExpressionBuilder::build_left_value(Value *val) {
  expression->set_left(val);
  return *this;
}
ExpressionBuilder &ExpressionBuilder::build_right_value(Value *val) {
  expression->set_right(val);
  return *this;
}
ExpressionBuilder &
ExpressionBuilder::build_operator(_type_of_operator _operator) {
  expression->set_operator(_operator);
  return *this;
}
std::shared_ptr<Expression> &ExpressionBuilder::return_built_obj() {
  return expression;
}
} // namespace ast::blocks::builders
