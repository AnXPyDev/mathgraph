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
  Symbol_ptr symbol;
  expression::Expression_ptr get_expression(Enviroment_ptr env = undefined_enviroment, Expression_ptr caller = NULL);
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  Reference(Symbol_ptr symbol = undefined_symbol);
};
