// number represents a constant, a defined numerical value

#pragma once

#include <iostream>
#include <memory>

#include "base.hpp"
#include "expression.hpp"

using namespace std;

namespace mathgraph::algebra {
  struct Number : public Expression {
    ostream& output_to_stream(ostream& stream);
    // getter for _value
    const number_t& value();
    Number(number_t value);
    // constructs a new number as a shared pointer to expression
    static shared_ptr<Expression> construct(approx_t value = 0);
  private:
    // the value stored in Number
    number_t _value;
  };
}
