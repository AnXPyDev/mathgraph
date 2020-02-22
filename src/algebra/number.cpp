#include <cmath>
#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "fraction.hpp"
#include "operations.hpp"
#include "number.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Number::output_to_stream(ostream& stream) { return stream << this->_value; }
  const number_t& Number::value() { return this->_value; }
  Number::Number(number_t value) : _value{ value } {
    this->_type = "number";
  }

  shared_ptr<Expression> Number::construct(number_t value) {
    if (!ALLOW_FLOATING_POINT && value - floor(value) > EPSILON) {
      auto gcd = operations::gcd(value);
      return Fraction::construct(Number::construct(value / gcd), Number::construct((approx_t)1 / gcd));
    }
    return shared_ptr<Expression>(new Number((number_t)value));
  }
}
