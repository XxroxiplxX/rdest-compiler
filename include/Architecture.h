#ifndef COMPILER_VMM_ARCHTECTURE
#define COMPILER_VMM_ARCHTECTURE

#include "Logger.h"
#include <map>
#include <memory>
#include <vector>
namespace VirtualMachineModel {
enum state { _LOCKED, _UNLOCKED };
class Register {
  int id;
  state state;
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
public:
  std::unique_ptr<Register> create_register_unique_ptr(int _id);
  std::unique_ptr<Register> create_register_unique_ptr(int _id,
                                                       const char *arg);
};
class Memory {
  std::map<std::string, std::unique_ptr<Register>> variables;
  std::vector<std::string> argument_identificators;
  std::unique_ptr<Register> return_adress;

public:
  std::unique_ptr<Register> get_variable(std::string identificator) const;
  std::vector<std::string> &get_argument_identificators(int num);
  std::unique_ptr<Register> get_return_adress() const;
  void set_return_register();
  void insert_variable();
};

class Architecture {
  Logging::Logger log{"vm_model_log.log"};
  int register_index;
  std::map<std::string, Memory> procedures_memory;
  std::map<std::string, std::unique_ptr<Register>> constants_registers;
  std::unique_ptr<Register> op_1;
  std::unique_ptr<Register> op_2;
  std::unique_ptr<Register> mul_trash;
  std::unique_ptr<Register> mul_prod;
  std::unique_ptr<Register> one_const;
  std::unique_ptr<Register> div_X;
  std::unique_ptr<Register> div_Y;
  std::unique_ptr<Register> div_Q;
  std::unique_ptr<Register> div_R;
  std::unique_ptr<Register> div_C;
  void initialize_constants();
  void initialize_mul_registers();
  void initialize_div_registers();

public:
  std::unique_ptr<Register> get_one_constant() const;
  std::unique_ptr<Register> get_div_X() const;
  std::unique_ptr<Register> get_div_Y() const;
  std::unique_ptr<Register> get_div_R() const;
  std::unique_ptr<Register> get_div_Q() const;
  std::unique_ptr<Register> get_div_C() const;
  std::unique_ptr<Register> get_mul_prd() const;
  std::unique_ptr<Register> get_op_1() const;
  std::unique_ptr<Register> get_op_2() const;
  std::unique_ptr<Register> get_return_adress(std::string &proc_id) const;
  std::unique_ptr<Register> get_constant(std::string &number) const;
  std::unique_ptr<Register> get_register(std::string &identificator,
                                         std::string &proc_id) const;
  void assert_var(std::string &identificator, std::string &proc_id);
  void assert_ret_reg(std::string &proc_id);
  void assert_const(std::string &number);
  void assert_argument(std::string &identificator, std::string &proc_id);
};

} // namespace VirtualMachineModel

#endif // COMPILER_VMM_ARCHTECTURE