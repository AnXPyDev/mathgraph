#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "expression.hpp"

using namespace mathgraph::algebra;

expression::Expression::Expression() {
  this->type = "expression";
}

expression::Expression_ptr expression::Expression::get_expression(Enviroment_ptr env, expression::Expression_ptr caller) {
  if (caller != NULL) {
    return caller;
  }
  return expression::Expression_ptr(this);
}

value::Value_ptr expression::Expression::get_value(Enviroment_ptr env) {
  return value::undefined_value;
}

namespace mathgraph::algebra::expression {
  Expression_ptr undefined_expression(new Expression());
}
