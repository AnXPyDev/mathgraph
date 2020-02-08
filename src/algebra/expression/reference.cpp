#include "../symbol.hpp"
#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"
#include "reference.hpp"

using namespace mathgraph::algebra;

expression::Reference::Reference(Symbol* symbol) {
  this->type = "expression::reference";
  this->symbol = symbol;
}

expression::Expression* expression::Reference::get_expression(Enviroment* env) {
  return env->get_value(this->symbol);
}

value::Value* expression::Reference::get_value(Enviroment* env) {
  return this->get_expression(env)->get_value(env);
}
