#include <vector>

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "function.hpp"

using namespace mathgraph::algebra;

const std::vector<Symbol*> &expression::Function::get_argument_list() {
  return this->argument_list;
}

void expression::Function::set_argument_list(std::vector<Symbol*> argument_list) {
  this->argument_list = argument_list;
}

value::Value* expression::Function::get_value(Enviroment* env) {
  return this->get_expression(env)->get_value(env);
}

expression::Expression* expression::Function::get_expression(Enviroment* env) {
  return this->expression;
}

void expression::Function::set_expression(expression::Expression* expression) {
  this->expression = expression;
}

expression::Function::Function(std::vector<Symbol*> argument_list, expression::Expression* expression) {
  this->type = "expression::function";
  this->set_expression(expression);
  this->set_argument_list(argument_list);
}
