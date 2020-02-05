#pragma once

#include <vector>
#include <string>

#include "../value/value.hpp"
#include "../object.hpp"
#include "base.hpp"

namespace mathgraph::algebra::expression {
  class Expression;
}

#include "../enviroment.hpp"

using namespace mathgraph::algebra;

class mathgraph::algebra::expression::Expression : public Object {
protected:
  value::Value* value;
  std::vector<Expression*> members;
  std::vector<Expression*> dependants;
  bool mute_next_update;
  Enviroment* last_enviroment;
  virtual void update_value(Enviroment* enviroment = NULL, bool force_update = false);
public:
  value::Value* get_value(Enviroment* enviroment = NULL, bool force_update = false);
  void update(Enviroment* enviroment = NULL, bool force_update = false);
  void add_member(Expression* member);
  void remove_member(Expression* member);
  void add_dependant(Expression* dependant);
  void remove_dependant(Expression* dependant);
  ~Expression();
  Expression();
};
