#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "base.hpp"
#include "operations.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Expression::output_to_stream(ostream& stream) {
    return stream << this->_type;
  }
  shared_ptr<Expression> Expression::reduce(shared_ptr<Expression> caller) { return caller; }
  shared_ptr<Expression> Expression::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) { return caller; }
  vector<shared_ptr<Expression>> Expression::dependencies(shared_ptr<Expression> caller) { return {}; }
  const string& Expression::type() { return this->_type; }
  Expression::Expression() {
    this->_type = "undefined";
  }

  shared_ptr<Expression> undefined = shared_ptr<Expression>(new Expression);

  ostream& operator<<(ostream& stream, shared_ptr<Expression> expression) {
    return expression->output_to_stream(stream);
  }
  bool operator==(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    return operations::equal(expr_a, expr_b);
  }
  bool operator==(shared_ptr<Expression> expr, string type) {
    return expr->type() == type;
  }
}
