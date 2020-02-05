#pragma once

#include "base.hpp"
#include "value.hpp"

namespace mathgraph::algebra {
  class Number;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::Number : public Value {
private:
  approximate_t value;
public:
  const approximate_t &get_value();
  void set_value(approximate_t value = 0);
  Number(approximate_t value = 0);
};
