#include <iostream>
#include <memory>
#include <vector>

#include "algebra/types/base.hpp"
#include "algebra/expression.hpp"
#include "algebra/types/list.hpp"
#include "algebra/expressions/boolean_conversion.hpp"
#include "algebra/types/boolean.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  ostream& Boolean::output_to_stream(ostream& stream) {
    return stream << (this->_value ? "true" : "false");
  }
  const bool& Boolean::value() { return this->_value; }
  Boolean::Boolean(bool value) : _value{ value } {
    this->_type = "boolean_constant";
  }
  shared_ptr<Expression> Boolean::construct(bool value) {
    return value ? b_true : b_false;
  }
  shared_ptr<Expression> Boolean::construct(shared_ptr<Expression> expr) {
    if (expr == "undefined") {
      return b_false;
    } else if (expr == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(expr.get())->elements();
      for (auto element : list_elements) {
        new_list_elements.push_back(Boolean::construct(element));
      }
      return List::construct(new_list_elements);
    } else if (expr == "boolean_constant") {
      return expr;
    } else if (expr->dependencies().size() == 0) {
      return b_true;
    }
    return expressions::Boolean_conversion::construct(expr);
  }
  shared_ptr<Expression> b_true = shared_ptr<Expression>(new Boolean(true));
  shared_ptr<Expression> b_false = shared_ptr<Expression>(new Boolean(false));
}
