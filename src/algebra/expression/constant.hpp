#pragma once

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Constant;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Constant : public expression::Expression {
public:
  value::Value_ptr value;
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  Constant(value::Value_ptr value = value::undefined_value);
};
