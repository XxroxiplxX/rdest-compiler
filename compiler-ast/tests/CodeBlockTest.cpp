
#include "CodeBlockBuilder.h"
#include "ExpressionBuilder.h"
#include "InstructionBuilder.h"

#include "gtest/gtest.h"
#include <memory>
namespace ut {
using namespace ast::blocks;
TEST(CodeBlockTest, basic_codeblock_creation) {
  std::unique_ptr<builders::CodeBlockBuilder> codeblock_builder_ptr(
      new builders::CodeBlockBuilder());
  std::unique_ptr<builders::InstructionBuilder> instruction_builder_ptr(
      new builders::InstructionBuilder());
  std::unique_ptr<builders::ExpressionBuilder> expression_builder_ptr(
      new builders::ExpressionBuilder());
  auto cb1 = codeblock_builder_ptr->build_codeblock_id(3)
                 .build_new_added_instruction(
                     instruction_builder_ptr->build_proc_id("proc3")
                         .return_built_obj())
                 .return_built_obj();
  EXPECT_EQ(3, cb1->get_codeblock_id());
  EXPECT_EQ("proc3", cb1->get_all_instructions()[0]->get_proc_id());
}
} // namespace ut