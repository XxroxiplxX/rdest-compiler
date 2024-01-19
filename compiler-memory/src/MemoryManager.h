

#ifndef RDEST_COMPILER_MEMORYMANAGER_H
#define RDEST_COMPILER_MEMORYMANAGER_H

#include "Register.h"
#include "compiler-memory/src/ProcedureMemoryModel.h"
#include <compiler-utils/src/Logger.h>
namespace memory {
class MemoryManager {
  Logging::Logger log{"vm_model_log.log"};
  std::shared_ptr<RegisterFactory> register_factory;
  std::map<std::string, std::unique_ptr<ProcedureMemory>> procedures_memory;
  std::map<std::string, std::shared_ptr<Register>> constants_registers;
  std::shared_ptr<Register> op_1;
  std::shared_ptr<Register> op_2;
  std::shared_ptr<Register> mul_trash;
  std::shared_ptr<Register> mul_prod;
  std::shared_ptr<Register> one_const;
  std::shared_ptr<Register> div_X;
  std::shared_ptr<Register> div_Y;
  std::shared_ptr<Register> div_Q;
  std::shared_ptr<Register> div_R;
  std::shared_ptr<Register> div_C;
  void initialize_constants();
  void initialize_mul_registers();
  void initialize_div_registers();

public:
  MemoryManager();
  std::shared_ptr<Register> &get_one_constant();
  std::shared_ptr<Register> &get_div_X();
  std::shared_ptr<Register> &get_div_Y();
  std::shared_ptr<Register> &get_div_R();
  std::shared_ptr<Register> &get_div_Q();
  std::shared_ptr<Register> &get_div_C();
  std::shared_ptr<Register> &get_mul_prod();
  std::shared_ptr<Register> &get_mul_trash();
  std::shared_ptr<Register> &get_op_1();
  std::shared_ptr<Register> &get_op_2();
  std::shared_ptr<Register> &get_return_adress(std::string &proc_id);
  std::shared_ptr<Register> &get_constant(std::string &number);
  std::shared_ptr<Register> &get_register(std::string &identificator,
                                          std::string &proc_id);
  void assert_var(std::string &identificator, std::string &proc_id);
  void assert_ret_reg(std::string &proc_id);
  void assert_const(std::string &number);
  void assert_argument(std::string &identificator, std::string &proc_id);
};
} // namespace memory

#endif // RDEST_COMPILER_MEMORYMANAGER_H
