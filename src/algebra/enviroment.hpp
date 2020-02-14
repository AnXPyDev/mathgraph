#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "base.hpp"
#include "symbol.hpp"

namespace mathgraph::algebra {
  class Enviroment;
  typedef std::shared_ptr<Enviroment> Enviroment_ptr;
  extern Enviroment_ptr undefined_enviroment;
}

#include "expression/expression.hpp"

using namespace mathgraph::algebra;

class mathgraph::algebra::Enviroment {
private:
  std::map<std::string, expression::Expression_ptr> symbol_map;
  Enviroment_ptr parent;
public:
  void set(Symbol_ptr symbol, expression::Expression_ptr expression);
  expression::Expression_ptr get(Symbol_ptr symbol);
  void set_parent(Enviroment_ptr parent);
  Enviroment_ptr get_parent();
  ~Enviroment();
  Enviroment();
};
