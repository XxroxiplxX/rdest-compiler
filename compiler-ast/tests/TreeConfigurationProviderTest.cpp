#include "Block.h"
#include "CodeBlock.h"
#include "gtest/gtest.h"
#include <memory>

namespace ut {
using namespace ast::blocks;
class TreeConfigurationProviderTest : public ::testing::Test {
public:
  std::shared_ptr<fields::CodeBlock> codeblock_ptr_array[5] = {
      std::shared_ptr<fields::CodeBlock>(new fields::CodeBlock()),
      std::shared_ptr<fields::CodeBlock>(new fields::CodeBlock()),
      std::shared_ptr<fields::CodeBlock>(new fields::CodeBlock()),
      std::shared_ptr<fields::CodeBlock>(new fields::CodeBlock()),
      std::shared_ptr<fields::CodeBlock>(new fields::CodeBlock())};
};
TEST_F(TreeConfigurationProviderTest, incomplete_binary_tree) {
  codeblock_ptr_array[0]->set_next_true_codeblock(codeblock_ptr_array[1]);
  codeblock_ptr_array[0]->set_next_false_codeblock(codeblock_ptr_array[2]);

  codeblock_ptr_array[1]->set_next_true_codeblock(codeblock_ptr_array[3]);
  codeblock_ptr_array[1]->set_next_false_codeblock(codeblock_ptr_array[4]);

  EXPECT_TRUE(codeblock_ptr_array[0]->get_next_false_codeblock());
  EXPECT_TRUE(codeblock_ptr_array[0]->get_next_true_codeblock());

  EXPECT_TRUE(codeblock_ptr_array[1]->get_next_false_codeblock());
  EXPECT_TRUE(codeblock_ptr_array[1]->get_next_true_codeblock());

  EXPECT_FALSE(codeblock_ptr_array[2]->get_next_false_codeblock());
  EXPECT_FALSE(codeblock_ptr_array[2]->get_next_true_codeblock());
}
} // namespace ut