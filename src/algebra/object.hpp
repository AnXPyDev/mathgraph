#pragma once

#include <string>

#include "base.hpp"

namespace mathgraph::algebra {
  class Object;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::Object {
private:
public:
  std::string type;
  virtual ~Object();
  Object();
};
