#include <iostream>

#include "algebra/expression.hpp"
#include "algebra/scope.hpp"
#include "algebra/types/list.hpp"
#include "algebra/types/boolean.hpp"
#include "algebra/functions/base.hpp"
#include "algebra/functions/two_expr_function.hpp"
#include "algebra/functions/and.hpp"

using namespace std;

namespace mathgraph::algebra::functions {
  ostream& And::output_to_stream(ostream& stream) {
    return stream << "(" << this->_expr_a << " && " << this->_expr_b << ")";
  }
  expr_t And::evaluate(expr_t caller, scope_t scope) {
    return And::_evaluate(this->_expr_a, this->_expr_b, scope);
  }
  expr_t And::reduce(expr_t caller, scope_t scope) {
    return And::_reduce(this->_expr_a, this->_expr_b, scope);
  }
  And::And(expr_t expr_a, expr_t expr_b) : Two_expr_function(expr_a, expr_b) {
    this->_type = "functions::And";
  }
  expr_t And::construct(expr_t expr_a, expr_t expr_b) {
    return expr_t(new And(expr_a, expr_b));
  }
  expr_t And::_reduce(expr_t expr_a, expr_t expr_b, scope_t scope) {
    return And::construct(Expression::_reduce(expr_a, scope), Expression::_reduce(expr_b, scope));
  }
  expr_t And::_evaluate(expr_t expr_a, expr_t expr_b, scope_t scope) {
    expr_a = Expression::_evaluate(expr_a, scope);
    expr_b = Expression::_evaluate(expr_b, scope);
    if (expr_a == "list") {
      vector<expr_t> new_list_elements;
      for (auto element : dynamic_cast<types::List*>(expr_a.get())->elements()) {
        new_list_elements.push_back(And::_evaluate(element, expr_b, scope));
      }
      return types::List::construct(new_list_elements);
    } else if (expr_b == "list") {
      vector<expr_t> new_list_elements;
      for (auto element : dynamic_cast<types::List*>(expr_b.get())->elements()) {
        new_list_elements.push_back(And::_evaluate(expr_a, element, scope));
      }
      return types::List::construct(new_list_elements);
    }
    bool b_expr_a = dynamic_cast<types::Boolean*>(Expression::_evaluate(types::Boolean::construct(expr_a)).get())->value();
    bool b_expr_b = dynamic_cast<types::Boolean*>(Expression::_evaluate(types::Boolean::construct(expr_b)).get())->value();
    if (b_expr_a && b_expr_b) {
      return expr_b;
    }
    return types::b_false;
  }
}
