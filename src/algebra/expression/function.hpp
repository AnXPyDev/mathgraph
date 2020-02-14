#pragma once

#include <vector>

#include "../value/value.hpp"
#include "../symbol.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Function;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Function : public expression::Expression {
private:
  std::vector<Symbol_ptr> argument_list;
  expression::Expression_ptr expression;
public:
  const std::vector<Symbol_ptr> &get_argument_list();
  void set_argument_list(std::vector<Symbol_ptr> argument_list);
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  expression::Expression_ptr get_expression(Enviroment_ptr env = undefined_enviroment, Expression_ptr caller = NULL);
  void set_expression(expression::Expression_ptr expression);
  Function(std::vector<Symbol_ptr> argument_list = {}, expression::Expression_ptr expression = expression::undefined_expression);
};
