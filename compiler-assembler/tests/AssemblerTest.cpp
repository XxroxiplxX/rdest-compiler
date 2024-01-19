#include "Assembler.h"
#include "AssemblerBuilders.h"
#include "CodeBlock.h"
#include "CodeBlockBuilder.h"
#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace ut {
using namespace assembler;
using namespace memory;
using ast::blocks::builders::CodeBlockBuilder;
class TestStream : public std::ostream {};
class AssemblerTest : public ::testing::Test {
public:
  friend fields::AsmInstruction;
  friend fields::AsmBasicInstruction;
  builders::AsmBasicInstructionBuilder basic_ins_builder;
  builders::AsmConstantInstructionBuilder const_ins_builder;
  builders::AsmJumpInstructionBuilder jump_ins_builder;
  builders::AsmSingleInstructionBuilder single_ins_builder;
  CodeBlockBuilder code_block_builder;
  std::shared_ptr<Register> test_register;
  void set_up() { test_register = std::make_shared<Register>(Register(5)); }
  std::ostringstream test_stream;
};

TEST_F(AssemblerTest, AsmBasicInstructionTest) {
  set_up();
  auto uut = basic_ins_builder.build_instruction_address(test_register)
                 .build_instruction_opcode("LOAD")
                 .build_instruction_comment("comment")
                 .return_built_instruction();
  uut->print(test_stream);
  EXPECT_EQ(test_stream.str(), "LOAD      5         [comment]\n");
}
TEST_F(AssemblerTest, AsmJumpInstructionTestSucces) {
  auto test_cb = code_block_builder.build_codeblock_instruction_pointer(10)
                     .return_built_obj();
  
  auto uut = jump_ins_builder.build_codeblock_to_jump(test_cb)
                 .build_instruction_opcode("JUMPI")
                 .build_instruction_comment("comment")
                 .return_built_instruction();
  EXPECT_NO_THROW(uut->print(test_stream));
  EXPECT_EQ(test_stream.str(), "JUMPI     10        [comment]\n");
}
TEST_F(AssemblerTest, AsmJumpInstructionTestFail_empty_codeblock) {
  auto uut = jump_ins_builder.build_instruction_opcode("JUMP").return_built_instruction();
  EXPECT_THROW(uut->print(test_stream), std::runtime_error);
}
TEST_F(AssemblerTest, AsmJumpInstructionTestFail_untranslated_codeblock) {
  auto test_cb = code_block_builder.build_codeblock_id(2).return_built_obj();
  auto uut = jump_ins_builder.build_codeblock_to_jump(test_cb).return_built_instruction();
  EXPECT_THROW(uut->print(test_stream), std::runtime_error);
}
} // namespace ut