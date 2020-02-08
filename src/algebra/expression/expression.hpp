#pragma once

#include "../object.hpp"
#include "../value/value.hpp"
#include "base.hpp"

namespace mathgraph::algebra::expression {
  class Expression;
  extern Expression* undefined_expression;
}

#include "../enviroment.hpp"

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Expression : public Object {
public:
  virtual Expression* get_expression(Enviroment* env = undefined_enviroment);
  virtual value::Value* get_value(Enviroment* env = undefined_enviroment);
  Expression();
};
