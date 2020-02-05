#pragma once

#include <vector>

#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class List;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::List : public expression::Expression {
protected:
  void update_value(Enviroment* enviroment = NULL, bool force_update = false);
public:
  List(std::vector<expression::Expression*> elements = {});
};
