#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "algebra/types/base.hpp"
#include "algebra/expression.hpp"
#include "algebra/expressions/error.hpp"
#include "algebra/types/symbol.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  ostream& Symbol::output_to_stream(ostream& stream) { return stream << this->_value; }
  shared_ptr<Expression> Symbol::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    auto ret = scope->get_key(this->_value);
    if (ret == "undefined") {
      return expressions::Error::construct("symbol \"" + this->_value + "\" does not refer to a defined expression in this scope");
    }
    return Expression::_evaluate(ret, scope);
  }
  vector<shared_ptr<Expression>> Symbol::dependencies(shared_ptr<Expression> caller) {
    return {caller};
  }
  const string& Symbol::value() {
    return this->_value;
  }
  Symbol::Symbol(string value) : _value{ value } {
    this->_type = "symbol";
  }
  shared_ptr<Expression> Symbol::construct(string value) {
    return shared_ptr<Expression>(new Symbol(value));
  }
}
