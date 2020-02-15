#include <iostream>

#include "expression.hpp"

namespace mathgraph::algebra {
  shared_ptr<Expression> Expression::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return caller;
  }

  shared_ptr<Expression> Expression::evaluate(shared_ptr<Expression> caller) {
    return this->evaluate(empty_scope, caller);
  }

  ostream& Expression::output_to_stream(ostream& os) {
    return os << "undefined";
  }

  const string& Expression::get_type() {
    return this->type;
  }

  Expression::Expression() : type{ "undefined" } {}

  shared_ptr<Expression> undefined = shared_ptr<Expression>(new Expression);

  ostream& operator<<(ostream& os, shared_ptr<Expression> expr) {
    return expr->output_to_stream(os);
  }
}
