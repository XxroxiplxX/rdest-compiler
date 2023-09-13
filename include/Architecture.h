#ifndef COMPILER_VMM_ARCHTECTURE
#define COMPILER_VMM_ARCHTECTURE

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
} // namespace VirtualMachineModel

#endif // COMPILER_VMM_ARCHTECTURE