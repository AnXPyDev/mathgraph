#include <iostream>

#include "../expression.hpp"
#include "../number.hpp"
#include "../boolean.hpp"
#include "../symbol.hpp"
#include "../list.hpp"

#include "compare.hpp"

namespace mathgraph::algebra::operations {
  bool equal(shared_ptr<Expression> a, shared_ptr<Expression> b) {
    if (a->get_type() != b->get_type()) {
      return false;
    } else if (a->get_type() == "undefined") {
      return equal(dynamic_cast<Expression*>(a.get()), dynamic_cast<Expression*>(b.get()));
    } else if (a->get_type() == "number") {
      return equal(dynamic_cast<Number*>(a.get()), dynamic_cast<Number*>(b.get()));
    } else if (a->get_type() == "boolean") {
      return equal(dynamic_cast<Boolean*>(a.get()), dynamic_cast<Boolean*>(b.get()));
    } else if (a->get_type() == "list") {
      return equal(dynamic_cast<List*>(a.get()), dynamic_cast<List*>(b.get()));
    } else if (a->get_type() == "symbol") {
      return equal(dynamic_cast<Symbol*>(a.get()), dynamic_cast<Symbol*>(b.get()));
    }
  };

  bool equal(Expression* a, Expression* b) { return true; }
  bool equal(Number* a, Number* b) { return a->get() == b->get(); }
  bool equal(Boolean* a, Boolean* b) { return a->get() == b->get(); }
  bool equal(Symbol* a, Symbol* b) { return a->get() == b->get(); }
  bool equal(List* a, List* b) {
    auto elements1 = a->get();
    auto elements2 = a->get();
    if (elements1.size() != elements2.size()) {
      return false;
    }
    for (int i = 0; i < elements1.size(); ++i) {
      if (!equal(elements1[i], elements2[i])) {
        return false;
      }
    }
    return true;
  }
}
