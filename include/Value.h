#ifndef COMPILER_VALUETYPES_VALUE
#define COMPILER_VALUETYPES_VALUE
#include <string>
namespace ValueTypes {
enum type_of_value { _NUM = 1, _ID = 2 };
std::string type_to_string(type_of_value type);
class Value {
  std::string val;
protected:
  virtual type_of_value get_type() = 0;
public:
  virtual ~Value(){};
  virtual std::string val_to_string() = 0;
  std::string get_val();
  void set_val(std::string);
};
class NumericalValue : public Value {
  type_of_value get_type() override;

public:
  std::string val_to_string() override;
};
class IdentifierValue : public Value {
  type_of_value get_type() override;

public:
  std::string val_to_string() override;
};
} // namespace ValueTypes

#endif