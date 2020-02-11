#include "../value/value.hpp"
#include "../enviroment.hpp"
#include "constant.hpp"

using namespace mathgraph::algebra;

expression::Constant::Constant(value::Value_ptr value) {
  this->type = "expression::constant";
  this->value = value;
}

value::Value_ptr expression::Constant::get_value(Enviroment_ptr env) {
  return this->value;
}
