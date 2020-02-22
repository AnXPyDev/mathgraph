#include <cmath>
#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"
#include "operations.hpp"
#include "integer.hpp"
#include "float.hpp"

using namespace std;

namespace mathgraph::algebra {
  ostream& Float::output_to_stream(ostream& stream) { return stream << this->_value << "f"; }
  const float_t& Float::value() { return this->_value; }
  Float::Float(float_t value) : _value{ value } {
    this->_type = "float";
  }

  shared_ptr<Expression> Float::construct(float_t value) {
    return shared_ptr<Expression>(new Float(value));
  }

}
