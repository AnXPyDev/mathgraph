#include <cmath>
#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "fraction.hpp"
#include "operations.hpp"
#include "integer.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Integer::output_to_stream(ostream& stream) { return stream << this->_value; }
  const integer_t& Integer::value() { return this->_value; }
  Integer::Integer(integer_t value) : _value{ value } {
    this->_type = "integer";
  }

  shared_ptr<Expression> Integer::construct(float_t value) {
    if (value - floor(value) > EPSILON) {
      auto gcd = operations::gcd(value);
      return Fraction::construct(Integer::construct((integer_t)(value / gcd)), Integer::construct((integer_t)((float_t)1 / gcd)));
    }
    return shared_ptr<Expression>(new Integer((integer_t)value));
  }

  shared_ptr<Expression> Integer::construct(integer_t value) {
    return shared_ptr<Expression>(new Integer(value));
  }

}
