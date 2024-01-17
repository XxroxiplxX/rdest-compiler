#ifndef COMPILER_TREE_CONFIGURATION_PROVIDER
#define COMPILER_TREE_CONFIGURATION_PROVIDER
#include "Block.h"
#include "CodeBlock.h"

#include "compiler-utils/src/Logger.h"
#include <memory>
#include <vector>

class EdgeProvider {
  int _begin_id;
  int _end_id;

public:
  int get_begin_id() const;
  void set_begin_id(int to_set);
  int get_end_id() const;
  void set_end_id(int to_set);
};

class TreeConfigurationProvider {
  Logging::Logger log{"tree_configuration_provider_log.log"};
  int configuration_id;
  std::vector<EdgeProvider> providers_vector;
  std::unique_ptr<Blocks::CodeBlockBuilder> codeblock_builder;
  std::unique_ptr<Blocks::InstructionBuilder> instruction_builder;
  std::unique_ptr<Blocks::ExpressionBuilder> expression_builder;

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
  std::unique_ptr<Blocks::CodeBlockBuilder> &get_codeblock_builder();
  std::unique_ptr<Blocks::InstructionBuilder> &get_instruction_builder();
  std::unique_ptr<Blocks::ExpressionBuilder> &get_expression_builder();
};

#endif // TREE_CONFIGURATION_PROVIDER