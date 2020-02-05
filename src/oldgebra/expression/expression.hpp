#pragma once

#include <vector>
#include <string>

#include "base.hpp"
#include "value.hpp"

namespace mathgraph::algebra {
  class Expression;
}

using namespace mathgraph::algebra;

class mathgraph::algebra::Expression {
private:
  std::vector<Expression*> members;
  std::vector<Expression*> dependants;
  Value* value;
public:
  std::string type;
  Value* get_value();
  virtual void update_value();
  void update();
  void add_member(Expression* member);
  void remove_member(Expression* member);
  void add_dependant(Expression* dependant);
  void remove_dependant(Expression* dependant);
  ~Expression();
  Expression();
};
