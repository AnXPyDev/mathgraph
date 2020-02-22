#include <iostream>
#include <cmath>

#include "../base.hpp"
#include "base.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  integer_t gcd(integer_t a, integer_t b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }
  float_t gcd(float_t a, float_t b) {
    unsigned int m = 1;
    while ((a - floor(a)) + (b - floor(b)) > EPSILON) {
      m *= 10;
      a *= 10;
      b *= 10;
    }
    return (float_t)gcd((integer_t)a, (integer_t)b) / (float_t)m;
  }
}
