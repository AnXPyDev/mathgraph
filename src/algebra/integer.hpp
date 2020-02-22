// number represents a constant, a defined numerical value

#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Integer : public Expression {
    ostream& output_to_stream(ostream& stream);
    // getter for _value
    const integer_t& value();
    Integer(integer_t value);
    // constructs a new number as a shared pointer to expression
    static shared_ptr<Expression> construct(integer_t value = 0);
    static shared_ptr<Expression> construct(float_t value = 0);
  private:
    // the value stored in Number
    integer_t _value;
  };
}
