#pragma once

#include <iostream>

#include "base.hpp"
#include "value.hpp"
#include "list.hpp"

namespace mathgraph::algebra::value {
  namespace operations {}
}

using namespace mathgraph::algebra;
using namespace mathgraph::algebra::value;

namespace mathgraph::algebra::value::operations {
  Value_ptr add(Value_ptr a, Value_ptr b);
  Value_ptr subtract(Value_ptr a, Value_ptr b);
  Value_ptr multiply(Value_ptr a, Value_ptr b);
  Value_ptr divide(Value_ptr a, Value_ptr b);
  Value_ptr modulus(Value_ptr a, Value_ptr b);
  Value_ptr power(Value_ptr a, Value_ptr b);
  Value_ptr root(Value_ptr a, Value_ptr b);
  Value_ptr logarithm(Value_ptr a, Value_ptr b);
  Value_ptr less(Value_ptr a, Value_ptr b);
  Value_ptr more(Value_ptr a, Value_ptr b);
  Value_ptr less_or_equal(Value_ptr a, Value_ptr b);
  Value_ptr more_or_equal(Value_ptr a, Value_ptr b);
  Value_ptr equal(Value_ptr a, Value_ptr b);
  Value_ptr conjunction(Value_ptr a, Value_ptr b);
  Value_ptr disjunction(Value_ptr a, Value_ptr b);
  Value_ptr negate(Value_ptr a);
  std::ostream& output_to_stream(std::ostream& stream, Value_ptr b);
  bool to_boolean(Value_ptr a);
}

std::ostream& operator<<(std::ostream& stream, Value_ptr b);
