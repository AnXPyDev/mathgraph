#include <vector>

#include "../value/value.hpp"
#include "../value/list.hpp"
#include "../enviroment.hpp"
#include "expression.hpp"
#include "list.hpp"

using namespace mathgraph::algebra;

expression::List::List(std::vector<expression::Expression_ptr> elements) {
  this->type = "expression::list";
  this->elements = elements;
}

value::Value_ptr expression::List::get_value(Enviroment_ptr env) {
  std::vector<value::Value_ptr> value_elements;
  for (auto it = this->elements.begin(); it < this->elements.end(); ++it) {
    value_elements.push_back(((*it)->get_expression(env, *it))->get_value(env));
  }
  return value::Value_ptr(new value::List(value_elements));
}
