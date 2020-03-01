#include <memory>
#include <iostream>

#include "algebra/expression.hpp"
#include "algebra/scope.hpp"
#include "algebra/expressions/boolean_conversion.hpp"
#include "algebra/types/boolean.hpp"
#include "algebra/functions/base.hpp"
#include "algebra/functions/if.hpp"

using namespace std;

namespace mathgraph::algebra::functions {
  ostream& If::output_to_stream(ostream& stream) {
    return stream << "IF<" << this->_condition << " then " << this->_case_true << " else " << this->_case_false << ">";
  }
  expr_t If::condition() { return this->_condition; }
  expr_t If::case_true() { return this->_case_true; }
  expr_t If::case_false() { return this->_case_false; }
  expr_t If::evaluate(expr_t caller, scope_t scope) {
    return If::_evaluate(this->_condition, this->_case_true, this->_case_false, scope);
  }
  expr_t If::reduce(expr_t caller, scope_t scope) {
    return If::_reduce(this->_condition, this->_case_true, this->_case_false, scope);
  }
  If::If(expr_t condition, expr_t case_true, expr_t case_false) : _condition{ condition }, _case_true{ case_true }, _case_false{ case_false } {
    this->_type = "functions::If";
  }
  expr_t If::_reduce(expr_t condition, expr_t case_true, expr_t case_false, scope_t scope) {
    return If::construct(Expression::_reduce(condition, scope), Expression::_reduce(case_true, scope), Expression::_reduce(case_false, scope));
  }
  expr_t If::_evaluate(expr_t condition, expr_t case_true, expr_t case_false, scope_t scope) {
    bool b_condition;
    auto cond_eval = Expression::_evaluate(condition, scope);
    if (cond_eval == "boolean") {
      b_condition = dynamic_cast<types::Boolean*>(cond_eval.get())->value();
    } else {
      b_condition = dynamic_cast<types::Boolean*>(expressions::Boolean_conversion::_evaluate(cond_eval).get())->value();
    }
    if (b_condition) {
      return Expression::_evaluate(case_true, scope);
    } else {
      return Expression::_evaluate(case_false, scope);
    }
  }
  expr_t If::construct(expr_t condition, expr_t case_true, expr_t case_false) {
    return expr_t(new If(condition, case_true, case_false));
  }
}
