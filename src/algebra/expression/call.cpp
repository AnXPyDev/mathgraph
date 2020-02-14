#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#include "../symbol.hpp"
#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "constant.hpp"
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

value::Value_ptr expression::Call::evaluate(Enviroment_ptr env) {
  expression::Expression_ptr expr = this->expression->get_expression(env, this->expression);
  Enviroment_ptr temp_env(new Enviroment());
  temp_env->set_parent(env);
  std::vector<Symbol_ptr> argument_list;
  if (expr->type == "expression::function") {
    argument_list = (dynamic_cast<expression::Function*>(expr.get()))->get_argument_list();
  }
  for (int i = 0; i < this->arguments.size(); ++i) {
    expression::Expression_ptr constant_arg = expression::Expression_ptr(new expression::Constant(this->arguments[i]->evaluate(env)));
    if (i >= argument_list.size()) {
      Symbol_ptr arg_name(new Symbol("_arg" + std::to_string(i)));
      temp_env->set(arg_name, constant_arg);
    } else {
      temp_env->set(argument_list[i], constant_arg);
    }
  }
  auto ret = expr->evaluate(temp_env);
  return ret;
}


expression::Call::Call(expression::Expression_ptr expression, std::vector<expression::Expression_ptr> arguments) {
  this->type = "expression::call";
  this->set_expression(expression);
  this->set_arguments(arguments);
}
