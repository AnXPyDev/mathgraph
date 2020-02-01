#pragma once

#include <vector>

#include "base.hpp"
#include "value.hpp"

namespace mathgraph::algebra {
  class List;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::List : public Value {
private:
  std::vector<Value*> elements;
public:
  const std::vector<Value*> &get_elements();
  void set_elements(std::vector<Value*> elements = {});
  List(std::vector<Value*> elements = {});
};
