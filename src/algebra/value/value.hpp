#pragma once

#include <memory>

#include "../object.hpp"
#include "base.hpp"

namespace mathgraph::algebra::value {
  class Value;
  typedef std::shared_ptr<Value> Value_ptr;
  extern Value_ptr undefined_value;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::value::Value : public Object {
public:
  virtual ~Value();
  Value();
};
