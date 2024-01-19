

#ifndef RDEST_COMPILER_PROCEDUREMEMORYMODEL_H
#define RDEST_COMPILER_PROCEDUREMEMORYMODEL_H

#include "Register.h"
#include <map>
#include <vector>
namespace memory {
class ProcedureMemory {
  std::map<std::string, std::shared_ptr<Register>> variables;
  std::vector<std::string> argument_identificators;
  std::shared_ptr<Register> return_adress;
  std::shared_ptr<RegisterFactory> register_factory_ptr;

public:
  ProcedureMemory(std::shared_ptr<RegisterFactory> &reg_fact_ptr);
  std::shared_ptr<Register> &get_variable(std::string &identificator);
  std::vector<std::string> &get_argument_identificators();
  std::shared_ptr<Register> &get_return_adress();
  int set_return_adress();
  int insert_variable(std::string &var_identificator);
  void insert_argument(std::string &arg_identificator);
};
} // namespace memory

#endif // RDEST_COMPILER_PROCEDUREMEMORYMODEL_H
