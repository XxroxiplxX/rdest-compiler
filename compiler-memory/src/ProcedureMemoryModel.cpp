

#include "ProcedureMemoryModel.h"

namespace memory {
ProcedureMemory::ProcedureMemory(std::shared_ptr<RegisterFactory> &reg_fact_ptr)
    : register_factory_ptr(reg_fact_ptr) {}
std::shared_ptr<Register> &
ProcedureMemory::get_variable(std::string &identificator) {
  return variables[identificator];
}
std::vector<std::string> &ProcedureMemory::get_argument_identificators() {
  return argument_identificators;
}
std::shared_ptr<Register> &ProcedureMemory::get_return_adress() {
  return return_adress;
}
int ProcedureMemory::set_return_adress() {
  return_adress = register_factory_ptr->create_register_shared_ptr();
  return return_adress->get_id();
}
int ProcedureMemory::insert_variable(std::string &var_identificator) {
  variables[var_identificator] =
      register_factory_ptr->create_register_shared_ptr();
  return variables[var_identificator]->get_id();
}
void ProcedureMemory::insert_argument(std::string &arg_identificator) {
  argument_identificators.push_back(arg_identificator);
}
} // namespace memory
