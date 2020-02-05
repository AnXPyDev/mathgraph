#include <iostream>
#include <vector>

#include "base.hpp"
#include "value.hpp"
#include "list.hpp"

using namespace mathgraph::algebra::value;

void List::set_elements(std::vector<Value*> elements) {
  this->elements = elements;
}

const std::vector<Value*> &List::get_elements() {
  return this->elements;
}

List::List(std::vector<Value*> elements) {
  this->type = "value::list";
  this->set_elements(elements);
}

List::~List() {}
