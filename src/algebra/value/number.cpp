#include "number.hpp"

using namespace mathgraph::algebra;

const approximate_t &value::Number::get_value() {
  return this->value;
}

void value::Number::set_value(approximate_t value) {
  this->value = value;
}

value::Number::~Number() {}

value::Number::Number(approximate_t value) {
  this->type = "value::number";
  this->set_value(value);
}
