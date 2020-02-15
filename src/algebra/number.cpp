#include "number.hpp"

namespace mathgraph::algebra {
  const approx_t& Number::get() {
    return this->value;
  }

  ostream& Number::output_to_stream(ostream& os) {
    return os << this->value;
  }

  Number::Number(approx_t value) : value{ value } {
    this->type = "number";
  }

  shared_ptr<Expression> Number::construct(approx_t value) {
    return shared_ptr<Expression>(new Number(value));
  }
}
