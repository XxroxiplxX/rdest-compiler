
#include <compiler-ast/src/CodeBlock.h>

#include "gtest/gtest.h"
#include <memory>
namespace UnitTests {
TEST(CodeBlockTest, basic_codeblock_creation) {
  std::unique_ptr<Blocks::CodeBlockBuilder> codeblock_builder_ptr(
      new Blocks::CodeBlockBuilder());
  std::unique_ptr<Blocks::InstructionBuilder> instruction_builder_ptr(
      new Blocks::InstructionBuilder());
  std::unique_ptr<Blocks::ExpressionBuilder> expression_builder_ptr(
      new Blocks::ExpressionBuilder());
  auto cb1 = codeblock_builder_ptr->build_codeblock_id(3)
                 .build_new_added_instruction(
                     instruction_builder_ptr->build_proc_id("proc3")
                         .return_builded_obj())
                 .return_built_obj();
  EXPECT_EQ(3, cb1->get_codeblock_id());
  EXPECT_EQ("proc3", cb1->get_all_instructions()[0]->get_proc_id());
}
} // namespace UnitTests