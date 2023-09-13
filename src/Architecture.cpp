#include "Architecture.h"
#include <memory>

namespace VirtualMachineModel {

Register::Register(int _id) : id(_id), _state(_UNLOCKED), is_proc_arg(false) {}
Register::Register(int _id, const char *arg)
    : id(_id), _state(_UNLOCKED), is_proc_arg(true) {
  delete[] arg;
}
void Register::lock() { _state = _LOCKED; }
void Register::unlock() { _state = _UNLOCKED; }
int Register::get_id() const { return id; }
bool Register::is_locked() const { return (_state == _LOCKED) ? true : false; }
bool Register::is_reg_proc_arg() const { return is_proc_arg; }

RegisterFactory::RegisterFactory() : register_index(0) {}
std::unique_ptr<Register> RegisterFactory::create_register_unique_ptr() {
  return std::unique_ptr<Register>(new Register(register_index++));
}
std::unique_ptr<Register>
RegisterFactory::create_register_unique_ptr(const char *arg) {
  return std::unique_ptr<Register>(new Register(register_index++, arg));
}

Memory::Memory(std::shared_ptr<RegisterFactory> &reg_fact_ptr)
    : register_factory_ptr(reg_fact_ptr) {}
std::unique_ptr<Register> &Memory::get_variable(std::string &identificator) {
  return variables[identificator];
}
std::vector<std::string> &Memory::get_argument_identificators() {
  return argument_identificators;
}
std::unique_ptr<Register> &Memory::get_return_adress() { return return_adress; }
int Memory::set_return_adress() {
  return_adress = register_factory_ptr->create_register_unique_ptr();
  return return_adress->get_id();
}
int Memory::insert_variable(std::string &var_identificator) {
  variables[var_identificator] =
      register_factory_ptr->create_register_unique_ptr();
  return variables[var_identificator]->get_id();
}
void Memory::insert_argument(std::string &arg_identificator) {
  argument_identificators.push_back(arg_identificator);
}

Architecture::Architecture()
    : register_factory(
          std::shared_ptr<RegisterFactory>(new RegisterFactory())) {
  initialize_constants();
  initialize_mul_registers();
  initialize_div_registers();
}
void Architecture::initialize_constants() {
  one_const = register_factory->create_register_unique_ptr();
  log.info("[%s] one constant register initialized with id: %d", __func__,
           one_const->get_id());
}
void Architecture::initialize_mul_registers() {
  mul_prod = register_factory->create_register_unique_ptr();
  log.info("[%s] multiply product register initialized with id: %d", __func__,
           mul_prod->get_id());
  mul_trash = register_factory->create_register_unique_ptr();
  log.info("[%s] multiply trash register initialized with id: %d", __func__,
           mul_trash->get_id());
}
void Architecture::initialize_div_registers() {
  div_X = register_factory->create_register_unique_ptr();
  log.info("[%s] divide X register initialized with id: %d", __func__,
           div_X->get_id());

  div_Y = register_factory->create_register_unique_ptr();
  log.info("[%s] divide Y register initialized with id: %d", __func__,
           div_Y->get_id());

  div_Q = register_factory->create_register_unique_ptr();
  log.info("[%s] divide Q register initialized with id: %d", __func__,
           div_Q->get_id());

  div_R = register_factory->create_register_unique_ptr();
  log.info("[%s] divide R register initialized with id: %d", __func__,
           div_R->get_id());

  div_C = register_factory->create_register_unique_ptr();
  log.info("[%s] divide C register initialized with id: %d", __func__,
           div_C->get_id());
}
std::unique_ptr<Register> &Architecture::get_one_constant() {
  log.info("[%s] memory passed one constant register with id: %d", __func__,
           one_const->get_id());
  return one_const;
}
std::unique_ptr<Register> &Architecture::get_div_X() {
  log.info("[%s] memory passed divide X register with id: %d", __func__,
           div_X->get_id());
  return div_X;
}
std::unique_ptr<Register> &Architecture::get_div_Y() {
  log.info("[%s] memory passed divide Y register with id: %d", __func__,
           div_Y->get_id());
  return div_Y;
}
std::unique_ptr<Register> &Architecture::get_div_R() {
  log.info("[%s] memory passed divide R register with id: %d", __func__,
           div_R->get_id());
  return div_R;
}
std::unique_ptr<Register> &Architecture::get_div_Q() {
  log.info("[%s] memory passed divide Q register with id: %d", __func__,
           div_Q->get_id());
  return div_Q;
}
std::unique_ptr<Register> &Architecture::get_div_C() {
  log.info("[%s] memory passed divide C register with id: %d", __func__,
           div_C->get_id());
  return div_C;
}
std::unique_ptr<Register> &Architecture::get_mul_prod() {
  log.info("[%s] memory passed multiply product register with id: %d", __func__,
           mul_prod->get_id());
  return mul_prod;
}
std::unique_ptr<Register> &Architecture::get_mul_trash() {
  log.info("[%s] memory passed multiply trash register with id: %d", __func__,
           mul_trash->get_id());
  return mul_trash;
}
std::unique_ptr<Register> &Architecture::get_op_1() {
  log.info("[%s] memory passed op 1 register with id: %d", __func__,
           op_1->get_id());
  return op_1;
}
std::unique_ptr<Register> &Architecture::get_op_2() {
  log.info("[%s] memory passed op 2 register with id: %d", __func__,
           op_2->get_id());
  return op_2;
}
std::unique_ptr<Register> &
Architecture::get_return_adress(std::string &proc_id) {
  auto &ret_adress = procedures_memory[proc_id]->get_return_adress();
  log.info("[%s] memory passed register with id: %d", __func__,
           ret_adress->get_id());
  return ret_adress;
}
std::unique_ptr<Register> &Architecture::get_constant(std::string &number) {
  auto &_constant = constants_registers[number];
  log.info("[%s] memory passed register with id: %d", __func__,
           _constant->get_id());
  return _constant;
}
std::unique_ptr<Register> &
Architecture::get_register(std::string &identificator, std::string &proc_id) {
  auto &_register = procedures_memory[proc_id]->get_variable(identificator);
  log.info("[%s] memory passed register with id: %d", __func__,
           _register->get_id());
  return _register;
}
void Architecture::assert_var(std::string &identificator,
                              std::string &proc_id) {
  if (!procedures_memory[proc_id]) {
    procedures_memory[proc_id] =
        std::make_unique<Memory>(Memory(register_factory));
    log.info("[%s] memory initialized unit for procedure with id: %s", __func__,
             proc_id);
  }
  int id = procedures_memory[proc_id]->insert_variable(identificator);
  log.info("[%s] memory initialized variable register with id %d for procedure "
           "with id: %s",
           __func__, id, proc_id);
}
void Architecture::assert_ret_reg(std::string &proc_id) {
  int id = procedures_memory[proc_id]->set_return_adress();
  log.info("[%s] memory initialized return register with id %d for procedure "
           "with id: %s",
           __func__, id, proc_id);
}
void Architecture::assert_const(std::string &number) {
  constants_registers[number] = register_factory->create_register_unique_ptr();
  log.info("[%s] memory initialized constant register with id %d", __func__,
           constants_registers[number]->get_id());
}
void Architecture::assert_argument(std::string &identificator,
                                   std::string &proc_id) {
  if (!procedures_memory[proc_id]) {
    procedures_memory[proc_id] =
        std::make_unique<Memory>(Memory(register_factory));
    log.info("[%s] memory initialized unit for procedure with id: %s", __func__,
             proc_id);
  }
  procedures_memory[proc_id]->insert_argument(identificator);
  log.info("[%s] memory accepted argument: %s for procedure with id: %s",
           __func__, identificator, proc_id);
}
} // namespace VirtualMachineModel