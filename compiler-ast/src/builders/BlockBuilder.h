
#ifndef RDEST_COMPILER_BLOCKBUILDER_H
#define RDEST_COMPILER_BLOCKBUILDER_H

#include "Block.h"
#include "Value.h"
namespace ast::blocks::builders {
using namespace fields;
template <class Construction> class BlockBuilder {
public:
  virtual ~BlockBuilder() {}
  virtual BlockBuilder &build_left_value(Value *val) = 0;
  virtual BlockBuilder &build_right_value(Value *val) = 0;
  virtual BlockBuilder &build_operator(_type_of_operator _operator) = 0;
  virtual void reset() = 0;
  virtual std::shared_ptr<Construction> &return_built_obj() = 0;
};
} // namespace ast::blocks::builders

#endif // RDEST_COMPILER_BLOCKBUILDER_H
