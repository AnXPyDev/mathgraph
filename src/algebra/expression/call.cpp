#include <vector>
#include <string>

#include "../symbol.hpp"
#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "function.hpp"
#include "call.hpp"

using namespace mathgraph::algebra;

void expression::Call::set_expression(expression::Expression* expression) {
  this->expression = expression;
}

void expression::Call::set_arguments(std::vector<expression::Expression*> arguments) {
  this->arguments = arguments;
}

const std::vector<expression::Expression*> &expression::Call::get_arguments() {
  return this->arguments;
}

expression::Expression* expression::Call::get_expression(Enviroment* env) {
  return this->expression->get_expression(env);
}

value::Value* expression::Call::get_value(Enviroment* env) {
  expression::Expression* expr = this->get_expression(env);
  Enviroment* temp_env = new Enviroment();
  temp_env->set_parent(env);
  std::vector<Symbol*> argument_list;
  if (expr->type == "expression::function") {
    argument_list = (dynamic_cast<expression::Function*>(expr))->get_argument_list();
  }
  for (int i = 0; i < this->arguments.size(); ++i) {
    if (i >= argument_list.size()) {
      Symbol arg_name("_arg" + std::to_string(i));
      temp_env->set_value(&arg_name, this->arguments[i]);
    } else {
      temp_env->set_value(argument_list[i], this->arguments[i]);
    }
  }
  auto ret = expr->get_value(temp_env);
  delete temp_env;
  return ret;
}


expression::Call::Call(expression::Expression* expression, std::vector<expression::Expression*> arguments) {
  this->type = "expression::call";
  this->set_expression(expression);
  this->set_arguments(arguments);
}
