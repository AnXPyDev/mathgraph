#include <map>
#include <string>
#include <iostream>
#include <memory>

#include "enviroment.hpp"
#include "symbol.hpp"
#include "expression/expression.hpp"

using namespace mathgraph::algebra;

void Enviroment::set(Symbol_ptr symbol, expression::Expression_ptr expression) {
  this->symbol_map[symbol->get_value()] = expression;
}

expression::Expression_ptr Enviroment::get(Symbol_ptr symbol) {
  if (this->symbol_map.find(symbol->get_value()) != this->symbol_map.end()) {
    return this->symbol_map[symbol->get_value()];
  }
  if (this->parent != NULL) {
    return this->parent->get(symbol);
  }
  return expression::undefined_expression;
}

void Enviroment::set_parent(Enviroment_ptr parent) {
  this->parent = parent;
}

Enviroment_ptr Enviroment::get_parent() {
  return this->parent;
}

Enviroment::~Enviroment() {}

Enviroment::Enviroment() {
  this->parent = NULL;
}

namespace mathgraph::algebra {
  Enviroment_ptr undefined_enviroment(new Enviroment());
}
