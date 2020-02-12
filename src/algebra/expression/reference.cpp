#include <iostream>

#include "../symbol.hpp"
#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"
#include "reference.hpp"

using namespace mathgraph::algebra;

expression::Reference::Reference(Symbol_ptr symbol) {
  this->type = "expression::reference";
  this->symbol = symbol;
}

expression::Expression_ptr expression::Reference::get_expression(Enviroment_ptr env, Expression_ptr caller) {
  return env->get_value(this->symbol);
}

value::Value_ptr expression::Reference::get_value(Enviroment_ptr env) {
  return this->get_expression(env)->get_value(env);
}
