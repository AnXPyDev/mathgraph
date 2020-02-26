#include <iostream>
#include <memory>
#include <vector>

#include "base.hpp"
#include "expression.hpp"
#include "list.hpp"
#include "boolean_constant.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Boolean_Constant::output_to_stream(ostream& stream) {
    return stream << (this->_value ? "true" : "false");
  }
  const bool& Boolean_Constant::value() { return this->_value; }
  Boolean_Constant::Boolean_Constant(bool value) : _value{ value } {
    this->_type = "boolean_constant";
  }
  shared_ptr<Expression> Boolean_Constant::construct(bool value) {
    return value ? b_true : b_false;
  }
  shared_ptr<Expression> Boolean_Constant::construct(shared_ptr<Expression> expr) {
    if (expr == "undefined") {
      return b_false;
    } else if (expr == "list") {
      vector<shared_ptr<Expression>> new_list_elements;
      auto list_elements = dynamic_cast<List*>(expr.get())->elements();
      for (auto element : list_elements) {
        new_list_elements.push_back(Boolean_Constant::construct(element));
      }
      return List::construct(new_list_elements);
    } else if (expr == "boolean") {
      return expr;
    }
    return b_true;
  }
  shared_ptr<Expression> b_true = shared_ptr<Expression>(new Boolean_Constant(true));
  shared_ptr<Expression> b_false = shared_ptr<Expression>(new Boolean_Constant(false));
}
