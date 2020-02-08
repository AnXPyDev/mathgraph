#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "expression.hpp"

using namespace mathgraph::algebra;

expression::Expression::Expression() {
  this->type = "expression";
}

expression::Expression* expression::Expression::get_expression(Enviroment* env) {
  return this;
}

value::Value* expression::Expression::get_value(Enviroment* env) {
  return value::undefined_value;
}

namespace mathgraph::algebra::expression {
  Expression* undefined_expression = new Expression();
}
