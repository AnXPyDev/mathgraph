#include <iostream>
#include <cmath>

#include "../base.hpp"
#include "base.hpp"

using namespace std;

namespace mathgraph::algebra::operations {
  whole_t gcd(whole_t a, whole_t b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }
  approx_t gcd(approx_t a, approx_t b) {
    unsigned int m = 1;
    while ((a - floor(a)) + (b - floor(b)) > EPSILON) {
      m *= 10;
      a *= 10;
      b *= 10;
    }
    return (approx_t)gcd((whole_t)a, (whole_t)b) / (approx_t)m;
  }
}
