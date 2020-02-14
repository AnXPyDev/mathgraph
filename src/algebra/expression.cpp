#include "expression.hpp"

namespace mathgraph::algebra {
  shared_ptr<Expression> Expression::evaluate(shared_ptr<Scope> scope, shared_ptr<Expression> caller) {
    return caller;
  }

  ostream& Expression::output_to_stream(ostream& os) {
    return os << "undefined";
  }

  shared_ptr<Expression> undefined = shared_ptr<Expression>(new Expression);

  ostream& operator<<(ostream& os, shared_ptr<Expression> expr) {
    return expr->output_to_stream(os);
  }
}
