

#include "Register.h"

namespace memory {
Register::Register(int _id) : id(_id), _state(_UNLOCKED), is_proc_arg(false) {}
Register::Register(int _id, const char *arg)
    : id(_id), _state(_UNLOCKED), is_proc_arg(true) {
  delete[] arg;
}
void Register::lock() { _state = _LOCKED; }
void Register::unlock() { _state = _UNLOCKED; }
int Register::get_id() const { return id; }
bool Register::is_locked() const { return (_state == _LOCKED); }
bool Register::is_reg_proc_arg() const { return is_proc_arg; }
std::string Register::get_id_as_string() const { return std::to_string(id); }
RegisterFactory::RegisterFactory() : register_index(0) {}
std::shared_ptr<Register> RegisterFactory::create_register_shared_ptr() {
  return std::make_shared<Register>(register_index++);
}
std::shared_ptr<Register>
RegisterFactory::create_register_shared_ptr(const char *arg) {
  return std::make_shared<Register>(register_index++, arg);
}

} // namespace memory