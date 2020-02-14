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
private:
  std::vector<expression::Expression_ptr> elements;
public:
  value::Value_ptr evaluate(Enviroment_ptr env = undefined_enviroment);
  List(std::vector<expression::Expression_ptr> elements = {});
};
