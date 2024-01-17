#ifndef COMPILER_VMM_ARCHTECTURE
#define COMPILER_VMM_ARCHTECTURE

#include <compiler-utils/src/Logger.h>
#include <map>
#include <memory>
#include <vector>
namespace VirtualMachineModel {
enum state { _LOCKED, _UNLOCKED };
class Register {
  int id;
  state _state;
  bool is_proc_arg;

public:
  Register(int _id);
  Register(int _id, const char *arg);
  void lock();
  void unlock();
  int get_id() const;
  bool is_locked() const;
  bool is_reg_proc_arg() const;
};

class RegisterFactory {
  int register_index;

public:
  RegisterFactory();
  std::shared_ptr<Register> create_register_shared_ptr();
  std::shared_ptr<Register> create_register_shared_ptr(const char *arg);
};
class Memory {
  std::map<std::string, std::shared_ptr<Register>> variables;
  std::vector<std::string> argument_identificators;
  std::shared_ptr<Register> return_adress;
  std::shared_ptr<RegisterFactory> register_factory_ptr;

public:
  Memory(std::shared_ptr<RegisterFactory> &reg_fact_ptr);
  std::shared_ptr<Register> &get_variable(std::string &identificator);
  std::vector<std::string> &get_argument_identificators();
  std::shared_ptr<Register> &get_return_adress();
  int set_return_adress();
  int insert_variable(std::string &var_identificator);
  void insert_argument(std::string &arg_identificator);
};

class Architecture {
  Logging::Logger log{"vm_model_log.log"};
  std::shared_ptr<RegisterFactory> register_factory;
  std::map<std::string, std::unique_ptr<Memory>> procedures_memory;
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
  Architecture();
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

} // namespace VirtualMachineModel

#endif // COMPILER_VMM_ARCHTECTURE