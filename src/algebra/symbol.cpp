#include "symbol.hpp"

namespace mathgraph::algebra {
  const string& Symbol::get() {
    return this->value;
  }

  ostream& Symbol::output_to_stream(ostream& os) {
    return os << this->value;
  }

  shared_ptr<Expression> Symbol::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    auto ret = scope->get(this->value);
    if (ret->get_type() == "undefined") {
      return caller;
    }
    return ret;
  }

  Symbol::Symbol(string value) : value{ value } {
    this->type = "symbol";
  }

  shared_ptr<Expression> Symbol::construct(string value) {
    shared_ptr<Expression> temp = shared_ptr<Expression>(new Symbol(value));
    return temp->evaluate(temp);
  }
}
