#include <vector>

#include "../value/value.hpp"
#include "../value/list.hpp"
#include "../enviroment.hpp"
#include "list.hpp"

using namespace mathgraph::algebra;

expression::List::List(std::vector<expression::Expression*> elements) {
  this->type = "expression::list";
  this->elements = elements;
}

value::Value* expression::List::get_value(Enviroment* env) {
  std::vector<value::Value*> value_elements;
  for (auto it = this->elements.begin(); it < this->elements.end(); ++it) {
    value_elements.push_back(((*it)->get_expression(env))->get_value(env));
  }
  return new value::List(value_elements);
}
