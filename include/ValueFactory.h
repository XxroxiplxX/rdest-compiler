#include "Value.h"

namespace ValueTypes {
class AbstractValueFactory {
public:
  virtual Value *createNumericalValue() const = 0;
  virtual Value *createIdentValue() const = 0;
};

class ValueFactory : public AbstractValueFactory {

  Value *createNumericalValue() const override;
  Value *createIdentValue() const override;

public:
  Value *createValue(std::string base) const;
};
} // namespace ValueTypes