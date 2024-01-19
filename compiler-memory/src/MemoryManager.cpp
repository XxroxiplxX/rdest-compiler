
#include "MemoryManager.h"

namespace memory {
MemoryManager::MemoryManager()
    : register_factory(std::make_shared<RegisterFactory>()) {
  initialize_constants();
  initialize_mul_registers();
  initialize_div_registers();
}
void MemoryManager::initialize_constants() {
  one_const = register_factory->create_register_shared_ptr();
  log.info("[%s] one constant register initialized with id: %d", __func__,
           one_const->get_id());
}
void MemoryManager::initialize_mul_registers() {
  op_1 = register_factory->create_register_shared_ptr();
  log.info("[%s] multiply op_1 register initialized with id: %d", __func__,
           op_1->get_id());
  op_2 = register_factory->create_register_shared_ptr();
  log.info("[%s] multiply op_2 register initialized with id: %d", __func__,
           op_2->get_id());
  mul_prod = register_factory->create_register_shared_ptr();
  log.info("[%s] multiply product register initialized with id: %d", __func__,
           mul_prod->get_id());
  mul_trash = register_factory->create_register_shared_ptr();
  log.info("[%s] multiply trash register initialized with id: %d", __func__,
           mul_trash->get_id());
}
void MemoryManager::initialize_div_registers() {
  div_X = register_factory->create_register_shared_ptr();
  log.info("[%s] divide X register initialized with id: %d", __func__,
           div_X->get_id());

  div_Y = register_factory->create_register_shared_ptr();
  log.info("[%s] divide Y register initialized with id: %d", __func__,
           div_Y->get_id());

  div_Q = register_factory->create_register_shared_ptr();
  log.info("[%s] divide Q register initialized with id: %d", __func__,
           div_Q->get_id());

  div_R = register_factory->create_register_shared_ptr();
  log.info("[%s] divide R register initialized with id: %d", __func__,
           div_R->get_id());

  div_C = register_factory->create_register_shared_ptr();
  log.info("[%s] divide C register initialized with id: %d", __func__,
           div_C->get_id());
}
std::shared_ptr<Register> &MemoryManager::get_one_constant() {
  log.info("[%s] memory passed one constant register with id: %d", __func__,
           one_const->get_id());
  return one_const;
}
std::shared_ptr<Register> &MemoryManager::get_div_X() {
  log.info("[%s] memory passed divide X register with id: %d", __func__,
           div_X->get_id());
  return div_X;
}
std::shared_ptr<Register> &MemoryManager::get_div_Y() {
  log.info("[%s] memory passed divide Y register with id: %d", __func__,
           div_Y->get_id());
  return div_Y;
}
std::shared_ptr<Register> &MemoryManager::get_div_R() {
  log.info("[%s] memory passed divide R register with id: %d", __func__,
           div_R->get_id());
  return div_R;
}
std::shared_ptr<Register> &MemoryManager::get_div_Q() {
  log.info("[%s] memory passed divide Q register with id: %d", __func__,
           div_Q->get_id());
  return div_Q;
}
std::shared_ptr<Register> &MemoryManager::get_div_C() {
  log.info("[%s] memory passed divide C register with id: %d", __func__,
           div_C->get_id());
  return div_C;
}
std::shared_ptr<Register> &MemoryManager::get_mul_prod() {
  log.info("[%s] memory passed multiply product register with id: %d", __func__,
           mul_prod->get_id());
  return mul_prod;
}
std::shared_ptr<Register> &MemoryManager::get_mul_trash() {
  log.info("[%s] memory passed multiply trash register with id: %d", __func__,
           mul_trash->get_id());
  return mul_trash;
}
std::shared_ptr<Register> &MemoryManager::get_op_1() {
  log.info("[%s] memory passed op 1 register with id: %d", __func__,
           op_1->get_id());
  return op_1;
}
std::shared_ptr<Register> &MemoryManager::get_op_2() {
  log.info("[%s] memory passed op 2 register with id: %d", __func__,
           op_2->get_id());
  return op_2;
}
std::shared_ptr<Register> &
MemoryManager::get_return_adress(std::string &proc_id) {
  auto &ret_adress = procedures_memory[proc_id]->get_return_adress();
  log.info("[%s] memory passed register with id: %d", __func__,
           ret_adress->get_id());
  return ret_adress;
}
std::shared_ptr<Register> &MemoryManager::get_constant(std::string &number) {
  auto &_constant = constants_registers[number];
  log.info("[%s] memory passed register with id: %d", __func__,
           _constant->get_id());
  return _constant;
}
std::shared_ptr<Register> &
MemoryManager::get_register(std::string &identificator, std::string &proc_id) {
  auto &_register = procedures_memory[proc_id]->get_variable(identificator);
  log.info("[%s] memory passed register with id: %d", __func__,
           _register->get_id());
  return _register;
}
void MemoryManager::assert_var(std::string &identificator,
                               std::string &proc_id) {
  if (!procedures_memory[proc_id]) {
    procedures_memory[proc_id] =
        std::make_unique<ProcedureMemory>(ProcedureMemory(register_factory));
    log.info("[%s] memory initialized unit for procedure with id: %s", __func__,
             proc_id);
  }
  int id = procedures_memory[proc_id]->insert_variable(identificator);
  log.info("[%s] memory initialized variable register with id %d for procedure "
           "with id: %s",
           __func__, id, proc_id);
}
void MemoryManager::assert_ret_reg(std::string &proc_id) {
  int id = procedures_memory[proc_id]->set_return_adress();
  log.info("[%s] memory initialized return register with id %d for procedure "
           "with id: %s",
           __func__, id, proc_id);
}
void MemoryManager::assert_const(std::string &number) {
  constants_registers[number] = register_factory->create_register_shared_ptr();
  log.info("[%s] memory initialized constant register with id %d", __func__,
           constants_registers[number]->get_id());
}
void MemoryManager::assert_argument(std::string &identificator,
                                    std::string &proc_id) {
  if (!procedures_memory[proc_id]) {
    procedures_memory[proc_id] =
        std::make_unique<ProcedureMemory>(ProcedureMemory(register_factory));
    log.info("[%s] memory initialized unit for procedure with id: %s", __func__,
             proc_id);
  }
  procedures_memory[proc_id]->insert_argument(identificator);
  log.info("[%s] memory accepted argument: %s for procedure with id: %s",
           __func__, identificator, proc_id);
}
} // namespace memory