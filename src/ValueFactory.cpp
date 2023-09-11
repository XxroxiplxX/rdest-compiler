#include "../include/ValueFactory.h"

namespace ValueTypes {
Value *ValueFactory::create_numerical_value() const {
  return new NumericalValue();
}
Value *ValueFactory::create_ident_value() const { 
  return new IdentifierValue(); 
}
Value *ValueFactory::create_value(std::string base) const {
  Value *to_ret = nullptr;
  auto load = "";
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
  to_ret->set_val(load);
  return to_ret;
}
} // namespace ValueTypes