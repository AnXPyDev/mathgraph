#pragma once

#include "../symbol.hpp"
#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Reference;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Reference : public expression::Expression {
public:
  Symbol* symbol;
  expression::Expression* get_expression(Enviroment* env = undefined_enviroment);
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  Reference(Symbol* symbol = undefined_symbol);
};
