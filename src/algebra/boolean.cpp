#include "boolean.hpp"

namespace mathgraph::algebra {
  const bool& Boolean::get() {
    return this->value;
  }

  ostream& Boolean::output_to_stream(ostream& os) {
    return os << (this->value ? "true" : "false");
  }

  Boolean::Boolean(bool value) : value{ value } {
    this->type = "boolean";
  }

  shared_ptr<Expression> Boolean::construct(bool value) {
    if (value) {
      return b_true;
    } else {
      return b_false;
    }
  }

  shared_ptr<Expression> b_true = shared_ptr<Expression>(new Boolean(true));
  shared_ptr<Expression> b_false = shared_ptr<Expression>(new Boolean(false));
}
