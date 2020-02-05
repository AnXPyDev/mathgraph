#pragma once

#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "../value/number.hpp"
#include "base.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Constant;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Constant : public expression::Expression {
private:
  value::Value* constant_value;
public:
  void set_value(value::Value* value);
  Constant(value::Value* value = new value::Number(0));
};
