#include "value.hpp"

using namespace mathgraph::algebra;

value::Value::~Value() {}
value::Value::Value() {
  this->type = "value";
}
