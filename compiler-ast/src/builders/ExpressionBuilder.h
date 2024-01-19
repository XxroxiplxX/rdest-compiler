

#ifndef RDEST_COMPILER_EXPRESSIONBUILDER_H
#define RDEST_COMPILER_EXPRESSIONBUILDER_H
#include "BlockBuilder.h"
#include "Expression.h"

namespace ast::blocks::builders {

class ExpressionBuilder : public BlockBuilder<Expression> {
  std::shared_ptr<Expression> expression;

public:
  void reset() override;
  ExpressionBuilder();
  ExpressionBuilder &build_left_value(Value *val) override;
  ExpressionBuilder &build_right_value(Value *val) override;
  ExpressionBuilder &build_operator(_type_of_operator _operator) override;
  std::shared_ptr<Expression> &return_built_obj() override;
};
} // namespace ast::blocks::builders

#endif // RDEST_COMPILER_EXPRESSIONBUILDER_H
