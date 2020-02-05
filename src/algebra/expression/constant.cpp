#include "../enviroment.hpp"
#include "../value/value.hpp"
#include "constant.hpp"

using namespace mathgraph::algebra;

void expression::Constant::set_value(value::Value* value) {
  this->value = value;
}

expression::Constant::Constant(value::Value* value) : Expression() {
  this->set_value(value);
}
