#ifndef COMPILER_VMM_ARCHTECTURE
#define COMPILER_VMM_ARCHTECTURE

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
};
} // namespace VirtualMachineModel

#endif // COMPILER_VMM_ARCHTECTURE