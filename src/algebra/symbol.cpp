#include <string>

#include "symbol.hpp"

using namespace mathgraph::algebra;

const std::string &Symbol::get_value() {
  return this->value;
}

void Symbol::set_value(std::string value) {
  this->value = value;
}

Symbol::~Symbol() {}

Symbol::Symbol(std::string value) {
  this->type = "symbol";
  this->set_value(value);
}

