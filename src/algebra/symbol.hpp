#pragma once

#include <string>

#include "object.hpp"

namespace mathgraph::algebra {
  class Symbol;
  extern Symbol* undefined_symbol;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::Symbol : public Object {
private:
  std::string value;
public:
  const std::string &get_value();
  void set_value(std::string value);
  ~Symbol();
  Symbol(std::string value);
};
