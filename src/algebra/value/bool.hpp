#pragma once

#include "value.hpp"

namespace mathgraph::algebra::value {
  class Bool;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::value::Bool : public value::Value {
private:
  bool value;
public:
  const bool &evaluate();
  void set_value(bool value);
  ~Bool();
  Bool(bool value = true);
};
