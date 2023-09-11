#ifndef COMPILER_VALUETYPES_VALUEFACTORY
#define COMPILER_VALUETYPES_VALUEFACTORY

#include "Value.h"
#include "Logger.h"
namespace ValueTypes {
class AbstractValueFactory {
public:
  virtual Value *create_numerical_value() const = 0;
  virtual Value *create_ident_value() const = 0;
};

class ValueFactory : public AbstractValueFactory {
  Logging::Logger log{"value_factory_logs.log"};
  Value *create_numerical_value() const override;
  Value *create_ident_value() const override;

public:
  Value *create_value(std::string base);
};
} // namespace ValueTypes


#endif