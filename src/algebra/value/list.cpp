#include <iostream>
#include <vector>

#include "base.hpp"
#include "value.hpp"
#include "list.hpp"

using namespace mathgraph::algebra;

void value::List::set_elements(std::vector<value::Value_ptr> elements) {
  this->elements = elements;
}

const std::vector<value::Value_ptr> &value::List::get_elements() {
  return this->elements;
}

value::List::List(std::vector<value::Value_ptr> elements) {
  this->type = "value::list";
  this->set_elements(elements);
}

value::List::~List() {}
