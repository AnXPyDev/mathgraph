#include <vector>

#include "../value/list.hpp"
#include "expression.hpp"
#include "list.hpp"

using namespace mathgraph::algebra;

void expression::List::update_value(Enviroment* enviroment, bool force_update) {
  std::vector<value::Value*> element_list;
  for (auto it = this->members.begin(); it < this->members.end(); ++it) {
    element_list.push_back((*it)->get_value(enviroment, force_update));
  }
  this->value = new value::List(element_list);
}

expression::List::List(std::vector<expression::Expression*> elements) : Expression() {
  this->type = "expression::list";
  for (auto it = elements.begin(); it < elements.end(); ++it) {
    this->add_member(*it);
  }
  this->value = new value::List();
}
