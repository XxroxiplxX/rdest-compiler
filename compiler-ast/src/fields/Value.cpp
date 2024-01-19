#include "Value.h"
#include <string>

namespace ast::blocks::fields {

std::string type_to_string(type_of_value type) {
  if (type == _NUM) {
    return "_NUM";
  } else {
    return "_ID";
  }
}

std::string Value::get_val() { return val; }
void Value::set_val(std::string _val) { val = _val; }

std::string NumericalValue::val_to_string() {
  return "@val@ = @type:" + type_to_string(get_type()) + "@load:" + get_val();
}
type_of_value NumericalValue::get_type() { return type_of_value::_NUM; }

std::string IdentifierValue::val_to_string() {
  return "@val@ = @type:" + type_to_string(get_type()) + "@load:" + get_val();
}
type_of_value IdentifierValue::get_type() { return type_of_value::_ID; }

} // namespace ast::blocks::fields