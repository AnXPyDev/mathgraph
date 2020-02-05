#pragma once

#include <map>
#include <vector>
#include <string>

#include "base.hpp"
#include "symbol.hpp"

namespace mathgraph::algebra {
  class Enviroment;
}

#include "expression/expression.hpp"

using namespace mathgraph::algebra;

class mathgraph::algebra::Enviroment {
private:
  std::map<std::string, expression::Expression*> symbol_map;
  Enviroment* parent;
public:
  void set_value(Symbol* symbol, expression::Expression* expression);
  expression::Expression* get_value(Symbol* symbol);
  void set_parent(Enviroment* parent);
  Enviroment* get_parent();
  ~Enviroment();
  Enviroment();
};
