#ifndef COMPILER_TREE_CONFIGURATION_PROVIDER
#define COMPILER_TREE_CONFIGURATION_PROVIDER
#include "Block.h"
#include "CodeBlock.h"
#include "CodeBlockBuilder.h"
#include "EdgeProvider.h"
#include "ExpressionBuilder.h"
#include "InstructionBuilder.h"
#include <compiler-utils/src/Logger.h>
#include <memory>
#include <vector>

namespace ast::providers {
using namespace blocks;

class TreeConfigurationProvider {
  Logging::Logger log{"tree_configuration_provider_log.log"};
  int configuration_id;
  std::vector<EdgeProvider> providers_vector;
  std::unique_ptr<builders::CodeBlockBuilder> codeblock_builder;
  std::unique_ptr<builders::InstructionBuilder> instruction_builder;
  std::unique_ptr<builders::ExpressionBuilder> expression_builder;

public:
  TreeConfigurationProvider();
  void increment_configuration_id();
  int get_configuration_id();
  TreeConfigurationProvider &add_configuration();
  TreeConfigurationProvider &set_begin_id(std::string &begin_id,
                                          std::string &configuration_id);
  TreeConfigurationProvider &set_end_id(std::string &end_id,
                                        std::string &configuration_id);
  EdgeProvider &get_configuration(std::string &configuration_id);
  std::unique_ptr<builders::CodeBlockBuilder> &get_codeblock_builder();
  std::unique_ptr<builders::InstructionBuilder> &get_instruction_builder();
  std::unique_ptr<builders::ExpressionBuilder> &get_expression_builder();
};

} // namespace ast::providers
#endif // TREE_CONFIGURATION_PROVIDER