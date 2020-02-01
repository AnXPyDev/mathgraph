#pragma once

#include <iostream>

#include "base.hpp"
#include "value.hpp"
#include "list.hpp"

namespace mathgraph::algebra {
  namespace operations {}
}

using namespace mathgraph::algebra;

namespace mathgraph::algebra::operations {
  Value* add(Value* a, Value* b);
  Value* subtract(Value* a, Value* b);
  Value* multiply(Value* a, Value* b);
  Value* divide(Value* a, Value* b);
  Value* modulus(Value* a, Value* b);
  Value* power(Value* a, Value* b);
  Value* root(Value* a, Value* b);
  Value* logarithm(Value* a, Value* b);
  std::ostream& output_to_stream(std::ostream& stream, Value* b);
}

// Value* operator+(Value* a, Value* b);
// Value* operator-(Value* a, Value* b);
// Value* operator*(Value* a, Value* b);
// Value* operator/(Value* a, Value* b);
std::ostream& operator<<(std::ostream& stream, Value* b);
