#pragma once

#include "../base.hpp"
#include "base.hpp"

namespace mathgraph::algebra::operations {
  approx_t gcd(approx_t a, approx_t b = 1);
  whole_t gcd(whole_t a, whole_t b = 1);
}
