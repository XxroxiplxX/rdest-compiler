#include "TreeConfigurationProvider.h"
#include "Block.h"
#include "CodeBlock.h"
#include <memory>
#include <stdexcept>
#include <string>

int EdgeProvider::get_begin_id() const { return _begin_id; }
void EdgeProvider::set_begin_id(int to_set) { _begin_id = to_set; }

int EdgeProvider::get_end_id() const { return _end_id; }
void EdgeProvider::set_end_id(int to_set) { _end_id = to_set; }

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
TreeConfigurationProvider &TreeConfigurationProvider::add_configuration() {
  providers_vector.push_back(EdgeProvider());
  return *this;
}
TreeConfigurationProvider &
TreeConfigurationProvider::set_begin_id(std::string &begin_id,
                                        std::string &configuration_id) {
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

  if (conf_id >= providers_vector.size()) {
    log.error("[%s] looking for unexisting configuration with id: %d", __func__,
              conf_id);
  }

  try {
    providers_vector[conf_id].set_begin_id(std::stoi(begin_id));
  } catch (std::invalid_argument &e) {
    log.warning("[%s] invalid argument for std::stoi: %s", __func__, begin_id);
  } catch (std::out_of_range &e) {
    log.warning("[%s] argument out of range for std::stoi: %s", __func__,
                begin_id);
  }
  return *this;
}
TreeConfigurationProvider &
TreeConfigurationProvider::set_end_id(std::string &end_id,
                                      std::string &configuration_id) {
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

  if (conf_id >= providers_vector.size()) {
    log.error("[%s] looking for unexisting configuration with id: %d", __func__,
              conf_id);
  }

  try {
    providers_vector[conf_id].set_end_id(std::stoi(end_id));
  } catch (std::invalid_argument &e) {
    log.warning("[%s] invalid argument for std::stoi: %s", __func__, end_id);
  } catch (std::out_of_range &e) {
    log.warning("[%s] argument out of range for std::stoi: %s", __func__,
                end_id);
  }
  return *this;
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