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
  std::vector<Symbol*> argument_list;
  expression::Expression* expression;
public:
  const std::vector<Symbol*> &get_argument_list();
  void set_argument_list(std::vector<Symbol*> argument_list);
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  expression::Expression* get_expression(Enviroment* env = undefined_enviroment);
  void set_expression(expression::Expression* expression);
  Function(std::vector<Symbol*> argument_list = {}, expression::Expression* expression = expression::undefined_expression);
};
