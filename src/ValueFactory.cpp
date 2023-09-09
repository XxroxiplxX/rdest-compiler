#include "../include/ValueFactory.h"

namespace ValueTypes {
Value *ValueFactory::createNumericalValue() const {
  return new NumericalValue();
}
Value *ValueFactory::createIdentValue() const { 
  return new IdentifierValue(); 
}
Value *ValueFactory::createValue(std::string base) const {
  Value *to_ret = nullptr;
  auto load = "";
  if (base[0] == 'I') {
    to_ret = createIdentValue();
    for (int i = 3; i < base.length(); i++) {
      load += base[i];
    }
    to_ret->set_val(load);
  } else if (base[0] == 'N') {
    to_ret = createNumericalValue();
    for (int i = 4; i < base.length(); i++) {
      load += base[i];
    }
  } else {
    to_ret = createIdentValue();
    for (int i = 3; i < base.length(); i++) {
      load += base[i];
    }
  }
}
} // namespace ValueTypes