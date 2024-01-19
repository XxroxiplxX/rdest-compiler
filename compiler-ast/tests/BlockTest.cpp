#include "Block.h"
#include "ExpressionBuilder.h"
#include "ValueFactory.h"
#include "gtest/gtest.h"
namespace ut {
using namespace ast::blocks;
class ExpressionBuilderTest : public ::testing::Test {
public:
  std::string value_templates[4] = {"ID_z", "NUM_12", "ID_var", "NUM_100"};
  builders::ValueFactory value_factory;
};

TEST_F(ExpressionBuilderTest, two_objects_created) {
  builders::ExpressionBuilder eb;
  auto exp =
      eb.build_left_value(value_factory.create_value(value_templates[0]))
          .build_right_value(value_factory.create_value(value_templates[1]))
          .build_operator(fields::_ADD)
          .return_built_obj();
  EXPECT_EQ(exp->get_operator(), fields::_ADD);
  EXPECT_EQ(exp->get_left()->get_val(), "z");
  eb.reset();
  auto exp2 =
      eb.build_left_value(value_factory.create_value(value_templates[2]))
          .build_right_value(value_factory.create_value(value_templates[3]))
          .build_operator(fields::_MUL)
          .return_built_obj();
  EXPECT_EQ(exp2->get_operator(), fields::_MUL);
  EXPECT_EQ(exp2->get_left()->get_val(), "var");
}
} // namespace ut