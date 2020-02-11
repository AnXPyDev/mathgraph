#pragma once

#include <string>
#include <memory>

#include "object.hpp"

namespace mathgraph::algebra {
  class Symbol;
  typedef std::shared_ptr<Symbol> Symbol_ptr;
  extern Symbol_ptr undefined_symbol;
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
