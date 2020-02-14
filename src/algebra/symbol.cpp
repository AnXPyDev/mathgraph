#include "symbol.hpp"

namespace mathgraph::algebra {
  const string& Symbol::get() {
    return this->value;
  }

  ostream& Symbol::output_to_stream(ostream& os) {
    return os << this->value;
  }

  Symbol::Symbol(string value) : value{ value } {}

  shared_ptr<Expression> Symbol::construct(string value) {
    return shared_ptr<Expression>(new Symbol(value));
  }
}
