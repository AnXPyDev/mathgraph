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
  value::Value* value;
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  Constant(value::Value* value = value::undefined_value);
};
