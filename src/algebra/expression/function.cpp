#include <vector>

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "function.hpp"

using namespace mathgraph::algebra;

const std::vector<Symbol_ptr> &expression::Function::get_argument_list() {
  return this->argument_list;
}

void expression::Function::set_argument_list(std::vector<Symbol_ptr> argument_list) {
  this->argument_list = argument_list;
}

value::Value_ptr expression::Function::get_value(Enviroment_ptr env) {
  return this->get_expression(env)->get_value(env);
}

expression::Expression_ptr expression::Function::get_expression(Enviroment_ptr env, Expression_ptr caller) {
  return this->expression;
}

void expression::Function::set_expression(expression::Expression_ptr expression) {
  this->expression = expression;
}

expression::Function::Function(std::vector<Symbol_ptr> argument_list, expression::Expression_ptr expression) {
  this->type = "expression::function";
  this->set_expression(expression);
  this->set_argument_list(argument_list);
}
