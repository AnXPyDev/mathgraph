#include "bool.hpp"

using namespace mathgraph::algebra;

const bool &value::Bool::evaluate() {
  return this->value;
}

void value::Bool::set_value(bool value) {
  this->value = value;
}

value::Bool::~Bool() {}

value::Bool::Bool(bool value) {
  this->type = "value::bool";
  this->set_value(value);
}
