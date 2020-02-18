#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "base.hpp"
#include "expression.hpp"
#include "symbol.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Symbol::output_to_stream(ostream& stream) { return stream << this->_value; }
  shared_ptr<Expression> Symbol::evaluate(shared_ptr<Expression> caller, shared_ptr<Scope> scope) {
    // TODO: implement getting expression from scope
    return undefined;
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
