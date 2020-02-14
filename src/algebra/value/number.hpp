#pragma once

#include "base.hpp"
#include "value.hpp"

namespace mathgraph::algebra::value {
  class Number;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::value::Number : public value::Value {
private:
  approximate_t value;
public:
  const approximate_t &evaluate();
  void set_value(approximate_t value);
  ~Number();
  Number(approximate_t value = 0);
};
