#include <vector>
#include <string>

#include "../symbol.hpp"
#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "function.hpp"
#include "call.hpp"

using namespace mathgraph::algebra;

void expression::Call::set_expression(expression::Expression_ptr expression) {
  this->expression = expression;
}

void expression::Call::set_arguments(std::vector<expression::Expression_ptr> arguments) {
  this->arguments = arguments;
}

const std::vector<expression::Expression_ptr> &expression::Call::get_arguments() {
  return this->arguments;
}

expression::Expression_ptr expression::Call::get_expression(Enviroment_ptr env, Expression_ptr caller) {
  return this->expression->get_expression(env, this->expression);
}

value::Value_ptr expression::Call::get_value(Enviroment_ptr env) {
  expression::Expression_ptr expr = this->get_expression(env);
  Enviroment_ptr temp_env(new Enviroment());
  temp_env->set_parent(env);
  std::vector<Symbol_ptr> argument_list;
  if (expr->type == "expression::function") {
    argument_list = (dynamic_cast<expression::Function*>(expr.get()))->get_argument_list();
  }
  for (int i = 0; i < this->arguments.size(); ++i) {
    if (i >= argument_list.size()) {
      Symbol_ptr arg_name(new Symbol("_arg" + std::to_string(i)));
      temp_env->set_value(arg_name, this->arguments[i]);
    } else {
      temp_env->set_value(argument_list[i], this->arguments[i]);
    }
  }
  return expr->get_value(temp_env);
}


expression::Call::Call(expression::Expression_ptr expression, std::vector<expression::Expression_ptr> arguments) {
  this->type = "expression::call";
  this->set_expression(expression);
  this->set_arguments(arguments);
}
