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
  const whole_t& Number::value() { return this->_value; }
  Number::Number(whole_t value) : _value{ value } {
    this->_type = "number";
  }

  shared_ptr<Expression> Number::construct(approx_t value) {
    if (value - floor(value) > EPSILON) {
      return Fraction::construct(Number::construct(value / operations::gcd(value)), Number::construct(1));
    }
    return shared_ptr<Expression>(new Number((whole_t)value));
  }
}
