#pragma once

#include "algebra/base.hpp"
#include "algebra/operations/base.hpp"

namespace mathgraph::algebra::operations {
  float_t gcd(float_t a, float_t b = 1);
  integer_t gcd(integer_t a, integer_t b = 1);
}
