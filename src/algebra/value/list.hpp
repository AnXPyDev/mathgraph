#pragma once

#include <vector>

#include "value.hpp"

namespace mathgraph::algebra::value {
  class List;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::value::List : public value::Value {
private:
  std::vector<value::Value_ptr> elements;
public:
  const std::vector<value::Value_ptr> &get_elements();
  void set_elements(std::vector<value::Value_ptr> elements);
  ~List();
  List(std::vector<value::Value_ptr> elements = {});
};
