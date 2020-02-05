#include <vector>

#include "../symbol.hpp"
#include "../value/list.hpp"
#include "expression.hpp"
#include "reference.hpp"

using namespace mathgraph::algebra;

void expression::Reference::update_value(Enviroment* enviroment, bool force_update) {
  this->value = (enviroment->get_value(this->symbol))->get_value(enviroment, force_update);
}

expression::Reference::Reference(Symbol* symbol) : Expression() {
  this->symbol = symbol;
}
