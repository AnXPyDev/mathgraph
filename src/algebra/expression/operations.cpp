#include "../value/value.hpp"
#include "../value/operations.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"
#include "operations.hpp"

using namespace mathgraph::algebra;

expression::Operation::Operation(expression::Expression* expr_a, expression::Expression* expr_b) {
  this->expr_a = expr_a;
  this->expr_b = expr_b;
}

value::Value* expression::operations::Add::get_value(Enviroment* env) {
  return value::operations::add(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Subtract::get_value(Enviroment* env) {
  return value::operations::subtract(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Multiply::get_value(Enviroment* env) {
  return value::operations::multiply(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Divide::get_value(Enviroment* env) {
  return value::operations::divide(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Modulus::get_value(Enviroment* env) {
  return value::operations::modulus(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Power::get_value(Enviroment* env) {
  return value::operations::power(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Root::get_value(Enviroment* env) {
  return value::operations::root(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}

value::Value* expression::operations::Logarithm::get_value(Enviroment* env) {
  return value::operations::logarithm(((this->expr_a)->get_expression(env))->get_value(env), ((this->expr_b)->get_expression(env))->get_value(env));
}
