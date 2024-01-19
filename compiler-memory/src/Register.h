

#ifndef RDEST_COMPILER_REGISTER_H
#define RDEST_COMPILER_REGISTER_H
#include <memory>
#include <string>
namespace memory {
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
  std::string get_id_as_string() const;
};

class RegisterFactory {
  int register_index;

public:
  RegisterFactory();
  std::shared_ptr<Register> create_register_shared_ptr();
  std::shared_ptr<Register> create_register_shared_ptr(const char *arg);
};
} // namespace memory

#endif // RDEST_COMPILER_REGISTER_H
