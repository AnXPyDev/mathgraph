#include "base.hpp"
#include "number.hpp"

using namespace mathgraph::algebra;

Number::Number(approximate_t value) {
  this->type = "number";
  this->set_value(value);
}

void Number::set_value(approximate_t value) {
  this->value = value;
}

const approximate_t &Number::evaluate() {
  return this->value;
}
