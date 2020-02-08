#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "constant.hpp"

using namespace mathgraph::algebra;

expression::Constant::Constant(value::Value* value) {
  this->type = "expression::constant";
  this->value = value;
}

value::Value* expression::Constant::get_value(Enviroment* env) {
  return this->value;
}
