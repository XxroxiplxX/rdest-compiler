#include "Block.h"
#include "CodeBlock.h"
#include "ValueFactory.h"
#include "TreeConfigurationProvider.h"
#include "gtest/gtest.h"
#include <memory>

namespace UnitTests {
  class TreeConfigurationProviderTest : public ::testing::Test {
    public:
      std::shared_ptr<Blocks::CodeBlock> codeblock_ptr_array[5] = {
        std::shared_ptr<Blocks::CodeBlock>(new Blocks::CodeBlock()),
        std::shared_ptr<Blocks::CodeBlock>(new Blocks::CodeBlock()),
        std::shared_ptr<Blocks::CodeBlock>(new Blocks::CodeBlock()),
        std::shared_ptr<Blocks::CodeBlock>(new Blocks::CodeBlock()),
        std::shared_ptr<Blocks::CodeBlock>(new Blocks::CodeBlock())
      };
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
}