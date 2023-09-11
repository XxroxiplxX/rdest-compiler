#include "TreeConfigurationProvider.h"
#include "Block.h"
#include "CodeBlock.h"
#include <memory>
#include <stdexcept>
#include <string>

int EdgeProvider::get_begin_id() const { return _begin_id; }
EdgeProvider &EdgeProvider::set_begin_id(std::string &to_set) {
  try {
    _begin_id = std::stoi(to_set);
  } catch (std::invalid_argument &e) {
    log.error("[%s] invalid argument for std::stoi: %s", __func__, to_set);
  } catch (std::out_of_range &e) {
    log.error("[%s] argument out of range for std::stoi: %s", __func__, to_set);
  }
  return *this;
}

int EdgeProvider::get_end_id() const { return _end_id; }
EdgeProvider &EdgeProvider::set_end_id(std::string &to_set) {
  try {
    _end_id = std::stoi(to_set);
  } catch (std::invalid_argument &e) {
    log.warning("[%s] invalid argument for std::stoi: %s", __func__, to_set);
  } catch (std::out_of_range &e) {
    log.warning("[%s] argument out of range for std::stoi: %s", __func__,
                to_set);
  }
  return *this;
}

void TreeConfigurationProvider::addConfiguration(EdgeProvider &edgeProvider) {
  providers_vector.push_back(edgeProvider);
}
TreeConfigurationProvider::TreeConfigurationProvider()
    : configuration_id(0),
      codeblock_builder(std::make_unique<Blocks::CodeBlockBuilder>(
          Blocks::CodeBlockBuilder())),
      instruction_builder(std::make_unique<Blocks::InstructionBuilder>(
          Blocks::InstructionBuilder())),
      expression_builder(std::make_unique<Blocks::ExpressionBuilder>(
          Blocks::ExpressionBuilder())) {}
void TreeConfigurationProvider::increment_configuration_id() {
  configuration_id++;
}
int TreeConfigurationProvider::get_configuration_id() {
  return configuration_id;
}
EdgeProvider &
TreeConfigurationProvider::get_configuration(std::string &configuration_id) {
  int conf_id;
  try {
    conf_id = std::stoi(configuration_id);
  } catch (std::invalid_argument &e) {
    log.warning("[%s] invalid argument for std::stoi: %s", __func__,
                configuration_id);
  } catch (std::out_of_range &e) {
    log.warning("[%s] argument out of range for std::stoi: %s", __func__,
                configuration_id);
  }
  if (conf_id > providers_vector.size() - 1) {
    log.error("[%s] argument out of range for providers_vector: %s", __func__,
              configuration_id);
  }
  return providers_vector[conf_id];
}
std::unique_ptr<Blocks::CodeBlockBuilder> &
TreeConfigurationProvider::get_codeblock_builder() {
  return codeblock_builder;
}
std::unique_ptr<Blocks::InstructionBuilder> &
TreeConfigurationProvider::get_instruction_builder() {
  return instruction_builder;
}
std::unique_ptr<Blocks::ExpressionBuilder> &
TreeConfigurationProvider::get_expression_builder() {
  return expression_builder;
}