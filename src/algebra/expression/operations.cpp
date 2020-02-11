#include "../value/value.hpp"
#include "../value/bool.hpp"
#include "../value/operations.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"
#include "operations.hpp"

using namespace mathgraph::algebra;

expression::Operation::Operation(expression::Expression_ptr expr_a, expression::Expression_ptr expr_b) {
  this->type = "expression::operation";
  this->expr_a = expr_a;
  this->expr_b = expr_b;
}

value::Value_ptr expression::operations::Add::get_value(Enviroment_ptr env) {
  return value::operations::add(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Subtract::get_value(Enviroment_ptr env) {
  return value::operations::subtract(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Multiply::get_value(Enviroment_ptr env) {
  return value::operations::multiply(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Divide::get_value(Enviroment_ptr env) {
  return value::operations::divide(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Modulus::get_value(Enviroment_ptr env) {
  return value::operations::modulus(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Power::get_value(Enviroment_ptr env) {
  return value::operations::power(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Root::get_value(Enviroment_ptr env) {
  return value::operations::root(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Logarithm::get_value(Enviroment_ptr env) {
  return value::operations::logarithm(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::And::get_value(Enviroment_ptr env) {
  return value::operations::conjunction(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Or::get_value(Enviroment_ptr env) {
  return value::operations::disjunction(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Equal::get_value(Enviroment_ptr env) {
  return value::operations::equal(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Less::get_value(Enviroment_ptr env) {
  return value::operations::less(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::More::get_value(Enviroment_ptr env) {
  return value::operations::more(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}
value::Value_ptr expression::operations::Less_or_equal::get_value(Enviroment_ptr env) {
  return value::operations::less_or_equal(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::More_or_equal::get_value(Enviroment_ptr env) {
  return value::operations::more_or_equal(((this->expr_a)->get_expression(env, this->expr_a))->get_value(env), ((this->expr_b)->get_expression(env, this->expr_b))->get_value(env));
}

value::Value_ptr expression::operations::Negate::get_value(Enviroment_ptr env) {
  return value::operations::negate(this->get_expression(env)->get_value(env));
}

expression::Expression_ptr expression::operations::Negate::get_expression(Enviroment_ptr env, expression::Expression_ptr caller) {
  return this->expression;
}

expression::operations::Negate::Negate(expression::Expression_ptr expression) {
  this->type = "expression::operation::negate";
  this->expression = expression;
}

value::Value_ptr if_then_else(value::Value_ptr condition, expression::Expression_ptr case_true, expression::Expression_ptr case_false, Enviroment_ptr env) {
  if (condition->type == "value::list") {
    std::vector<value::Value_ptr> new_list_elements;
    List* list = dynamic_cast<value::List*>(condition.get());
    std::vector<value::Value_ptr> list_elements = list->get_elements();
    for (auto it = list_elements.begin(); it < list_elements.end(); ++it) {
      new_list_elements.push_back(if_then_else(*it, case_true, case_false, env));
    }
    return value::Value_ptr(new value::List(new_list_elements));
  } else {
    bool boolean_condition = value::operations::to_boolean(condition);
    expression::Expression_ptr ret_expr = case_false;
    if (boolean_condition) {
      ret_expr = case_true;
    }
    value::Value_ptr ret = ret_expr->get_value(env);
    if (ret != value::undefined_value) {
      return ret;
    }
    return value::Value_ptr(new value::Bool(boolean_condition));
  }
}

value::Value_ptr expression::operations::If::get_value(Enviroment_ptr env) {
  return if_then_else(this->condition->get_value(env), this->case_true, this->case_false, env);
}

expression::operations::If::If(expression::Expression_ptr condition, expression::Expression_ptr case_true, expression::Expression_ptr case_false) {
  this->type = "expression::operation::if";
  this->condition = condition;
  this->case_false = case_false;
  this->case_true = case_true;
}
