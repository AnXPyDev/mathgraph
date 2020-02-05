#pragma once

#include <vector>

#include "value.hpp"

namespace mathgraph::algebra::value {
  class List;
}

using namespace mathgraph::algebra::value;

class mathgraph::algebra::value::List : public Value {
private:
  std::vector<Value*> elements;
public:
  const std::vector<Value*> &get_elements();
  void set_elements(std::vector<Value*> elements);
  ~List();
  List(std::vector<Value*> elements = {});
};
