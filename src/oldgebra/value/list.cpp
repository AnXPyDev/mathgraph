#include <vector>

#include "base.hpp"
#include "value.hpp"
#include "list.hpp"

using namespace mathgraph::algebra;

List::List(std::vector<Value*> elements) {
  this->type = "list";
  this->set_elements(elements);
}

void List::set_elements(std::vector<Value*> elements) {
  this->elements = elements;
}

const std::vector<Value*> &List::get_elements() {
  return this->elements;
}
