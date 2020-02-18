#include <string>
#include <vector>
#include <memory>

#include "../expression.hpp"
#include "../symbol.hpp"
#include "../number.hpp"
#include "../fraction.hpp"
#include "../exponentiation.hpp"
#include "../list.hpp"
#include "base.hpp"
#include "equal.hpp"

using namespace std;


namespace mathgraph::algebra::operations {
  bool equal(Symbol* sym_a, Symbol* sym_b) {
    return sym_a->value() == sym_b->value();
  }

  bool equal(Number* num_a, Number* num_b) {
    return num_a->value() == num_b->value();
  }

  bool equal(Fraction* frac_a, Fraction* frac_b) {
    return equal(frac_a->numerator(), frac_b->numerator()) && equal(frac_a->denominator(), frac_b->denominator());
  }

  bool equal(Exponentiation* exp_a, Exponentiation* exp_b) {
    return equal(exp_a->base(), exp_b->base()) && equal(exp_a->exponent(), exp_b->exponent());
  }

  bool equal(List* list_a, List* list_b) {
    auto elements_a = list_a->elements();
    auto elements_b = list_b->elements();
    if (elements_a.size() != elements_b.size()) return false;
    for (int i = 0; i < elements_a.size(); ++i) {
      if (!equal(elements_a[i], elements_b[i])) return false;
    }
    return true;
  }

  // compares expressions, returns true if they are equal
  // only expressions of the same type can be equal
  bool equal(shared_ptr<Expression> expr_a, shared_ptr<Expression> expr_b) {
    if (expr_a->type() == expr_b->type()) {
      string type = expr_a->type();
      if (type == "undefined") {
        return true;
      } else if (type == "symbol") {
        return equal(dynamic_cast<Symbol*>(expr_a.get()), dynamic_cast<Symbol*>(expr_b.get()));
      } else if (type == "number") {
        return equal(dynamic_cast<Number*>(expr_a.get()), dynamic_cast<Number*>(expr_b.get()));
      } else if (type == "fraction") {
        return equal(dynamic_cast<Fraction*>(expr_a.get()), dynamic_cast<Fraction*>(expr_b.get()));
      } else if (type == "exponentiation") {
        return equal(dynamic_cast<Exponentiation*>(expr_a.get()), dynamic_cast<Exponentiation*>(expr_b.get()));
      } else if (type == "list" || type == "addition" || type == "multiplication") {
        return equal(dynamic_cast<List*>(expr_a.get()), dynamic_cast<List*>(expr_b.get()));
      }
    }
    return false;
  }
}
