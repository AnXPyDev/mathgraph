#pragma once

#include <string>

#include "base.hpp"

namespace mathgraph::algebra {
  class Value;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::Value {
public:
  std::string type;
  virtual ~Value();
};
