#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Float : public Expression {
    ostream& output_to_stream(ostream& stream);
    // getter for _value
    const float_t& value();
    Float(float_t value);
    // constructs a new number as a shared pointer to expression
    static shared_ptr<Expression> construct(float_t value = 0);
  private:
    // the value stored in Number
    float_t _value;
  };
}
