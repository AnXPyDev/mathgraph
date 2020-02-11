#pragma once

#include <memory>

#include "../object.hpp"
#include "../value/value.hpp"
#include "base.hpp"

namespace mathgraph::algebra::expression {
  class Expression;
  typedef std::shared_ptr<Expression> Expression_ptr;
  extern Expression_ptr undefined_expression;
}

#include "../enviroment.hpp"

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Expression : public Object {
public:
  virtual expression::Expression_ptr get_expression(Enviroment_ptr env = undefined_enviroment, expression::Expression_ptr caller = NULL);
  virtual value::Value_ptr get_value(Enviroment_ptr env = undefined_enviroment);
  Expression();
};
