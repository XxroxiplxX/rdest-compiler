#include "../include/ValueFactory.h"

namespace ValueTypes {
Value *ValueFactory::create_numerical_value() const {
  return new NumericalValue();
}
Value *ValueFactory::create_ident_value() const { 
  return new IdentifierValue(); 
}
Value *ValueFactory::create_value(std::string base) {
  Value *to_ret = nullptr;
  std::string load = "";
  log.info("[%s] Create initialization with base: %s", __func__, base);
  if (base[0] == 'I') {
    to_ret = create_ident_value();
    for (int i = 3; i < base.length(); i++) {
      load += base[i];
    }
  } else if (base[0] == 'N') {
    to_ret = create_numerical_value();
    for (int i = 4; i < base.length(); i++) {
      load += base[i];
    }
  } else {
    to_ret = create_ident_value();
    for (int i = 3; i < base.length(); i++) {
      load += base[i];
    }
  }
  log.info("[%s] The collected value is: %s", __func__, load);
  to_ret->set_val(load);
  log.info("[%s] Created value with load: %s", __func__, to_ret->get_val());
  return to_ret;
}
} // namespace ValueTypes