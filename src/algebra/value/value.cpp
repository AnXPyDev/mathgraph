#include "value.hpp"

using namespace mathgraph::algebra;

value::Value::~Value() {}
value::Value::Value() {
  this->type = "value";
}

namespace mathgraph::algebra::value {
  Value_ptr undefined_value(new Value());
}
