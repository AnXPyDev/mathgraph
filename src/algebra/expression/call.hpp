#pragma once

#include <vector>

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Call;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Call : public expression::Expression {
private:
  expression::Expression* expression;
  std::vector<expression::Expression*> arguments;
public:
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  expression::Expression* get_expression(Enviroment* env = undefined_enviroment);
  void set_expression(expression::Expression* expression);
  void set_arguments(std::vector<expression::Expression*> arguments);
  const std::vector<expression::Expression*> &get_arguments();
  Call(expression::Expression* expression = expression::undefined_expression, std::vector<expression::Expression*> arguments = {});
};
