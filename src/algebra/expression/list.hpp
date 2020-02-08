#pragma once

#include <vector>

#include "../value/value.hpp"
#include "../value/list.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"

namespace mathgraph::algebra::expression {
  class List;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::List : public expression::Expression {
public:
  std::vector<expression::Expression*> elements;
  value::Value* get_value(Enviroment* env = undefined_enviroment);
  List(std::vector<expression::Expression*> elements = {});
};
