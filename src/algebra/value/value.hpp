#pragma once

#include "../object.hpp"
#include "base.hpp"

namespace mathgraph::algebra::value {
  class Value;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::value::Value : public Object {
public:
  virtual ~Value();
  Value();
};
