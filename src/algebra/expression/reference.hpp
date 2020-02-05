#pragma once

#include "../enviroment.hpp"
#include "../symbol.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class Reference;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Reference : public expression::Expression {
protected:
  void update_value(Enviroment* enviroment = NULL, bool force_update = false);
  Symbol* symbol;
public:
  Reference(Symbol* symbol = new Symbol(""));
};
