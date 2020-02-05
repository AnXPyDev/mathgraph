#include <map>
#include <string>

#include "enviroment.hpp"
#include "symbol.hpp"
#include "expression/expression.hpp"

using namespace mathgraph::algebra;

void Enviroment::set_value(Symbol* symbol, expression::Expression* expression) {
  this->symbol_map[symbol->get_value()] = expression;
}

expression::Expression* Enviroment::get_value(Symbol* symbol) {
  if (this->symbol_map.find(symbol->get_value()) != this->symbol_map.end()) {
    return this->symbol_map[symbol->get_value()];
  }
  if (this->parent != NULL) {
    return this->parent->get_value(symbol);
  }
  return new expression::Expression();
}

void Enviroment::set_parent(Enviroment* parent) {
  this->parent = parent;
}

Enviroment* Enviroment::get_parent() {
  return this->parent;
}

Enviroment::~Enviroment() {}

Enviroment::Enviroment() {
  this->parent = NULL;
}
