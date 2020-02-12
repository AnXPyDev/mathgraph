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
  expression::Expression_ptr expression;
  std::vector<expression::Expression_ptr> arguments;
public:
  value::Value_ptr get_value(Enviroment_ptr env = undefined_enviroment);
  void set_expression(expression::Expression_ptr expression);
  void set_arguments(std::vector<expression::Expression_ptr> arguments);
  const std::vector<expression::Expression_ptr> &get_arguments();
  Call(expression::Expression_ptr expression = expression::undefined_expression, std::vector<expression::Expression_ptr> arguments = {});
};
