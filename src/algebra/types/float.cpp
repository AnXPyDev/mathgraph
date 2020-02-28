#include <cmath>
#include <iostream>
#include <memory>

#include "algebra/types/base.hpp"
#include "algebra/expression.hpp"
#include "algebra/operations.hpp"
#include "algebra/types/integer.hpp"
#include "algebra/types/float.hpp"

using namespace std;

namespace mathgraph::algebra::types {
  ostream& Float::output_to_stream(ostream& stream) { return stream << this->_value << "f"; }
  const float_t& Float::value() { return this->_value; }
  Float::Float(float_t value) : _value{ value } {
    this->_type = "float";
  }

  shared_ptr<Expression> Float::construct(float_t value) {
    return shared_ptr<Expression>(new Float(value));
  }

}
